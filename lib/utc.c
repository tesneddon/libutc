/*
**  FACILITY:   libutc
**
**  ABSTRACT:   
**
**  MODULE DESCRIPTION:
**
**      ...
**
**  AUTHOR:     Tim Sneddon <tsneddon@endlesssoftware.com.au>
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
**      15-AUG-2013  V1.0    Sneddon    Initial coding.
**--
*/
#include "utc_priv.h"

/*
**  Forward declarations
*/

    int utc_bintime(timespec_t *timesp, timespec_t *inaccsp, long *tdf,
                    utc_t *utc);
    int utc_gettime(utc_t *utc);
    int utc_gmtime(struct tm *timetm, long *tns, struct tm *inacctm, long ins,
    	    	   utc_t *utc);


/*
 *++
 *  utc_bintime()
 *
 *  Functional Description:
 *
 *      Converts a 128-bit UTC time into timespecs
 *
 *  Inputs:
 *
 *      utc - pointer to 128-bit time to split into timespecs
 *
 *  Implicit Inputs:
 *
 *
 *  Outputs:
 *
 *      timesp - pointer to timespec to receive time component of utc.
 *      inaccsp - pointer to timespec to receive inaccuracy component
 *      tdf  - pointer to int to receive the tdf
 *
 *  Implicit Outputs:
 *
 *  Outputs:
 *
 *      timesp - pointer to timespec to receive time component of utc.
 *      inaccsp - pointer to timespec to receive inaccuracy component
 *      tdf  - pointer to int to receive the tdf
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
int utc_bintime( timespec_t *timesp, timespec_t *inaccsp, long *tdf, utc_t *utc)

{
    UTCValue timevalue, inaccvalue;
    unsigned long temp;
    register int i;

    if ((i = utc_comptime(&timevalue, &inaccvalue, tdf, utc)) < 0)
        return(i);

    if (inaccsp != NULL) {
        if (IsInfiniteInacc(&inaccvalue)) {
            inaccsp->tv_sec = inaccsp->tv_nsec = -1;
        } else {
            UTCiDiv(&inaccvalue, K_100NS_PER_SEC, &inaccvalue, &temp);
            inaccsp->tv_sec = UTClow(&inaccvalue);
            inaccsp->tv_nsec = temp*100;
        }
    }
    UTCadd(&timevalue, &diff_UTC_UNIX_ticks, &timevalue);
    UTCiDiv(&timevalue, K_100NS_PER_SEC, &timevalue, &temp);
    if ((long) temp < 0) {
        temp += K_100NS_PER_SEC;
        (UTClow(&timevalue))--;
    }
    if (timesp != NULL)
    {
        timesp->tv_sec = UTClow(&timevalue);
        timesp->tv_nsec = temp*100;
    }

    if (IsUTCgt(&timevalue, &max_UNIX_time) ||
        IsUTClt(&timevalue, &min_UNIX_time)) {
        return(-1);
    };

    return(0);

} /* utc_bintime() */

int utc_gettime(utc_t *utc) {

    struct timeval tv;
    struct timezone tz;
    struct timespec ts;

    gettimeofday(&tv, &tz);
    ts.tv_sec = tv.tv_sec;
    ts.tv_nsec = tv.tv_usec * 1000;

    return utc_mkbintime(utc, &ts, 0, -tz.tz_minuteswest*60);
} /* utc_gettime */

/*
 *++
 *  utc_gmtime()
 *
 *  Functional Description:
 *
 *      Converts a 128-bit UTC time into gmt time tm structs.
 *
 *  Inputs:
 *
 *      utc - pointer to 128-bit time to split into tm structs
 *
 *  Implicit Inputs:
 *
 *
 *  Outputs:
 *
 *      timetm - pointer to tm struct to receive time component of utc.
 *      tns - pointer to longword to receive nanosecond within second
 *      inacctm - pointer to tm struct to receive inaccuracy component
 *      ins - pointer to longword to receive inacc nanosecond
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
int utc_gmtime(struct tm *timetm,
    	       long *tns,
               struct tm *inacctm,
    	       long ins,
    	       utc_t *utc) {

    UTCValue timevalue, inaccvalue;
    register int i;

    if ((i = utc_comptime(&timevalue, &inaccvalue, (long *)NULL, utc)) < 0)
        return(i);

    splitinacc(&inaccvalue, inacctm, ins);
    splittime(&timevalue, 0L, timetm, tns);

    if (timetm != NULL) {
        timetm->tm_isdst = 0;
#ifdef TM_ZONE                          /* some systems don't have these */
        timetm->TM_ZONE = GMT;
#endif
#ifdef TM_GMTOFF
        timetm->TM_GMTOFF = 0;
#endif
    }

    /*
    ** Let the OS take care of this.
    ** tzname[0] = GMT;
    */
    return 0;
} /* utc_gmtime */
