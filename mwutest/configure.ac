#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(mwutest, 1.0, shaomingfu@gmail.com)
AM_INIT_AUTOMAKE(mwutest, 1.0, shaomingfu@gmail.com)
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([locale.h stddef.h stdint.h stdlib.h string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([floor gettimeofday localeconv memset pow sqrt strchr])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
