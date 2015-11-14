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
 Security support for OpenTRV.
 */

#include <util/crc16.h>

#include "Security.h"

#include "Power_Management.h"


//// Get the current basic ßstats transmission level (for data outbound from this node).
//// May not exactly match enumerated levels; use inequalities.
//// Not thread-/ISR- safe.
//OTV0P2BASE::stats_TX_level getStatsTXLevel() { return((OTV0P2BASE::stats_TX_level)eeprom_read_byte((uint8_t *)V0P2BASE_EE_START_STATS_TX_ENABLE)); }

