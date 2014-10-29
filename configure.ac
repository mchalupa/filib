
AC_PREREQ([2.64])

m4_define([filib_major_version], [0])
m4_define([filib_minor_version], [0])
m4_define([filib_micro_version], [0])
m4_define([filib_version],
          [filib_major_version.filib_minor_version.filib_micro_version])

AC_INIT([FiLib library],
        [filib_version],
        [mchqwerty@gmail.com],
        [filib],
        [https://github.com/mchalupa/filib/])

AC_SUBST([FILIB_VERSION_MAJOR], [filib_major_version])
AC_SUBST([FILIB_VERSION_MINOR], [filib_minor_version])
AC_SUBST([FILIB_VERSION_MICRO], [filib_micro_version])
AC_SUBST([FILIB_VERSION], [filib_version])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.11 foreign no-dist-gzip dist-xz])

AM_SILENT_RULES([yes])

# Check for programs
AC_PROG_CC

# Initialize libtool
LT_PREREQ([2.2])
LT_INIT

PKG_PROG_PKG_CONFIG()

TESTS_CFLAGS=
TESTS_LIBS=
FILIB_LIBS=
FILIB_CFLAGS=

AC_SUBST([TESTS_LIBS])
AC_SUBST([TESTS_CFLAGS])
AC_SUBST([FILIB_LIBS])
AC_SUBST([FILIB_CFLAGS])

AC_CONFIG_FILES([Makefile
		 src/Makefile
		 src/fiobject/Makefile
		 tests/Makefile])

AC_OUTPUT
