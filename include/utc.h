#ifndef utc_h__
#define utf_h__

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

#endif /* utc_h__ */

