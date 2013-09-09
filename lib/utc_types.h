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
#ifndef utc_types_h__
#define utc_types_h__

#if LONG_BIT >= 64
    typedef unsigned long unsigned64;
#else
    typedef struct unsigned64_s_t {
    	unsigned long hi;
    	unsigned long lo;
    } unsigned64;
#endif /* LONG_BIT */

    typedef struct signed64_s_t {
    	unsigned long hi;
    	unsigned long lo;
    } signed64;

    typedef struct unsigned48_s_t {
    	unsigned long  int  lo;             /* least significant 32 bits */
    	unsigned short int  hi;             /* most significant 16 bits */
    } unsigned48;

    typedef struct unsigned128_s_t {
    	unsigned long lolo;
    	unsigned long lohi;
    	unsigned long hilo;
    	unsigned long hihi;
    } unsigned128;

#endif /* utc_types_h__ */
