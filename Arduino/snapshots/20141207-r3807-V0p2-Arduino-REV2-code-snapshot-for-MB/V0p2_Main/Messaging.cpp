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

Author(s) / Copyright (s): Damon Hart-Davis 2014
*/

/*
 Generic messaging support for OpenTRV.
 */

#include <util/atomic.h>

#include "Messaging.h"
#include "EEPROM_Utils.h"
#include "PRNG.h"
#include "Power_Management.h"
#include "Security.h"
#include "Serial_IO.h"

#ifdef USE_MODULE_FHT8VSIMPLE
#include "FHT8V_Wireless_Rad_Valve.h"
#endif

//// Update 'C2' 8-bit CRC with next byte.
//// Usually initialised with 0xff.
//// Should work well from 10--119 bits (2--~14 bytes); best 27-50, 52, 56-119 bits.
//// See: http://users.ece.cmu.edu/~koopman/roses/dsn04/koopman04_crc_poly_embedded.pdf
//// Also: http://en.wikipedia.org/wiki/Cyclic_redundancy_check
//#define C2_POLYNOMIAL 0x97
//uint8_t crc8_C2_update(uint8_t crc, const uint8_t datum)
//  {
//  crc ^= datum;
//  for(uint8_t i = 0; ++i <= 8; )
//    {
//    if(crc & 0x80)
//      { crc = (crc << 1) ^ C2_POLYNOMIAL; }
//    else
//      { crc <<= 1; }
//    }
//  return(crc);
//  }

/**Update 7-bit CRC with next byte; result always has top bit zero.
 * Polynomial 0x5B (1011011, Koopman) = (x+1)(x^6 + x^5 + x^3 + x^2 + 1) = 0x37 (0110111, Normal)
 * <p>
 * Should maybe initialise with 0x7f.
 * <p>
 * See: http://users.ece.cmu.edu/~koopman/roses/dsn04/koopman04_crc_poly_embedded.pdf
 * <p>
 * Should detect all 3-bit errors in up to 7 bytes of payload,
 * see: http://users.ece.cmu.edu/~koopman/crc/0x5b.txt
 * <p>
 * For 2 or 3 byte payloads this should have a Hamming distance of 4 and be within a factor of 2 of optimal error detection.
 * <p>
 * TODO: provide table-driven optimised alternative,
 *     eg see http://www.tty1.net/pycrc/index_en.html
 */
uint8_t crc7_5B_update(uint8_t crc, const uint8_t datum)
    {
    for(uint8_t i = 0x80; i != 0; i >>= 1)
        {
        bool bit = (0 != (crc & 0x40));
        if(0 != (datum & i)) { bit = !bit; }
        crc <<= 1;
        if(bit) { crc ^= 0x37; }
        }
    return(crc & 0x7f);
    }





// Return true if header/structure and CRC looks valid for (3-byte) buffered stats payload.
bool verifyHeaderAndCRCForTrailingMinimalStatsPayload(uint8_t const *const buf)
  {
  return((MESSAGING_TRAILING_MINIMAL_STATS_HEADER_MSBS == ((buf[0]) & MESSAGING_TRAILING_MINIMAL_STATS_HEADER_MASK)) && // Plausible header.
         (0 == (buf[1] & 0x80)) && // Top bit is clear on this byte also.
         (buf[2] == crc7_5B_update(buf[0], buf[1]))); // CRC validates, top bit implicitly zero.
  }

// Store minimal stats payload into (2-byte) buffer from payload struct (without CRC); values are coerced to fit as necessary..
//   * payload  must be non-null
// Used for minimal and full packet forms,
void writeTrailingMinimalStatsPayloadBody(uint8_t *buf, const trailingMinimalStatsPayload_t *payload)
  {
#ifdef DEBUG
  if(NULL == payload) { panic(); }
#endif
  // Temperatures coerced to fit between MESSAGING_TRAILING_MINIMAL_STATS_TEMP_BIAS (-20C) and 0x7ff_MESSAGING_TRAILING_MINIMAL_STATS_TEMP_BIAS (107Cf).
#if MESSAGING_TRAILING_MINIMAL_STATS_TEMP_BIAS > 0
#error MESSAGING_TRAILING_MINIMAL_STATS_TEMP_BIAS must be negative
#endif
  const int16_t bitmask = 0x7ff;
  const int16_t minTempRepresentable = MESSAGING_TRAILING_MINIMAL_STATS_TEMP_BIAS;
  const int16_t maxTempRepresentable = bitmask + MESSAGING_TRAILING_MINIMAL_STATS_TEMP_BIAS;
#if 0 && defined(DEBUG)
  DEBUG_SERIAL_PRINT_FLASHSTRING("payload->tempC16: ");
  DEBUG_SERIAL_PRINTFMT(payload->tempC16, DEC);
  DEBUG_SERIAL_PRINT_FLASHSTRING(" min=");
  DEBUG_SERIAL_PRINTFMT(minTempRepresentable, DEC);
  DEBUG_SERIAL_PRINT_FLASHSTRING(" max=");
  DEBUG_SERIAL_PRINTFMT(maxTempRepresentable, DEC);
  DEBUG_SERIAL_PRINTLN();
#endif
  int16_t temp16Cbiased = payload->tempC16;
  if(temp16Cbiased < minTempRepresentable) { temp16Cbiased = minTempRepresentable; }
  else if(temp16Cbiased > maxTempRepresentable) { temp16Cbiased = maxTempRepresentable; }
  temp16Cbiased -= MESSAGING_TRAILING_MINIMAL_STATS_TEMP_BIAS; // Should now be strictly positive.
#if 0 && defined(DEBUG)
  DEBUG_SERIAL_PRINT_FLASHSTRING("temp16Cbiased: ");
  DEBUG_SERIAL_PRINTFMT(temp16Cbiased, DEC);
  DEBUG_SERIAL_PRINTLN();
#endif
  const uint8_t byte0 = MESSAGING_TRAILING_MINIMAL_STATS_HEADER_MSBS | (payload->powerLow ? 0x10 : 0) | (temp16Cbiased & 0xf);
  const uint8_t byte1 = (uint8_t) (temp16Cbiased >> 4);
  buf[0] = byte0;
  buf[1] = byte1;
#if 0 && defined(DEBUG)
  for(uint8_t i = 0; i < 2; ++i) { if(0 != (buf[i] & 0x80)) { panic(); } } // MSBits should be clear.
#endif
  }

// Store minimal stats payload into (3-byte) buffer from payload struct and append CRC; values are coerced to fit as necessary..
//   * payload  must be non-null
void writeTrailingMinimalStatsPayload(uint8_t *buf, const trailingMinimalStatsPayload_t *payload)
  {
  writeTrailingMinimalStatsPayloadBody(buf, payload);
  buf[2] = crc7_5B_update(buf[0], buf[1]);
#if 0 && defined(DEBUG)
  for(uint8_t i = 0; i < 3; ++i) { if(0 != (buf[i] & 0x80)) { panic(); } } // MSBits should be clear.
#endif
  }

// Extract payload from valid (3-byte) header+payload+CRC into payload struct; only 2 bytes are actually read.
// Input bytes (eg header and check value) must already have been validated.
void extractTrailingMinimalStatsPayload(const uint8_t *const buf, trailingMinimalStatsPayload_t *const payload)
  {
#ifdef DEBUG
  if(NULL == payload) { panic(); }
#endif
  payload->powerLow = (0 != (buf[0] & 0x10));
  payload->tempC16 = ((((int16_t) buf[1]) << 4) | (buf[0] & 0xf)) + MESSAGING_TRAILING_MINIMAL_STATS_TEMP_BIAS;
  }


// Count of dropped inbound stats message due to insufficient queue space.
// Must only be accessed under a lock (ATOMIC_BLOCK).
static uint16_t inboundStatsQueueOverrun = 0;

// Get count of dropped inbound stats messages due to insufficient queue space.
uint16_t getInboundStatsQueueOverrun()
  {
  ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
    { return(inboundStatsQueueOverrun); }
  }


// Last JSON (\0-terminated) stats record received, or with first byte \0 if none.
// Should only be accessed under a lock for thread safety.
static /* volatile */ char jsonStats[MSG_JSON_MAX_LENGTH + 1];

// Record stats (local or remote) in JSON (ie non-empty, {}-surrounded, \0-terminated text) format.
// If secure is true then this message arrived over a secure channel.
// The supplied buffer's content is not altered.
// The supplied JSON should already have been somewhat validated.
// Is thread/ISR-safe and moderately fast (though will require a data copy).
// May be backed by a finite-depth queue, even zero-length (ie discarding); usually holds just one item.
void recordJSONStats(bool secure, const char *json)
  {
#if 1 && defined(DEBUG)
  if(NULL == json) { panic(); }
  if('\0' == *json) { panic(); }
#endif
  ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
    {
    if('\0' != *jsonStats) { ++inboundStatsQueueOverrun; } // Dropped a frame.
    // Atomically overwrite existing buffer with new non-empty stats message.
    strncpy(jsonStats, json, MSG_JSON_MAX_LENGTH+1);
    // Drop over-length message,
    if('\0' != jsonStats[sizeof(jsonStats) - 1]) { *jsonStats = '\0'; }
    }
  }

// Gets (and clears) the last JSON record received, if any,
// filling in the supplied buffer
// else leaving it starting with '\0' if none available.
// The buffer must be at least MSG_JSON_MAX_LENGTH+1 chars.
void getLastJSONStats(char *buf)
  {
#if 1 && defined(DEBUG)
  if(NULL == buf) { panic(); }
#endif
  ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
    {
    if('\0' == *jsonStats)
      { *buf = '\0'; } // No message available.
    else
      {
      // Copy the message to the receiver.
      strcpy(buf, jsonStats);
      // Clear the buffer.
      *jsonStats = '\0';
      }
    }
  }


// Last core stats record received, or with no ID set if none.
// Should only be accessed under a lock for thread safety.
static /* volatile */ FullStatsMessageCore_t coreStats; // Start up showing no record set.

#if defined(ALLOW_MINIMAL_STATS_TXRX)
// Record minimal incoming stats from given ID (if each byte < 100, then may be FHT8V-compatible house code).
// Is thread/ISR-safe and fast.
// May be backed by a finite-depth queue, even zero-length (ie discarding); usually holds just one item.
void recordMinimalStats(const bool secure, const uint8_t id0, const uint8_t id1, const trailingMinimalStatsPayload_t * const payload)
  {
#if 0 && defined(DEBUG)
  if(NULL == payload) { panic(); }
#endif
   ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
    {
    if(coreStats.containsID) { ++inboundStatsQueueOverrun; } // Dropped a frame.
    clearFullStatsMessageCore(&coreStats);
    coreStats.id0 = id0;
    coreStats.id1 = id1;
    coreStats.containsID = true;
    memcpy((void *)&coreStats.tempAndPower, payload, sizeof(coreStats.tempAndPower));
    coreStats.containsTempAndPower = true;
    }
  }
#endif

// Record core incoming stats; ID must be set as a minimum.
// Is thread/ISR-safe and fast.
// May be backed by a finite-depth queue, even zero-length (ie discarding); usually holds just one item.
void recordCoreStats(const bool secure, const FullStatsMessageCore_t * const stats)
  {
#if 0 && defined(DEBUG)
  if(NULL == payload) { panic(); }
#endif  // TODO
   if(!stats->containsID) { return; } // Ignore if no ID.
   ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
    {
    if(coreStats.containsID) { ++inboundStatsQueueOverrun; } // Dropped a frame.
    memcpy((void *)&coreStats, stats, sizeof(coreStats));
    }
  }

// Gets (and clears) the last core stats record received, if any, returning true and filling in the stats struct.
// If no minimal stats record has been received since the last call then the ID will be absent and the rest undefined.
void getLastCoreStats(FullStatsMessageCore_t *stats)
  {
#if 0 && defined(DEBUG)
  if(NULL == stats) { panic(); }
#endif
  ATOMIC_BLOCK (ATOMIC_RESTORESTATE)
    {
    if(!coreStats.containsID)
      { stats->containsID = false; } // Nothing there; just clear containsID field in response for speed.
    else
      {
      // Copy everything.
      memcpy(stats, (void *)&coreStats, sizeof(*stats));
      coreStats.containsID = false; // Mark stats as read.
      }
    }
  }



#if defined(SUPPORT_TEMP_TX)
#if !defined(enableTrailingMinimalStatsPayload)
// Returns true if an unencrypted minimal trailing static payload and similar (eg bare stats transmission) is permitted.
// True if the TX_ENABLE value is no higher than stTXmostUnsec.
// Some filtering may be required even if this is true.
// TODO: allow cacheing in RAM for speed.
bool enableTrailingMinimalStatsPayload() { return(eeprom_read_byte((uint8_t *)EE_START_STATS_TX_ENABLE) <= stTXmostUnsec); }
#endif
#endif



// Coerce any ID bytes to valid values if unset (0xff) or if forced,
// by filling with valid values (0x80--0xfe) from decent entropy gathered on the fly.
// Will moan about invalid values and return false but not attempt to reset,
// eg in case underlying EEPROM cell is worn/failing.
// Returns true iff all values good.
bool ensureIDCreated(const bool force)
  {
  bool allGood = true;
  for(uint8_t i = 0; i < EE_LEN_ID; ++i)
    {
    uint8_t * const loc = i + (uint8_t *)EE_START_ID;
    if(force || (0xff == eeprom_read_byte(loc))) // Byte is unset or change is being forced.
        {
        serialPrintAndFlush(F("Setting ID byte "));
        serialPrintAndFlush(i);
        serialPrintAndFlush(F(" ... "));
        const uint8_t envNoise = ((i & 1) ? TemperatureC16.get() : AmbLight.get());
        for( ; ; )
          {
          // Try to make decently-randomised 'unique-ish' ID with mixture of sources.
          // Is not confidential, and will be transmitted in the clear.
          // System will typically not have been running long when this is invoked.
          const uint8_t newValue = 0x80 | (getSecureRandomByte() ^ envNoise);
          if(0xff == newValue) { continue; } // Reject unusable value.
          eeprom_smart_update_byte(loc, newValue);
          serialPrintAndFlush(newValue, HEX);
          break;
          }
        serialPrintlnAndFlush();
        }
    // Validate.
    const uint8_t v2 = eeprom_read_byte(loc);
    if(!validIDByte(v2))
        {
        allGood = false;
        serialPrintAndFlush(F("Invalid ID byte "));
        serialPrintAndFlush(i);
        serialPrintAndFlush(F(" ... "));
        serialPrintAndFlush(v2, HEX);
        serialPrintlnAndFlush();
        }
     }
  return(allGood);
  }


// Send core/common 'full' stats message.
//   * content contains data to be sent in the message; must be non-null
// Note that up to 7 bytes of payload is optimal for the CRC used.
// If successful, returns pointer to terminating 0xff at end of message.
// Returns null if failed (eg because of bad inputs or insufficient buffer space);
// part of the message may have have been written in this case and in particular the previous terminating 0xff may have been overwritten.
uint8_t *encodeFullStatsMessageCore(uint8_t * const buf, const uint8_t buflen, const stats_TX_level secLevel, const bool secureChannel,
    const FullStatsMessageCore_t * const content)
  {
  if(NULL == buf) { return(NULL); } // Could be an assert/panic instead at a pinch.
  if(NULL == content) { return(NULL); } // Could be an assert/panic instead at a pinch.
  if(secureChannel) { return(NULL); } // TODO: cannot create secure message yet.
//  if(buflen < FullStatsMessageCore_MIN_BYTES_ON_WIRE+1) { return(NULL); } // Need space for at least the shortest possible message + terminating 0xff.
//  if(buflen < FullStatsMessageCore_MAX_BYTES_ON_WIRE+1) { return(NULL); } // Need space for longest possible message + terminating 0xff.

  // Compute message payload length (excluding CRC and terminator).
  // Fail immediately (return NULL) if not enough space for message content.
  const uint8_t payloadLength =
      1 + // Initial header.
      (content->containsID ? 2 : 0) +
      (content->containsTempAndPower ? 2 : 0) +
      1 + // Flags header.
      (content->containsAmbL ? 1 : 0);
  if(buflen < payloadLength + 2)  { return(NULL); }

  // Validate some more detail.
  // ID
  if(content->containsID)
    {
    if((content->id0 == (uint8_t)0xff) || (content->id1 == (uint8_t)0xff)) { return(NULL); } // ID bytes cannot be 0xff.
    if((content->id0 & 0x80) != (content->id1 & 0x80)) { return(NULL); } // ID top bits don't match.
    }
  // Ambient light.
  if(content->containsAmbL)
    {
    if((content->ambL == 0) || (content->ambL == (uint8_t)0xff)) { return(NULL); } // Forbidden values.
    }

  // WRITE THE MESSAGE!
  // Pointer to next byte to write in message.
  register uint8_t *b = buf;

  // Construct the header.
  // * byte 0 :  |  0  |  1  |  1  |  1  |  R0 | IDP | IDH | SEC |   header, 1x reserved 0 bit, ID Present, ID High, SECure
//#define MESSAGING_FULL_STATS_HEADER_MSBS 0x70
//#define MESSAGING_FULL_STATS_HEADER_MASK 0xf0
//#define MESSAGING_FULL_STATS_HEADER_BITS_ID_PRESENT 4
//#define MESSAGING_FULL_STATS_HEADER_BITS_ID_HIGH 2
//#define MESSAGING_FULL_STATS_HEADER_BITS_ID_SECURE 1
  const uint8_t header = MESSAGING_FULL_STATS_HEADER_MSBS |
      (content->containsID ? MESSAGING_FULL_STATS_HEADER_BITS_ID_PRESENT : 0) |
      ((content->containsID && (0 != (content->id0 & 0x80))) ? MESSAGING_FULL_STATS_HEADER_BITS_ID_HIGH : 0) |
      0; // TODO: cannot do secure messages yet.
  *b++ = header;
 
  // Insert ID if requested.
  if(content->containsID)
    {
    *b++ = content->id0 & 0x7f;
    *b++ = content->id1 & 0x7f;
    }

  // Insert basic temperature and power status if requested.
  if(content->containsTempAndPower)
    {
    writeTrailingMinimalStatsPayloadBody(b, &(content->tempAndPower));
    b += 2;
    }
 
  // Always insert flags header , and downstream optional values.
// Flags indicating which optional elements are present:
// AMBient Light, Relative Humidity %.
// OC1/OC2 = Occupancy: 00 not disclosed, 01 probably, 10 possibly, 11 not occupied recently.
// IF EXT is 1 a futher flags byte follows.
// * byte b+2: |  0  |  1  |  1  | EXT | ABML| RH% | OC1 | OC2 |   EXTension-follows flag, plus optional section flags.
//#define MESSAGING_FULL_STATS_FLAGS_HEADER_MSBS 0x60
//#define MESSAGING_FULL_STATS_FLAGS_HEADER_MASK 0xe0
//#define MESSAGING_FULL_STATS_FLAGS_HEADER_AMBL 8
//#define MESSAGING_FULL_STATS_FLAGS_HEADER_RHP 4
  // Omit occupancy data unless encoding for a secure channel or at a very permissive stats TX security level.
  const uint8_t flagsHeader = MESSAGING_FULL_STATS_FLAGS_HEADER_MSBS |
    (content->containsAmbL ? MESSAGING_FULL_STATS_FLAGS_HEADER_AMBL : 0) |
    ((secureChannel || (secLevel <= stTXalwaysAll)) ? (content->occ & 3) : 0);
  *b++ = flagsHeader;
  // Now insert extra fields as flagged.
  if(content->containsAmbL)
    { *b++ = content->ambL; }
  // TODO: RH% etc

  // Finish off message by computing and appending the CRC and then terminating 0xff (and return pointer to 0xff).
  // Assumes that b now points just beyond the end of the payload.
  uint8_t crc = MESSAGING_FULL_STATS_CRC_INIT; // Initialisation.
  for(const uint8_t *p = buf; p < b; ) { crc = crc7_5B_update(crc, *p++); }
  *b++ = crc;
  *b = 0xff;
#if 0 && defined(DEBUG)
  if(b - buf != payloadLength + 1) { panic(F("msg gen err")); }
#endif
  return(b);
  }

// Decode core/common 'full' stats message.
// If successful returns pointer to next byte of message, ie just after full stats message decoded.
// Returns null if failed (eg because of corrupt message data) and state of 'content' result is undefined.
// This will avoid copying into the result data (possibly tainted) that has arrived at an inappropriate security level.
//   * content will contain data decoded from the message; must be non-null
const uint8_t *decodeFullStatsMessageCore(const uint8_t * const buf, const uint8_t buflen, const stats_TX_level secLevel, const bool secureChannel,
    FullStatsMessageCore_t * const content)
  {
  if(NULL == buf) { return(NULL); } // Could be an assert/panic instead at a pinch.
  if(NULL == content) { return(NULL); } // Could be an assert/panic instead at a pinch.
  if(buflen < FullStatsMessageCore_MIN_BYTES_ON_WIRE)
    {
#if 0
    DEBUG_SERIAL_PRINT_FLASHSTRING("buf too small: ");
    DEBUG_SERIAL_PRINT(buflen);
    DEBUG_SERIAL_PRINTLN();
#endif
    return(NULL); // Not long enough for even a minimal message to be present...
    }

  // Conservatively clear the result completely.
  clearFullStatsMessageCore(content);

  // READ THE MESSAGE!
  // Pointer to next byte to read in message.
  register const uint8_t *b = buf;

  // Validate the message header and start to fill in structure.
  const uint8_t header = *b++;
  // Deonstruct the header.
  // * byte 0 :  |  0  |  1  |  1  |  1  |  R0 | IDP | IDH | SEC |   header, 1x reserved 0 bit, ID Present, ID High, SECure
//#define MESSAGING_FULL_STATS_HEADER_MSBS 0x70
//#define MESSAGING_FULL_STATS_HEADER_MASK 0xf0
//#define MESSAGING_FULL_STATS_HEADER_BITS_ID_PRESENT 4
//#define MESSAGING_FULL_STATS_HEADER_BITS_ID_HIGH 2
//#define MESSAGING_FULL_STATS_HEADER_BITS_ID_SECURE 1
  if(MESSAGING_FULL_STATS_HEADER_MSBS != (header & MESSAGING_FULL_STATS_HEADER_MASK)) { return(NULL); } // Bad header.
  if(0 != (header & MESSAGING_FULL_STATS_HEADER_BITS_ID_SECURE)) { return(NULL); } // TODO: cannot do secure messages yet.
  // Extract ID if present.
  const bool containsID = (0 != (header & MESSAGING_FULL_STATS_HEADER_BITS_ID_PRESENT));
  if(containsID)
    {
    content->containsID = true;
    const uint8_t idHigh = ((0 != (header & MESSAGING_FULL_STATS_HEADER_BITS_ID_HIGH)) ? 0x80 : 0);
    content->id0 = *b++ | idHigh;
    content->id1 = *b++ | idHigh;
    }

  // If next header is temp/power then extract it, else must be the flags header.
  if(MESSAGING_TRAILING_MINIMAL_STATS_HEADER_MSBS == (*b & MESSAGING_TRAILING_MINIMAL_STATS_HEADER_MASK))
    {
    if(0 != (0x80 & b[1])) { return(NULL); } // Following byte does not have msb correctly cleared.
    extractTrailingMinimalStatsPayload(b, &(content->tempAndPower));
    b += 2;
    content->containsTempAndPower = true;
    }

  // If next header is flags then extract it.
  // FIXME: risk of misinterpretting CRC.
  if(MESSAGING_FULL_STATS_FLAGS_HEADER_MSBS != (*b & MESSAGING_FULL_STATS_FLAGS_HEADER_MASK)) { return(NULL); } // Corrupt message.
  const uint8_t flagsHeader = *b++;
  content->occ = flagsHeader & 3;
  const bool containsAmbL = (0 != (flagsHeader & MESSAGING_FULL_STATS_FLAGS_HEADER_AMBL));
  if(containsAmbL)
    {
    const uint8_t ambL = *b++;
    if((0 == ambL) || (ambL == (uint8_t)0xff)) { return(NULL); } // Illegal value.
    content->ambL = ambL;
    content->containsAmbL = true;
    }

  // Finish off by computing and checking the CRC (and return pointer to just after CRC).
  // Assumes that b now points just beyond the end of the payload.
  uint8_t crc = MESSAGING_FULL_STATS_CRC_INIT; // Initialisation.
  for(const uint8_t *p = buf; p < b; ) { crc = crc7_5B_update(crc, *p++); }
  if(crc != *b++) { return(NULL); } // Bad CRC.

  return(b); // Point to just after CRC.
  }





// Returns true unless the buffer clearly does not contain a possible valid raw JSON message.
// This message is expected to be one object wrapped in '{' and '}'
// and containing only ASCII printable/non-control characters in the range [32,126].
// The message must be no longer than MSG_JSON_MAX_LENGTH excluding trailing null.
// This only does a quick validation for egregious errors.
bool quickValidateRawSimpleJSONMessage(const char * const buf)
  {
  if('{' != buf[0]) { return(false); }
  // Scan up to maximum length for terminating '}'.
  const char *p = buf + 1;
  for(int i = 1; i < MSG_JSON_MAX_LENGTH; ++i)
    {
    const char c = *p++;
    // With a terminating '}' (followed by '\0') the message is superficially valid.
    if(('}' == c) && ('\0' == *p)) { return(true); }
    // Non-printable/control character makes the message invalid.
    if((c < 32) || (c > 126)) { return(false); }
    // Premature end of message renders it invalid.
    if('\0' == c) { return(false); }
    }
  return(false); // Bad (unterminated) message.
  }

// Adjusts null-terminated text JSON message up to MSG_JSON_MAX_LENGTH bytes (not counting trailing '\0') for TX.
// Sets high-bit on final '}' to make it unique, checking that all others are clear.
// Computes and returns 0x5B 7-bit CRC in range [0,127]
// or 0xff if the JSON message obviously invalid and should not be TXed.
// The CRC is initialised with the initial '{' character.
// NOTE: adjusts content in place.
#define adjustJSONMsgForTXAndComputeCRC_ERR 0xff // Error return value.
uint8_t adjustJSONMsgForTXAndComputeCRC(char * const bptr)
  {
  // Do initial quick validation before computing CRC, etc,
  if(!quickValidateRawSimpleJSONMessage(bptr)) { return(adjustJSONMsgForTXAndComputeCRC_ERR); }
//  if('{' != *bptr) { return(adjustJSONMsgForTXAndComputeCRC_ERR); }
  bool seenTrailingClosingBrace = false;
  uint8_t crc = '{';
  for(char *p = bptr; *++p; ) // Skip first char ('{'); loop until '\0'.
    {
    const char c = *p;
//    if(c & 0x80) { return(adjustJSONMsgForTXAndComputeCRC_ERR); } // No high-bits should be set!
    if(('}' == c) && ('\0' == *(p+1)))
      {
      seenTrailingClosingBrace = true;
      const char newC = c | 0x80;
      *p = newC; // Set high bit.
      crc = crc7_5B_update(crc, (uint8_t)newC); // Update CRC.
      return(crc);
      }
    crc = crc7_5B_update(crc, (uint8_t)c); // Update CRC.
    }
  if(!seenTrailingClosingBrace) { return(adjustJSONMsgForTXAndComputeCRC_ERR); } // Missing ending '}'.
  return(crc);
  }

// IF DEFINED: allow raw ASCII JSON message terminated with '}' and '\0' in adjustJSONMsgForRXAndCheckCRC().
// This has no error checking other than none of the values straying out of the printable range.
// Only intended as a transitional measure!
//#define ALLOW_RAW_JSON_RX

// Extract/adjust raw RXed putative JSON message up to MSG_JSON_MAX_LENGTH chars.
// Returns length including bounding '{' and '}' iff message superficially valid
// (essentially as checked by quickValidateRawSimpleJSONMessage() for an in-memory message)
// and that the CRC matches as computed by adjustJSONMsgForTXAndComputeCRC(),
// else returns -1.
// Strips the high-bit off the final '}' and replaces the CRC with a '\0'
// iff the message appeared OK
// to allow easy handling with string functions.
//  * bptr  pointer to first byte/char (which must be '{')
//  * bufLen  remaining bytes in buffer starting at bptr
// NOTE: adjusts content in place iff the message appears to be valid JSON.
#define adjustJSONMsgForRXAndCheckCRC_ERR -1
int8_t adjustJSONMsgForRXAndCheckCRC(char * const bptr, const uint8_t bufLen)
  {
  if('{' != *bptr) { return(adjustJSONMsgForRXAndCheckCRC_ERR); }
#if 0 && defined(DEBUG)
  DEBUG_SERIAL_PRINT_FLASHSTRING("adjustJSONMsgForRXAndCheckCRC()... {");
#endif
  uint8_t crc = '{';
  // Scan up to maximum length for terminating '}'-with-high-bit.
  const uint8_t ml = min(MSG_JSON_MAX_LENGTH, bufLen);
  char *p = bptr + 1;
  for(int i = 1; i < ml; ++i)
    {
    const char c = *p++;
    crc = crc7_5B_update(crc, (uint8_t)c); // Update CRC.
#ifdef ALLOW_RAW_JSON_RX
    if(('}' == c) && ('\0' == *p))
      {
      // Return raw message as-is!
#if 0 && defined(DEBUG)
      DEBUG_SERIAL_PRINTLN_FLASHSTRING("} OK raw");
#endif
      return(i+1);
      }
#endif
    // With a terminating '}' (followed by '\0') the message is superficially valid.
    if((((char)('}' | 0x80)) == c) && (crc == (uint8_t)*p))
      {
      *(p - 1) = '}';
      *p = '\0'; // Null terminate for use as a text string.
#if 0 && defined(DEBUG)
      DEBUG_SERIAL_PRINTLN_FLASHSTRING("} OK with CRC");
#endif
      return(i+1);
      }
    // Non-printable/control character makes the message invalid.
    if((c < 32) || (c > 126))
      {
#if 0 && defined(DEBUG)
      DEBUG_SERIAL_PRINT_FLASHSTRING(" bad: char 0x");
      DEBUG_SERIAL_PRINTFMT(c, HEX);
      DEBUG_SERIAL_PRINTLN();
#endif
      return(adjustJSONMsgForRXAndCheckCRC_ERR);
      }
#if 0 && defined(DEBUG)
    DEBUG_SERIAL_PRINT(c);
#endif
    }
#if 0 && defined(DEBUG)
  DEBUG_SERIAL_PRINTLN_FLASHSTRING(" bad: unterminated");
#endif
  return(adjustJSONMsgForRXAndCheckCRC_ERR); // Bad (unterminated) message.
  }


// Print a single char to a bounded buffer; returns 1 if successful, else 0 if full.
size_t BufPrint::write(const uint8_t c)
  {
  if(size < capacity) { b[size++] = c; b[size] = '\0'; return(1); }
  return(0);
  }

// Returns true iff if a valid key for our subset of JSON.
// Rejects keys containing " or \ or any chars outside the range [32,126]
// to avoid having to escape anything.
bool isValidKey(const SimpleStatsKey key)
  {
  if(NULL == key) { return(false); } 
  for(const char *s = key; '\0' != *s; ++s)
    {
    const char c = *s;
    if((c < 32) || (c > 126) || ('"' == c) || ('\\' == c)) { return(false); }
    }
  return(true);
  }

// Returns pointer to stats tuple with given (non-NULL) key if present, else NULL.
// Does a simple linear search.
SimpleStatsRotationBase::DescValueTuple * SimpleStatsRotationBase::findByKey(const SimpleStatsKey key) const
  {
  for(int i = 0; i < nStats; ++i)
    {
    DescValueTuple * const p = stats + i;
    if(0 == strcmp(p->descriptor.key, key)) { return(p); }
    }
  return(NULL); // Not found.
  }

// Remove given stat and properties.
// True iff the item existed and was removed.
bool SimpleStatsRotationBase::remove(const SimpleStatsKey key)
  {
  DescValueTuple *p = findByKey(key);
  if(NULL == p) { return(false); }
  // If it needs to be removed and is not the last item
  // then move the last item down into its slot.
  const bool lastItem = ((p - stats) == (nStats - 1));
  if(!lastItem) { *p = stats[nStats-1]; }
  // We got rid of one!
  // TODO: possibly explicitly destroy/overwrite the removed one at the end.
  --nStats;
  return(true);
  }

// Create/update stat/key with specified descriptor/properties.
// The name is taken from the descriptor.
bool SimpleStatsRotationBase::putDescriptor(const GenericStatsDescriptor &descriptor)
  {
  if(!isValidKey(descriptor.key)) { return(false); }
  DescValueTuple *p = findByKey(descriptor.key);
  // If item already exists, update its properties.
  if(NULL != p) { p->descriptor = descriptor; }
  // Else if not yet at capacity then add this new item at the end.
  // Don't mark it as changed since its value may not yet be meaningful
  else if(nStats < capacity)
    {
    p = stats + (nStats++);
    *p = DescValueTuple();
    p->descriptor = descriptor;
    }
  // Else failed: no space to add a new item.
  else { return(false); }
  return(true); // OK
  }
    
// Create/update value for given stat/key.
// If properties not already set and not supplied then stat will get defaults.
// If descriptor is supplied then its key must match (and the descriptor will be copied).
// True if successful, false otherwise (eg capacity already reached).
bool SimpleStatsRotationBase::put(const SimpleStatsKey key, const int newValue)
  {
  if(!isValidKey(key)) { return(false); }

  DescValueTuple *p = findByKey(key);
  // If item already exists, update it.
  if(NULL != p)
    {
    // Update the value and mark as changed if changed.
    if(p->value != newValue)
      {
      p->value = newValue;
      p->flags.changed = true;
      }
    // Update done!
    return(true);
    }

  // If not yet at capacity then add this new item at the end.
  // Mark it as changed to prioritise seeing it in the JSON output.
  if(nStats < capacity)
    {
    p = stats + (nStats++);
    *p = DescValueTuple();
    p->value = newValue;
    p->flags.changed = true;
    // Copy descriptor .
    p->descriptor = GenericStatsDescriptor(key);
    // Addition of new field done!
    return(true);
    }

  return(false); // FAILED: full.
  }

#if defined(ALLOW_JSON_OUTPUT)
// Print an object field "name":value to the given buffer.
size_t SimpleStatsRotationBase::print(BufPrint &bp, const SimpleStatsRotationBase::DescValueTuple &s, bool &commaPending) const
  {
  size_t w = 0;
  if(commaPending) { w += bp.print(','); }
  w += bp.print('"');
  w += bp.print(s.descriptor.key); // Assumed not to need escaping in any way.
  w += bp.print('"');
  w += bp.print(':');
  w += bp.print(s.value);
  commaPending = true;
  return(w);
  }
#endif

#if defined(ALLOW_JSON_OUTPUT)
// Write stats in JSON format to provided buffer; returns a non-zero value if successful.
// Output starts with an "@" (ID) string field,
// then and optional count (if enabled),
// then the tracked stats as space permits,
// attempting to give priority to high-priority and changed values,
// allowing a potentially large set of values to my multiplexed over time
// into a constrained size/bandwidth message.
//
//   * buf  is the byte/char buffer to write the JSON to; never NULL
//   * bufSize is the capacity of the buffer starting at buf in bytes;
//       should be two (2) greater than the largest JSON output to be generates
//       to allow for a trailing null and one extra byte/char to ensure that the message is not over-large
//   * sensitivity  threshold below which (sensitive) stats will not be included; 0 means include everything
//   * maximise  if true attempt to maximise the number of stats squeezed into each frame,
//       potentially at the cost of signficant CPU time
//   * suppressClearChanged  if true then 'changed' flag for included fields is not cleared by this
//       allowing them to continue to be treated as higher priority
uint8_t SimpleStatsRotationBase::writeJSON(uint8_t *const buf, const uint8_t bufSize, const uint8_t sensitivity,
                                           const bool maximise, const bool suppressClearChanged)
  {
#ifdef DEBUG
  if(NULL == buf) { panic(0); } // Should never happen.
#endif
  // Minimum size is for {"@":""} plus null plus extra padding char/byte to check for overrun.
  if(bufSize < 10) { return(0); } // Failed.

  // Write/print to buffer passed in.
  BufPrint bp((char *)buf, bufSize);
  // Count of characters written to buffer.
  size_t w = 0;
  // True if field has been written and will need a ',' if another field is written.
  bool commaPending = false;

  // Start object.
  w += bp.print('{');

  // Write ID first.
  // If an explicit ID is supplied then use it
  // else compute it taking the housecode by preference if it is set.
  w += bp.print(F("\"@\":\""));

#ifdef USE_MODULE_FHT8VSIMPLE
  if(NULL != id) { w += bp.print(id); } // Value has to be 'safe' (eg no " nor \ in it).
  else
    {
    if(localFHT8VTRVEnabled())
      {
      const uint8_t hc1 = FHT8VGetHC1();
      const uint8_t hc2 = FHT8VGetHC2();
      w += bp.print(hexDigit(hc1 >> 4));
      w += bp.print(hexDigit(hc1));
      w += bp.print(hexDigit(hc2 >> 4));
      w += bp.print(hexDigit(hc2));
      }
    else
#endif
      {
      const uint8_t id1 = eeprom_read_byte(0 + (uint8_t *)EE_START_ID);
      const uint8_t id2 = eeprom_read_byte(1 + (uint8_t *)EE_START_ID);
      w += bp.print(hexDigit(id1 >> 4));
      w += bp.print(hexDigit(id1));
      w += bp.print(hexDigit(id2 >> 4));
      w += bp.print(hexDigit(id2));
      }
    }

  w += bp.print('"');
  commaPending = true;

  // Write count next iff enabled.
  if(c.enabled)
    {
    if(commaPending) { w += bp.print(','); commaPending = false; }
    w += bp.print(F("\"+\":"));
    w += bp.print(c.count);
    commaPending = true;
    }

  bool gotHiPri = false;
  uint8_t hiPriIndex = 0;
  bool gotLoPri = false;
  uint8_t loPriIndex = 0;
  if(nStats != 0)
    {
    // High-pri/changed stats.
    // Only do this on a portion of runs to let 'normal' stats get a look-in.
    // This happens on even-numbered runs (eg including the first, typically).
    if(0 == (c.count & 1))
      {
      uint8_t next = lastTXedHiPri;
      for(int i = nStats; --i >= 0; )
        {
        // Wrap around the end of the stats.
        if(++next >= nStats) { next = 0; }
        // Skip stat if too sensitive to include in this output.
        DescValueTuple &s = stats[next];
        if(sensitivity > s.descriptor.sensitivity) { continue; }
        // Skip stat if not changed or high-priority.
        if(!s.descriptor.highPriority && !s.flags.changed) { continue; }
        // Found suitable stat to include in output.
        hiPriIndex = next;
        gotHiPri = true;
        // Add to JSON output.

        w += print(bp, s, commaPending);
        break;
        }
      }

    // Insert normal-priority stats iff no high-priority one selected.
    // Rotate through all eligible stats round-robin,
    // adding one to the end of the current message if possible,
    // checking first the item indexed after the previous one sent.
    if(!gotHiPri)
      {
      uint8_t next = lastTXedLoPri;
      for(int i = nStats; --i >= 0; )
        {
        // Wrap around the end of the stats.
        if(++next >= nStats) { next = 0; }
        // Avoid re-trasmitting the very last thing TXed.
        if(lastTXed == next) { continue; }
        // Skip stat if too sensitive to include in this output.
        DescValueTuple &s = stats[next];
        if(sensitivity > s.descriptor.sensitivity) { continue; }
        // Found suitable stat to include in output.
        loPriIndex = next;
        gotLoPri = true;
        // Add to JSON output.
        w += print(bp, s, commaPending);
        break;
        }
      }
    }

  // TODO: maximise.

  // Terminate object.
  w += bp.print('}');
  if(w >= (size_t)(bufSize-1))
    {
    // Overrun, so failed/aborted.
    *buf = '\0';
    return(0);
    }
 
  // On successfully creating output, update some internal state including success count.
  ++c.count;
  // Remember which hi-pri/changed stat (if any) was just included in the output
  // and note it as no longer changed since last sent.
  if(gotHiPri)
    {
    lastTXed = lastTXedHiPri = hiPriIndex;
    if(!suppressClearChanged) { stats[hiPriIndex].flags.changed = false; }
    }
  // Remember which normal stat (if any) was just included in the output
  // and note it as no longer changed since last sent.
  if(gotLoPri)
    {
    lastTXed = lastTXedLoPri = loPriIndex;
    if(!suppressClearChanged) { stats[loPriIndex].flags.changed = false; }
    }

  return(w); // Success!
  }
#endif
