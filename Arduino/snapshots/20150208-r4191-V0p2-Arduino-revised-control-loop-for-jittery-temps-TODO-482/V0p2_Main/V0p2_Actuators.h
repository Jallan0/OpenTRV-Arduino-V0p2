/*
The OpenTRV project licenses this file to you
under the Apache Licence, Version 2.0 (the "Licence");
you may not use this file except in compliance
with the Licence. You may obtain a copy of the Licence at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the Licence is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied. See the Licence for the
specific language governing permissions and limitations
under the Licence.

Author(s) / Copyright (s): Damon Hart-Davis 2014--2015
*/

/*
 * Header for main on-board sensors and actuators for V0p2 variants.
 */

#ifndef V0P2_ACTUATORS_H
#define V0P2_ACTUATORS_H

#include "Actuator.h"





// Abstract class for motor drive.
// Supports abstract model plus remote (wireless) and local/direct implementations.
// Implementations may require poll() called at a fixed rate.
class AbstractRadValve : public SimpleTSUint8Actuator
  {
  public:
    // Returns true if this sensor reading value passed is valid, eg in range [0,100].
    virtual bool isValid(const uint8_t value) const { return(value <= 100); }

    // Returns true iff not (re)calibrating/(re)initialising/(re)syncing.
    // By default there is no recalibration step.
    virtual bool isCalibrated() const { return(true); }

    // True if the controlled physical valve is thought to be at least partially open right now.
    // If multiple valves are controlled then is this true only if all are at least partially open.
    // Used to help avoid running boiler pump against closed valves.
    // Must not be true while (re)calibrating.
    // The default is to use the check the current computed position
    // against the minimum open percentage.
    virtual bool isControlledValveReallyOpen() const { return(isCalibrated() && (value >= getMinPercentOpen())); }

    // Get estimated minimum percentage open for significant flow for this device; strictly positive in range [1,99].
    // Defaults to 1 which is minimum possible legitimate value.
    virtual uint8_t getMinPercentOpen() const { return(1); }
  };


// Generic callback handler for hardware valve motor driver.
class HardwareMotorDriverInterfaceCallbackHandler
  {
  protected:
    ~HardwareMotorDriverInterfaceCallbackHandler() {}

  public:
    // Called when end stop hit, eg by overcurrent detection.
    // Can be called while run() is in progress.
    // Is ISR-/thread- safe.
    virtual void signalHittingEndStop() = 0;
  
    // Called when encountering leading edge of a mark in the shaft rotation in forward direction (falling edge in reverse).
    // Can be called while run() is in progress.
    // Is ISR-/thread- safe.
    virtual void signalShaftEncoderMarkStart() = 0;
  };

// Interface for low-level hardware motor driver.
class HardwareMotorDriverInterface
  {
  protected:
    ~HardwareMotorDriverInterface() {}

  public:
    // Legal motor drive states.
    enum motor_drive
      {
      motorOff = 0, // Motor switched off (default).
      motorDriveClosing, // Drive towards the valve-closed position.
      motorDriveOpening, // Drive towards the valve-open position.
      motorStateInvalid // Higher than any valid state.
      };

    // Call to actually run/stop low-level motor.
    // May take as much as 200ms eg to change direction.
    // Stopping (removing power) should typically be very fast, << 100ms.
    virtual void motorRun(motor_drive dir) = 0;

    // Enable/disable end-stop detection and shaft-encoder.
    // Disabling should usually forces the motor off,
    // with a small pause for any residual movement to complete.
    virtual void enableFeedback(bool enable, HardwareMotorDriverInterfaceCallbackHandler &callback) = 0;

    // If true then enableFeedback(true) needs to be called in a fairly tight loop
    // while the motor is running and for a short while after
    // to capture end-stop hits, etc.
    virtual bool needsPoll() const = 0;
  };

// Generic (unit-testable) motor diver login using end-stop detection and simple shaft-encoder.
// Designed to be embedded in a motor controller instance.
class CurrentSenseValveMotorDirect : public HardwareMotorDriverInterfaceCallbackHandler
  {
  public:
    // Basic/coarse state of driver.
    //
    // Power-up sequence will often require something like:
    //   * withdrowing pin completely (to make valve easy to fit)
    //   * waiting for some user activation step such as pressing a button to indicate valve fitted
    //   * running a (re)calibration for the valve.
    enum driverState
      {
      init = 0,
      initPinWithdrawingFully,
      initPinWithdrawn, // Allows valve to be fitted.
      initCalibrating, // Calibrating full valve travel.
      motorNormal, // Normal operating state: values lower than this indicate that power-up is not complete.
      decalcinating, // TODO: running decalcination cycle (and can recalibrate and mitigate valve seating issues).
      motorDriverWrror // Error state can only nomrally be cleared by power-cycling.
      };

  private:
    // Clicks from one end of the range to the other; 0 if not initialised.
    uint16_t clicksFullTravel;

    // Current clicks from closed end of travel.
    // ISR-/thread- safe with a mutex.
    volatile uint16_t clicksFromClosed;

    // Basic state of driver.
    // Marked volatile so that indivdual reads are ISR-/thread- safe without a mutex.
    // Hold a mutex to do compund operations sucn as read/modify/write.
    volatile /*driverState*/ uint8_t state;

    // Nominal motor drive status, ie what it should be doing.
    // (Motor may not actually be running all the time that this indicates itself not off.)
    /*motor_drive*/ uint8_t motorDriveStatus;

    // Current nominal percent open in range [0,100].
    uint8_t currentPC;

    // Target % open in range [0,100].
    uint8_t targetPC;

    // True if movement can be 'lazy'.
    bool lazy;

    // Turn motor off, or on in a given drive direction.
    // Sets state accordingly.
    // Does not provide any monitoring of stall, position encoding, etc.
    // May take significant time and have to be done very carefully in concrete implementations.
    void setMotorDrive(HardwareMotorDriverInterface::motor_drive dir) { motorDriveStatus = min((uint8_t)dir, (uint8_t)HardwareMotorDriverInterface::motorStateInvalid - 1); }

  public:
    CurrentSenseValveMotorDirect() : state(init), motorDriveStatus(HardwareMotorDriverInterface::motorOff) { }

    // Called when end stop hit, eg by overcurrent detection.
    // Can be called while run() is in progress.
    // Is ISR-/thread- safe.
    virtual void signalHittingEndStop();

    // Called when encountering leading edge of a mark in the shaft rotation in forward direction (falling edge in reverse).
    // Can be called while run() is in progress.
    // Is ISR-/thread- safe.
    virtual void signalShaftEncoderMarkStart();

    // Call when given user signal that valve has been fitted (ie is fully on).
    // Can be called while run() is in progress.
    // Is ISR-/thread- safe.
    void signalValveFitted();

    // Set target % open.
    // Can optionally be 'lazy' eg move more slowly or avoid tiny movements entirely.
    void setTargetPercentOpen(uint8_t newTargetPC, bool beLazy = false) { targetPC = min(newTargetPC, 100); lazy = beLazy; }

    // Used to run motor, adjust state, etc for up to specified maximum number of milliseconds.
    // Returns true if more work remaining to get into target state.
    bool run(uint16_t maxms, HardwareMotorDriverInterface &driver);

    // Returns true iff not (re)calibrating/(re)initialising/(re)syncing.
    // Initially false until power-up and at least initial calibration are complete.
    bool isCalibrated() const { return((state > (uint8_t)initCalibrating) && (0 != clicksFullTravel)); }

    // True iff power-up initialisation (eg including allowing user to fit to valve base) is done.
    bool isPowerUpDone() const { return(state >= (uint8_t)motorNormal); }

    // Get current motor drive status (off else direction of running).
    HardwareMotorDriverInterface::motor_drive getMotorDriveStatus() const { return((HardwareMotorDriverInterface::motor_drive) motorDriveStatus); }
  };

#if defined(LOCAL_TRV) && defined(DIRECT_MOTOR_DRIVE_V1)
// Implementation for V1 motor.
// Usually not instantaited except within ValveMotorDirectV1.
// Creating multiple instances almost certaintly a BAD IDEA.
class ValveMotorDirectV1HardwareDriver : public HardwareMotorDriverInterface
  {
  public:
    // Call to actually run/stop low-level motor.
    // May take as much as 200ms eg to change direction.
    // Stopping (removing power) should typically be very fast, << 100ms.
    virtual void motorRun(motor_drive dir);

    // Enable/disable end-stop detection and shaft-encoder.
    // Disabling should usually forces the motor off,
    // with a small pause for any residual movement to complete.
    virtual void enableFeedback(bool enable, HardwareMotorDriverInterfaceCallbackHandler &callback);

    // If true then enableFeedback(true) needs to be called in a fairly tight loop
    // while the motor is running and for a short while after
    // to capture end-stop hits, etc.
    // Always true for this driver.
    virtual bool needsPoll() const { return(true); }
  };

// Actuator/driver for direct local (radiator) valve motor control.
class ValveMotorDirectV1 : public AbstractRadValve
  {
  private:
//    CurrentSenseValveMotorDirect logic;

  protected:
    // Turn motor off, or on in a given drive direction.
    // This routine is very careful to avoid setting outputs into any illegal/'bad' state.
    // Sets flags accordingly.
    // Does not provide any monitoring of stall, position encoding, etc.
    // May take significant time (~150ms) to gently stop motor.
//    void motorDrive(motor_drive dir) { logic.setMotorDrive(dir); }

  public:
    // Regular poll/update.
    virtual uint8_t read();

//    // Handle simple interrupt.
//    // Fast and ISR (Interrupt Service Routines) safe.
//    // Returns true if interrupt was successfully handled and cleared
//    // else another interrupt handler in the chain may be called
//    // to attempt to clear the interrupt.
//    virtual bool handleInterruptSimple();

    // Minimally wiggles the motor to give tactile feedback and/or show to be working.
    // Does not itself track movement against shaft encoder, etc, or check for stall.
    // May take a significant fraction of a second.
    // Finishes with the motor turned off.
    void wiggle();

//#if defined(ALT_MAIN_LOOP) && defined(DEBUG)
//  // Drive motor back and forth (toggle direction each call) just for testing/fun.
//  void flip();
//#endif
  };
// Singleton implementation/instance.
extern ValveMotorDirectV1 ValveDirect;
#endif




#endif
