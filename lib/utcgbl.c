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
#include "utc_priv.h"

    UTCValue diff_UNIX_UTC_ticks = UTCinit(0x13814000UL,0x01b21dd2UL);
    UTCValue diff_UTC_UNIX_ticks = UTCinit(0xec7ec000UL,0xfe4de22dUL);
    UTCValue diff_UTC_UNIX_secs = UTCinit(0x27ac6380UL, 0xfffffffdUL);
    UTCValue min_UNIX_time = UTCinit(0x0,0x0);
    UTCValue min_UNIX_sgn_time = UTCinit(0x80000000UL,0xffffffffUL);
    UTCValue max_UNIX_time = UTCinit(0xffffffffUL,0x0);
    UTCValue max_UNIX_sgn_time = UTCinit(0x7fffffffUL,0x0);
    int monthToDays[12] = {
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };
