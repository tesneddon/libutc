dnl Copyright (c) 2013, Endless Software Solutions
dnl
dnl libutc is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl libutc is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

# Initialization...
#
AC_PREREQ([2.68])
AC_INIT([libutc], [0.1], [libutc-bugs@endlesssoftware.com.au],,
	 [http://endlesssoftware.com.au/libutc])

AM_INIT_AUTOMAKE
AM_SILENT_RULES([yes])

LT_PREREQ([2.2])
LT_INIT([dlopen])

AC_CONFIG_SRCDIR([lib/utc.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
		 include/Makefile
		 lib/Makefile])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for header files.
AC_CHECK_HEADERS([endian.h limits.h time.h sys/time.h])

# Determine size of LONG_BIT which is required by the internal API for
# performing 64-bit math.
#
AC_COMPUTE_INT([long_bit], [ sizeof(long) * CHAR_BIT ],
	       [#include <limits.h>],
               AC_MSG_ERROR([Unable to determine word size in bits; LONG_BIT]))
AC_DEFINE_UNQUOTED([LONG_BIT], [$long_bit],
		   [Define to the machine word size.])

# Check for the following library functions
#
AC_CHECK_FUNCS([gettimeofday])

AC_OUTPUT


echo \
"-----------------------------------------------------------------

${PACKAGE_NAME} Version ${PACKAGE_VERSION}

Prefix: '${prefix}'
Compiler: '${CC} ${CFLAGS} ${CPPFLAGS}'

Package features:
  None.

Now type 'make @<:@<target>@:>@'
  where the optional <target> is:
    all                - build all binaries
    install            - install everything

-----------------------------------------------------------------"
