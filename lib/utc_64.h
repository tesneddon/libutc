/*
**++
**  FACILITY:   libutc
**
**  ABSTRACT:   64-bit definitions
**
**  MODULE DESCRIPTION:
**
**      This module contains macros for handling 64-bit values (especially
**  useful for 32-bit platforms).
**
**  AUTHOR:     Tim E. Sneddon (from DCE source)
**
**  Copyright (c) 1990-19944, 1996 Open Software Foundation, Inc.
**  ALL RIGHTS RESERVED (DCE).  See the file named COPYING for the full
**  copyright text.
**  Copyright (C) 1991, 1990 Transarc Corporation - All rights reserved.
**  Copyright (c) 2013, Endless Software Solutions.
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
**  along with Foobar.  If not, see <http://www.gnu.org/licenses/>
**
**  CREATION DATE:  09-SEP-2013
**
**  MODIFICATION HISTORY:
**
**      09-SEP-2013 V1.0    Sneddon     Initial coding, built from DCE code.
**--
*/
#ifndef utc_64_h__
#define utc_64_h__
#include <limits.h>
#ifndef LONG_BIT
# define LONG_BIT (sizeof(unsigned long) * CHAR_BIT)
#endif

/*
 * ASSUMPTIONS throughout:
 *	32 bit longs
 *	twos complement arithmetic
 *	8-bit bytes
 */

/*
 * In these macro definitions, the arguments are named as follows:
 *    d  destination        (only used when a value is changed)
 *    s  source             (s1 and s2 for two sources)
 *    h  the high value     (either source or destination)
 *    l  the low value      (either source or destination)
 *    i  some integer amount
 *
 */

/*
 * U64CMP returns:  1 if s1 is greater;
 *                 -1 if s2 is greater,
 *                  0 if equal
 */
#if LONG_BIT >= 64
#define U64CMP(s1,s2)   ((long)(s1) < (long)(s2) ? -1 :         \
                         ((long)(s1) > (long)(s2) ? 1 : 0))
#define U64EQUAL(s1,s2) ( (s1) == (s2) )
#define U64ISZERO(s)    ( (s) == 0 )
#define U64ISNEG(s)    ( (long)(s) < 0 )
#define U64FITSIN32(s)   ( ((s) & 0xffffffff00000000) == 0 )

#define U64SET(d,s)     ( (d) = (s) )
#define U64SET32(d,l)   ( (d) = ((l) & 0x00000000ffffffff) )
#define U64SET64(d,h,l) ( (d) = (((h) << 32) | ((l) & 0x00000000ffffffff)) )
#define U64GET64(h,l,s) ( (h) = ((s)>>32), U64SET32(l,s))

#define U64ZERO(d)      U64SET(d,0)
#define U64LSHIFT(d,i)	( (d) <<= (i) )
#define U64RSHIFT(d,i)  ( (d) >>= (i) )
/* 	#define U64ADD32(a,i)	?????????? */
#define U64ADD(a,b)	( (a) += (b) )
#define U64SUB(a,b)	( (a) -= (b) )
#define U64NEGATE(d,s)	( (d) = -(s) )
#define U64COPY(d,s)	U64SET(d,s)
#define U64IADD(a,I,result)	( (result) = (a) + (I) )

#define U64_TO_HYPER(d, s)	( (d) = (s) )
#define HYPER_TO_U64(d, s)	( (d) = (s) )

#else   /* 64 bits */

#if LONG_BIT == 32
#define U64CMP(s1,s2)   ( (long)((s1).hi) < (long)((s2).hi) ? -1 : \
			( (long)((s1).hi) > (long)((s2).hi) ? 1 : \
			(       ((s1).lo) <       ((s2).lo) ? -1 : \
			(       ((s1).lo) >       ((s2).lo) ? 1 : 0 ))))

#define U64EQUAL(s1,s2) ((s1).lo == (s2).lo && (s1).hi == (s2).hi)
#define U64ISZERO(s)    ((s).lo == 0 && (s).hi == 0)
#define U64ISNEG(s)    (( (s).hi & 0x80000000UL ) != 0)
#define U64FITSIN32(s)  ((s).hi == 0)

#define U64SET(d,s)     ((d)=(s))
#define U64SET32(d,l)   ((d).hi = 0, (d).lo = (l))
#define U64SET64(d,h,l) ((d).hi = (h), (d).lo = (l))
#define U64GET32(l,s)   ((l) = (s).lo)
#define U64GET64(h,l,s) ((l) = (s).lo, (h) = (s).hi)
#define U64ZERO(d)      U64SET64(d,0,0)
#define U64ONES(d)      U64SET64(d,~0x0,~0x0)


#define U64LSHIFT(d,i)  ((d).hi <<= (i),                           \
			 (d).hi |= (((d).lo) >>                    \
			 ((sizeof(unsigned32)*8)-(i))),            \
			 (d).lo <<= (i))
#define U64RSHIFT(d,i)  ((d).lo >>= (i),                           \
			 (d).lo |= (((d).hi) <<                    \
			 ((sizeof(unsigned32)*8)-(i))),            \
			 (d).hi >>= (i))

/*
 * The algorithm here is to check for two cases that cause a carry.
 * If the top two bits are different then if the sum has the top
 * bit off then there must have been a carry.  If the top bits are
 * both one then there is always a carry.
 */
#define SIGN          0x80000000UL
#define U64ADD32(a,i) (((((a).lo ^ (long)(i)) & SIGN) ?             \
			(((((a).lo + (long)(i)) & SIGN) == 0) &&    \
			 (a).hi++) :                                \
			(((a).lo & (long)(i) & SIGN) && (a).hi++)), \
		       (a).lo += (long)(i))

#define U64ADD(a,b)   (U64ADD32((a),(b).lo), (a).hi += (b).hi)

#define U64SUB(a,b)   (U64ADD32((a),~((b).lo)),                \
		       (a).hi += ~((b).hi),                    \
		       U64ADD32((a),1))

/* We take the one's complement of both the lo and high
 * order longwords separately.  Then we do quad add of one.
 */

#define U64NEGATE(d,s)						\
{								\
        (d).lo = ~((s).lo);					\
	(d).hi = ~((s).hi);					\
        U64ADD32( (d),(1) );     				\
}

#define U64COPY(d,s)						\
{								\
	(d).lo = (s).lo;					\
	(d).hi = (s).hi;					\
}

#define U64IADD(add1,I,result)					\
{								\
    long _iAdd_intermediate = (((add1).lo & SIGN) != 0) ;       \
    (result).lo = (I) + (add1).lo ;				\
    (result).hi = (add1).hi ;					\
    if ((_iAdd_intermediate) ^ ((long)(I) < 0))			\
    {								\
	if ((long)(I) < 0)					\
	    (result).hi--; 					\
	if(!((result).lo & SIGN))				\
	    (result).hi++;					\
    }								\
}

#define U64_TO_HYPER(d,s) ( (d).low = (s).lo, (d).high = (s).hi )
#define HYPER_TO_U64(d,s) ( (d).lo = (s).low, (d).hi = (s).high )

#else	/* 32 bits */
#error " long integer must support 32 bits of precision. "
#endif  /* 32 bits */
#endif  /* 64 bits */

#endif /* utc_64_h__ */
