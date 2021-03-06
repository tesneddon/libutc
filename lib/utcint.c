/*
**  FACILITY:   libutc
**
**  ABSTRACT:	UTC internal routines
**
**  MODULE DESCRIPTION:
**
**
**  AUTHOR:	Tim Sneddon <tsneddon@endlesssoftware.com.au>
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
**  CREATION DATE:   07-OCT-2013
**
**  MODIFICATION HISTORY
**
**      07-OCT-2013  V1.0    Sneddon	Initial coding.
**--
*/
#include <string.h>
#include "utc_priv.h"

/*
**  Forward declarations
*/

    int utc_mkcomptime(utc_t *utc, UTCValue *timevalue, UTCValue *inaccvalue,
		       long tdf);


/*
 *++
 *  utc_mkcomptime()
 *
 *  Functional Description:
 *
 *      Converts components into a 128-bit UTC time.
 *
 *  Inputs:
 *
 *      timevalue - pointer to timespecs to provide time component of utc.
 *      inaccvalue - pointer to timespecs to provide inaccuracy component
 *                   (if pointer is null, assume infinite iaccuracy)
 *      tdf  - tdf to place in 128-bit UTC time.
 *
 *  Implicit Inputs:
 *
 *
 *  Outputs:
 *
 *      utc - pointer to 128-bit time resulting from components
 *
 *  Implicit Outputs:
 *
 *
 *  Value Returned:
 *
 *      0 success, -1 failure
 *
 *  Side Effects:
 *
 *
 *--
 */
int utc_mkcomptime(utc_t *utc,
		   UTCValue *timevalue,
		   UTCValue *inaccvalue,
		   long tdf) {

    struct UTC autc;
    UTCValue ainacc;

    if (inaccvalue == NULL || (IsInfiniteInacc(inaccvalue))) {
        UTCassign (&ainacc, K_INFINITE_INACC_LO, K_INFINITE_INACC_HI);
    } else {
        ainacc = *inaccvalue;
    }

#if (BYTE_ORDER == LITTLE_ENDIAN)
    autc.endian.little.flags = ((tdf / SECS_PER_MIN) >> 8) & 0xf |
                               (K_BINTIME_VERSION << VERSION_SHIFT) |
                               LITTLE_ENDIAN_FLAG;
    autc.endian.little.tdflo = (tdf / SECS_PER_MIN) & 0xff;
#if LONG_BIT >= 64
    autc.endian.little.inacclo = (unsigned int) (ainacc & 0x0ffffffff);
    autc.endian.little.inacchi =
		(unsigned short int)((ainacc & 0x0ffff00000000) >> 32);
    autc.endian.little.time = *timevalue;
#else   /* LONG_BIT */
    autc.endian.little.inacclo = ainacc.lo;
    autc.endian.little.inacchi = ainacc.hi;
    autc.endian.little.timelo = timevalue->lo;
    autc.endian.little.timehi = timevalue->hi;
#endif  /* LONG_BIT */
#endif  /* (BYTE_ORDER == LITTLE_ENDIAN) */

#if (BYTE_ORDER == BIG_ENDIAN)
    autc.endian.big.flags = ((tdf / SECS_PER_MIN) & 0xf) |
                                (K_BINTIME_VERSION << VERSION_SHIFT) |
                                BIG_ENDIAN_FLAG;
    autc.endian.big.tdfhi = (tdf / SECS_PER_MIN) >> 4;
#if LONG_BIT >= 64
    autc.endian.big.inacchi = (unsigned int) (ainacc & 0x0ffffffff);
    autc.endian.big.inacclo =
		(unsigned short int)((ainacc &0x0ffff00000000) >> 32);
    autc.endian.big.time = *timevalue;
#else   /* LONG_BIT */
    autc.endian.big.inacchi = ainacc.hi;
    autc.endian.big.inaccmid = ainacc.lo >> 16;
    autc.endian.big.inacclo = ainacc.lo;
    autc.endian.big.timehi = timevalue->hi;
    autc.endian.big.timelo = timevalue->lo;
#endif  /* LONG_BIT */
#endif  /* (BYTE_ORDER == BIG_ENDIAN) */

    memcpy(utc, &autc, sizeof(utc_t));

    return 0;
} /* utc_mkcomptime */
