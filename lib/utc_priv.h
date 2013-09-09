/*
**  FACILITY:   libutc
**
**  ABSTRACT:   libutc private definitions
**
**  MODULE DESCRIPTION:
**
**      ...
**
**  AUTHOR:     Tim Sneddon
**
**  Copyright (c) 2013, Endless Software Solutions
**
**  libutc is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  libutc is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
**
**  CREATION DATE:   09-SEP-2013
**
**  MODIFICATION HISTORY
**
**      09-SEP-2013  V1.0    Sneddon    Initial coding.
**--
*/
#ifndef utc_priv_h__
#define utc_priv_h__
#include "config.h"
#include <limits.h>
#include <sys/time.h>
#include <time.h>
#include <utc.h>
#include "utc_types.h"

/*
 * Conversion factors : Units in 100 nanoseconds
 */
#define K_100NS_PER_SEC (10000000)
#define K_100NS_PER_MS  (10000)
#define K_100NS_PER_US  (10)

/*
 * One billion 10**9 as a constant
 */
#define K_ONE_BILLION (1000000000)

/*
 * Infinite inaccuracy - all 48 bits are 1's
 */
#define K_INFINITE_INACC_LO 0xFFFFFFFFUL        /* low 32 bits all 1s */
#define K_INFINITE_INACC_HI 0x0000FFFF          /* high 16 bits all 1s */

/* control prog protocol number supported
 */
#define K_CTL_PROT_VERSION      1       /* CP to TS protocol version */

/*
 * Version numbers
 *
 * For the released product, the protocol version becomes 1.0 and the
 * test protocol version becomes 0.5.
 */
#define K_PROT_VERSION_MAJOR      1    /* packet protocol major version # */
#define K_PROT_VERSION_MINOR      0    /* packet protocol minor version # */

#define K_TEST_PROT_VERSION_MAJOR 0    /* packet protocol major version # */
#define K_TEST_PROT_VERSION_MINOR 5    /* packet protocol minor version # */

#define K_PROT_VERSION_MINMAJOR   1    /* minimum major version supported */

#define K_BINTIME_VERSION         1    /* DTSS Binary Time Format version */

/*
 * TIME DATA TYPES
 */


/*
 * UTC time in 100 naonsecond units.  This is defined in terms of Bits64
 * so we can do arithmetic involving utcs, tdfs, and inaccuracies without
 * doing explicit type conversion or memory copies into variables of the
 * appropriate types.
 */
typedef unsigned64 UTCValue;

/*
 * Inaccuracy is also expresed as an intergral number of 100ns units.
 * All one's in the inaccuracy field denotes an inaccuracy of infinity.
 * Unknown inaccuracies or inaccuracies greater than 48-bits are regarded
 * as infinite.  It is a 48-bit integer.
 */
typedef unsigned48 Inaccuracy;

/*
 * Define these all using the same structure tag so we can do arithmetic with
 * mixed types without having to do casting or memory copies.  This is
 * needed for the inaccuracy calculation.
 *
 * Note that UTCValue is also defined in terms of Bits64.
 */
typedef unsigned64      ExtTDF, ExtInacc;

#endif /* utc_priv_h__ */
