#ifndef utc_h__
#define utc_h__
#include <time.h>

#ifndef _UTC_T_
#define _UTC_T_
    typedef struct utc {
    	char char_array[16];
    } utc_t;
#endif /* _UTC_T_ */

    enum utc_cmptype {
    	utc_lessThen,
    	utc_equalTo,
    	utc_greaterThan,
    	utc_indeterminate
    };

#ifdef __timespec_defined
    typedef struct timespec timespec_t;
#else
# ifdef _AES_SOURCE
#  include <sys/timers.h>
# else
#  ifndef _TIMESPEC_T_
#   define _TIMESPEC_T_
    typedef struct timespec {
    	time_t tv_sec;
    	long tv_nsec;
    } timespec_t;
#  endif /* _TIMESPEC_T_ */
# endif /* _AES_SOURCE */
#endif /* __timespec_defined */
#ifndef _RELTIMESPEC_T_
# define _RELTIMESPEC_T_
    typedef struct timespec reltimespec_t;
#endif /* _RELTIMESPEC_T_ */

#define UTC_MAX_STR_LEN 50      /* Max length of string used by conversion
				   routines (utc_asc...) */

#ifdef __STDC__
    int utc_bintime(timespec_t *timesp, timespec_t *inaccsp, long *tdf,
    	    	    utc_t *utc);
    int utc_gettime(utc_t *utc);
    int utc_gmtime(struct tm *timetm, long *tns, struct tm *inacctm, long ins,
                   utc_t *utc);
    int utc_mkbintime(utc_t *utc, timespec_t *timesp, timespec_t *inaccsp,
    	    	      long tdf);
    int utc_mkgmtime(utc_t *utc, struct tm *timetm, long tns,
                     struct tm *inacctm, long ins);
    /* utc_mkcomptime */
#else
    int utc_bintime();
    int utc_gettime();
    int utc_gmtime();
    int utc_mkbintime();
    int utc_mkgmtime();
#endif /* __STDC__ */

#endif /* utc_h__ */

