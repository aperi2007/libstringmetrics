dnl Process this file with autoconf to produce a configure script.
AC_INIT(stringmetrics, 1.0, aperi2007@gmail.com)

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR(src/stringmetrics.c)
AC_CONFIG_MACRO_DIR([m4])

LT_INIT
AC_ENABLE_SHARED
AC_ENABLE_STATIC

AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
# AC_PROG_RANLIB
AC_PROG_LIBTOOL
AM_PROG_CC_C_O

AC_OUTPUT(Makefile src/Makefile)
