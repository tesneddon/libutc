/*
 * 	Header file UTC_ARITH - Contains Macros to do extended arithmetic
 *				on UTCValues.
 *		
 * AUTHOR:	Carol Frampton
 *		Jan. 16, 1989
 *
 *		adapted from QUAD.H
 *		
 */
#ifndef utc_arith_h__
#define utc_arith_h__
#include "utc_64.h"

/*
 * All macros work on the datatype UTCValue.  All macros require POINTERS
 * to UTCValues as parameters.  Pointers are used so these macros can be 
 * converted to functions at a later date if that's deemed desireable for the
 * underlying hardware.
 */ 

#define IsUTCzero(utc)	U64ISZERO (*(utc))

#define IsUTCneg(utc)  	U64ISNEG (*(utc))

/*
 * Signed UTC value comparisons
 * The greater than and less than macros depend on the high-order
 * longword being declared a signed long. They cast the low word to be
 * unsigned in the case that the high words are signed to make the
 * quad-word comparisons work.
 */

#define IsUTCgt(a,b)	( U64CMP(*(a), *(b)) == 1 )

#define IsUTCge(a,b)	( U64CMP(*(a), *(b)) >= 0 )

#define IsUTClt(a,b)	( U64CMP(*(a), *(b)) < 0 )

#define IsUTCle(a,b)	( U64CMP(*(a), *(b)) <= 0 )

#define IsUTCeq(a,b) 	U64EQUAL(*(a), *(b))

#define UTCadd(add1,add2,sum)					\
{								\
        UTCValue _intermediate_result;				\
	U64SET( _intermediate_result, *(add1) );		\
	U64ADD( _intermediate_result, *(add2) );		\
	U64SET( *(sum), _intermediate_result) ;			\
}

#define UTCzero(dest)		U64ZERO(*(dest))

#define UTCnegate(source,dest)	U64NEGATE( *(dest), *(source) )

#define UTCsub(sub1,sub2,result)			\
{							\
        UTCValue _intermediate_result;			\
	U64SET((_intermediate_result), *(sub1));	\
	U64SUB((_intermediate_result), *(sub2));	\
	U64SET(*(result),_intermediate_result);		\
}

/* 
 * UTCValue Absolute Value.  result = sub1 if sub1 is positive
 * or the absolute value of sub1 if it was negative.
 */
#define UTCabsVal(sub1,result)				\
{							\
	UTCValue   _utcZero;				\
	U64ZERO(_utcZero);				\
	if (U64ISNEG(*(sub1)))				\
	   UTCsub(&_utcZero, (sub1), result)		\
	else						\
	   *(result) = *(sub1);				\
}

/*
 * Shifts a 64 bit value up to 31 bits right or left.
 * These shift macros assume that the distance is <= 31 bits.
 * K&R says that negative shift distances give undefined results.
 */
#define UTCshiftLeft(num,dist)	   U64LSHIFT(*(num), dist);
#define UTCshiftRight(num,dist)    U64RSHIFT(*(num), dist);

/* 
 * UTCValue Multiply By 2. result = num*2
 */
#define UTCmultiplyBy2(num,result)  			\
{							\
        UTCValue _intermediate_ ; 			\
	U64SET(_intermediate_, *(num));			\
	U64LSHIFT(_intermediate_, 1);			\
	U64SET(*(result),_intermediate_) 		\
}

/* 
 * UTCValue Dvide By 2. result = num/2
 */
#define UTCdivideBy2(num,result)  			\
{							\
	UTCValue _intermediate_; 			\
	U64SET(_intermediate_, *(num));			\
	U64RSHIFT(_intermediate_, 1);			\
        U64SET(*(result),_intermediate_);		\
}

/*
 * UTCiAdd - macro to add a signed integer to a UTC time
 *
 * See UTCadd macro above
 */

#define UTCiAdd(add1,I,sum)	\
{							\
     UTCValue _intermediate_;				\
     U64IADD(*(add1),I,_intermediate_);			\
     U64SET(*(sum), _intermediate_);			\
}							    
 

/*
 * UTCiMul - macro to mutiply a UTC value by a signed integer
 */

#define UTCiMul(num,I,result)		\
{					\
    UTCValue _intermediate_ ;		\
    U64IMUL(*(num),I,_intermediate_);	\
    U64SET(*(result), _intermediate_);	\
}    

/*
 * UTCiDiv - macro to divide a UTC value by a signed integer
 */

#define UTCiDiv(dividend,I,quot,remd)				\
	U64IDIV(*(dividend),I,*(quot),*(remd))

#define UTCassign(destination,source_lo,source_hi)		\
	U64SET64(*(destination), source_hi, source_lo)

#define UTCcopy(d,s)	U64COPY(*(d),*(s))

/*
 * 64, 32 bit differences
 */

#if LONG_BIT >= 64
#define UTCinit(lo,hi) 				\
	{((unsigned long)(hi)<<32)|lo}

#define UTClow(low)  (*(low))

#define U64IMUL(num,I,result)	((result) = (num) * I)

#define U64IDIV(dividend,I,quot,remd)				\
{								\
    (remd) = (long)(dividend) % (I);			\
    (quot) = (long)(dividend) / (I);				\
}

#else	/* LONG_BIT */
#if LONG_BIT == 32 

#define UTCinit(lo,hi) 	 {hi,lo}

#define UTClow(low)  ((low)->lo)

#define U64IMUL(num,I,result)					\
{ 								\
    UTCValue _iMul_intermediate; 				\
								\
    U64SET(_iMul_intermediate, (num));				\
    uemul((num).lo,(unsigned long)(I),&(result)); 		\
    (result).hi += (_iMul_intermediate.hi)*(I); 		\
    if ((long)(I) < 0) 						\
        (result).hi -= _iMul_intermediate.lo; 			\
}


#define U64IDIV(dividend,I,quot,remd)                                   \
    {                                                                   \
    UTCValue _iDiv_intermed, _iDiv_intermed2;				\
    int _negDividend = 0;						\
									\
    _iDiv_intermed.hi = 0;						\
    if ((dividend).hi & 0x80000000UL) {					\
	_negDividend = 1;						\
	_iDiv_intermed.lo = ~(dividend).hi;				\
	if (!((_iDiv_intermed2.lo = -(dividend).lo) & 0xffffffffUL))	\
	    _iDiv_intermed.lo++;					\
    } else {								\
	_iDiv_intermed.lo = (dividend).hi;				\
	_iDiv_intermed2.lo = (dividend).lo;				\
    }									\
    (void) uediv(&_iDiv_intermed,					\
		 (unsigned long)((long)(I) < 0 ? -(I) : (I)),		\
		 &((quot).hi), &_iDiv_intermed2.hi);			\
    (void) uediv(&_iDiv_intermed2,					\
		 (unsigned long)((long)(I) < 0 ? -(I) : (I)),		\
		 &((quot).lo), (unsigned long *)&(remd));		\
    if (_negDividend ^ (long)(I) < 0) {					\
	(quot).hi = ~(quot).hi;					\
	if (!(((quot).lo = -(quot).lo) & 0xffffffffUL))			\
	    (quot).hi++;						\
    }									\
    if (_negDividend)							\
	(remd) = -(remd);						\
    }
#else
#error "long integers must have at least 32 bits of precision"
#endif  /* LONG_BIT == 32 */
#endif	/* LONG_BIT >= 64 */

#endif /* utc_arith_h__ */
