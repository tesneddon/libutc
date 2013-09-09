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
#include <sys/time.h>
#include <time.h>
#include <utc.h>
#include "utc_arith.h"

/*
**  Forward declarations
*/

    int utc_gettime(utc_t *utc);

int utc_gettime(utc_t *utc) {

    struct timeval tv;
    struct timezone tz;
    struct timespec ts;

    gettimeofday(&tv, &tz);
    ts.tv_sec = tv.tv_sec;
    ts.tv_nsec = tv.tv_usec * 1000;

    return utc_mkbintime(utc, &ts, 0, -tz.tz_minuteswest*60);
} /* utc_gettime */
