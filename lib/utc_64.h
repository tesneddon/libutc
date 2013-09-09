/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993, 1994, 1996 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE in the
 * src directory for the full copyright text.
 */
/*
 * HISTORY
 * $Log: dce64.h,v $
 * Revision 1.1.4.2  1996/02/18  23:32:57  marty
 * 	Update OSF copyright years
 * 	[1996/02/18  22:20:57  marty]
 *
 * Revision 1.1.4.1  1995/12/08  21:37:06  root
 * 	Submit OSF/DCE 1.2.1
 * 	[1995/12/08  18:08:58  root]
 * 
 * Revision 1.1.2.7  1994/09/23  19:59:59  tom
 * 	Back out change of unsigned/signed64 to typedef hyper
 * 	[1994/09/23  19:26:46  tom]
 * 
 * Revision 1.1.2.5  1994/09/21  22:01:37  tom
 * 	Add u64_to_hyper and hyper_to_u64 for dts use.
 * 	[1994/09/21  21:14:16  tom]
 * 
 * Revision 1.1.2.4  1994/08/23  20:31:42  cbrooks
 * 	Code Cleanup
 * 	[1994/08/19  17:52:19  cbrooks]
 * 
 * Revision 1.1.2.3  1994/08/16  18:12:42  cbrooks
 * 	Move U64IMUL, U64IDIV to utc_arith.h
 * 	[1994/08/16  17:51:40  cbrooks]
 * 
 * 	CR11494 - 64 bit changes
 * 	[1994/08/16  13:09:00  cbrooks]
 * 
 * 	More 64bit changes for 32bit machines
 * 	[1994/08/15  18:49:14  cbrooks]
 * 
 * 	64Bit changes - macro updates
 * 	[1994/08/12  18:57:42  cbrooks]
 * 
 * 	CR11494 - 64bit changes
 * 	[1994/08/09  18:44:15  cbrooks]
 * 
 * Revision 1.1.2.2  1994/03/17  17:45:14  bowe
 * 	Add Transarc copyright and assumptions comment.
 * 	[1994/03/17  16:48:26  bowe]
 * 
 * Revision 1.1.2.1  1994/03/16  21:56:56  bowe
 * 	Surround file with #ifndef
 * 	[1994/03/16  21:54:24  bowe]
 * 
 * 	Initial checkin
 * 	[1994/03/16  21:21:44  bowe]
 * 
 * $EndLog$
 */

/* Copyright (C) 1991, 1990 Transarc Corporation - All rights reserved. */

#ifndef utc_64_h__
#define utc_64_h__

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
