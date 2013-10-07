/*
**  FACILITY:   libutc
**
**  ABSTRACT:	UTC make routines
**
**  MODULE DESCRIPTION:
**
**	This module contains routines that build UTC timestamps from other
**  sources, like UNIX or OpenVMS system time.
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
**  CREATION DATE:   15-AUG-2013
**
**  MODIFICATION HISTORY
**
**      15-AUG-2013  V1.0    Sneddon	Initial coding.
**--
*/
#include <string.h>
#include "utc_priv.h"

/*
**  Forward declarations
*/

    int utc_mkbintime(utc_t *utc, timespec_t *timesp, timespec_t *inaccsp,
		      long tdf);
    int utc_mkgmtime(utc_t *utc, struct tm *timetm, long tns,
                     struct tm *inacctim, long ins);

/*
**++
**  utc_mkbintime()
**
**  Functional Description:
**
**      Converts timespecs into a 128-bit UTC time.
**
**  Inputs:
**
**      timesp - pointer to timespecs to provide time component of utc.
**      inaccsp - pointer to timespecs to provide inaccuracy component
**      tdf  - tdf, in seconds east of gmt, to place in 128-bit UTC time.
**
**  Implicit Inputs:
**
**
**  Outputs:
**
**      utc - pointer to 128-bit time resulting from timespecs.
**
**  Implicit Outputs:
**
**  Value Returned:
**
**      0 success, -1 failure
**
**  Side Effects:
**
**
**--
*/
int utc_mkbintime(utc_t *utc,
		  timespec_t *timesp,
		  timespec_t *inaccsp,
		  long tdf) {

    UTCValue timevalue, inaccvalue;

    if (inaccsp == NULL || (long)inaccsp->tv_sec < 0) {
        UTCassign (&inaccvalue, K_INFINITE_INACC_LO, K_INFINITE_INACC_HI);
    } else {
        uemul((unsigned long)inaccsp->tv_sec, K_100NS_PER_SEC,
              &inaccvalue);
        UTCiAdd(&inaccvalue, ((inaccsp->tv_nsec + 99)/100),
                &inaccvalue);
    }

    emul((long)timesp->tv_sec, K_100NS_PER_SEC, &timevalue);
    UTCiAdd(&timevalue, ((timesp->tv_nsec + 50)/100), &timevalue);
    UTCadd(&timevalue, &diff_UNIX_UTC_ticks, &timevalue);

    return utc_mkcomptime(utc, &timevalue, &inaccvalue, tdf);
} /* utc_mkbintime */

/*
 *++
 *  utc_mkgmtime()
 *
 *  Functional Description:
 *
 *      Converts a GMT tm struct and nanoseconds into an 128-bit UTC time.
 *
 *  Inputs:
 *
 *      timetm - pointer to tm struct with time component of utc.
 *      tns - longword of nanosecond within second
 *      inacctm - pointer to tm struct with inaccuracy component
 *      ins - longword of inacc nanosecond
 *
 *  Implicit Inputs:
 *
 *
 *  Outputs:
 *
 *      utc - pointer to 128-bit time to split into tm structs
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
int utc_mkgmtime(utc_t *utc,
    	    	 struct tm *timetm,
    	    	 long tns,
    	    	 struct tm *inacctm,
    	    	 long ins) {

    UTCValue timevalue, inaccvalue, secTemp;

    mergeinacc(inacctm, ins, &inaccvalue);

    if (mergetime(timetm, tns, &timevalue, &secTemp) < 0)
        return -1;

    return utc_mkcomptime(utc, &timevalue, &inaccvalue, 0L);
} /* utc_mkgmtime */
