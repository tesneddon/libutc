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

AC_PREREQ([2.68])
AC_INIT([libutc], [0.1], [libutc-bugs@endlesssoftware.com.au],,
	 [http://endlesssoftware.com.au/libutc])
AM_INIT_AUTOMAKE
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

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([limits.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([gettimeofday])

# Options
AM_SILENT_RULES

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
