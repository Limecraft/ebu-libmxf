dnl-----------------------------------------------------------------------------
dnl -- Extract package info
dnl-----------------------------------------------------------------------------

dnl extract package name and version from mxf_version.h

m4_define([m4_LIBMXF_LIBRARY_NAME],
	m4_esyscmd([(sed -n 's/^.*LIBMXF_LIBRARY_NAME[^\"]*\"\([^\"]*\)\"/\1/p' mxf/mxf_version.h | tr -d '\n')]))
m4_define([m4_LIBMXF_VERSION_MAJOR],
	m4_esyscmd([(sed -n 's/^.*LIBMXF_VERSION_MAJOR\ *\([0-9][0-9]*\)/\1/p' mxf/mxf_version.h | tr -d '\n')]))
m4_define([m4_LIBMXF_VERSION_MINOR],
	m4_esyscmd([(sed -n 's/^.*LIBMXF_VERSION_MINOR\ *\([0-9][0-9]*\)/\1/p' mxf/mxf_version.h | tr -d '\n')]))
m4_define([m4_LIBMXF_VERSION_MICRO],
	m4_esyscmd([(sed -n 's/^.*LIBMXF_VERSION_MICRO\ *\([0-9][0-9]*\)/\1/p' mxf/mxf_version.h | tr -d '\n')]))
m4_define([m4_LIBMXF_VERSION],
	m4_defn([m4_LIBMXF_VERSION_MAJOR]).m4_defn([m4_LIBMXF_VERSION_MINOR]).m4_defn([m4_LIBMXF_VERSION_MICRO]))


dnl-----------------------------------------------------------------------------
dnl -- Init
dnl-----------------------------------------------------------------------------

AC_INIT(m4_defn([m4_LIBMXF_LIBRARY_NAME]), m4_defn([m4_LIBMXF_VERSION]))
AC_CONFIG_SRCDIR([mxf/mxf.h])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.11 -Wall parallel-tests tar-ustar])
AM_SILENT_RULES([yes])

dnl define for automake 1.12 to avoid warnings
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])


dnl-----------------------------------------------------------------------------
dnl -- Version
dnl-----------------------------------------------------------------------------

dnl CURRENT, REVISION, AGE
dnl - library source changed -> increment REVISION
dnl - interfaces added/removed/changed -> increment CURRENT, REVISION = 0
dnl - interfaces added -> increment AGE
dnl - interfaces removed -> AGE = 0
LIBMXF_LIBVERSION="4:0:0"
AC_SUBST(LIBMXF_LIBVERSION)


LIBMXF_MAJORMINOR=m4_defn([m4_LIBMXF_VERSION_MAJOR]).m4_defn([m4_LIBMXF_VERSION_MINOR])
AC_SUBST(LIBMXF_MAJORMINOR)


dnl-----------------------------------------------------------------------------
dnl -- Checks for programs.
dnl-----------------------------------------------------------------------------

AC_PROG_LIBTOOL

AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL


dnl-----------------------------------------------------------------------------
dnl -- Enable options
dnl-----------------------------------------------------------------------------

AC_ARG_ENABLE(examples,
	AC_HELP_STRING([--disable-examples],
		[disable building of all examples [[default=no]]]),
	enable_examples=$enableval,
	enable_examples="yes")


AC_ARG_ENABLE(archive,
	AC_HELP_STRING([--disable-archive],
		[disable building of archive example [[default=no]]]),
	enable_archive=$enableval,
	enable_archive="default")
AM_CONDITIONAL(ENABLE_ARCHIVE,
	test x"$enable_archive" = xyes ||
		(test x"$enable_archive" = xdefault && test x"$enable_examples" = xyes))


AC_ARG_ENABLE(avidmxfinfo,
	AC_HELP_STRING([--disable-avidmxfinfo],
		[disable building of avidmxfinfo example [[default=no]]]),
	enable_avidmxfinfo=$enableval,
	enable_avidmxfinfo="default")

AM_CONDITIONAL(ENABLE_AVIDMXFINFO,
	test x"$enable_avidmxfinfo" = xyes ||
		(test x"$enable_avidmxfinfo" = xdefault && test x"$enable_examples" = xyes))


AC_ARG_ENABLE(reader,
	AC_HELP_STRING([--disable-reader],
		[disable building of reader example [[default=no]]]),
	enable_reader=$enableval,
	enable_reader="default")

AM_CONDITIONAL(ENABLE_READER,
	test x"$enable_reader" = xyes ||
		(test x"$enable_reader" = xdefault && test x"$enable_examples" = xyes))


AC_ARG_ENABLE(transfertop2,
	AC_HELP_STRING([--disable-transfertop2],
		[disable building of transfertop2 example [[default=no]]]),
	enable_transfertop2=$enableval,
	enable_transfertop2="default")

AM_CONDITIONAL(ENABLE_TRANSFERTOP2,
	test x"$enable_transfertop2" = xyes ||
		(test x"$enable_transfertop2" = xdefault && test x"$enable_examples" = xyes))


AC_ARG_ENABLE(writeavidmxf,
	AC_HELP_STRING([--disable-writeavidmxf],
		[disable building of writeavidmxf example [[default=no]]]),
	enable_writeavidmxf=$enableval,
	enable_writeavidmxf="default")

AM_CONDITIONAL(ENABLE_WRITEAVIDMXF,
	test x"$enable_writeavidmxf" = xyes ||
		(test x"$enable_writeavidmxf" = xdefault && test x"$enable_examples" = xyes))


dnl-----------------------------------------------------------------------------
dnl -- Checks for libraries.
dnl-----------------------------------------------------------------------------

AC_CHECK_LIB([m], [sin])


dnl Check for UUID generation library
case "$host" in
	*-*-*mingw*) os=win ;;
	*-*-darwin*) os=mac ;;
esac
if test x"$os" = xwin; then
	AC_CHECK_HEADER([windows.h],
					[UUIDLIB="-lole32"],
					AC_MSG_ERROR(No windows uuid generation function))
elif test x"$os" = xmac; then
	UUIDLIB=""
else
	AC_CHECK_LIB([uuid], [uuid_generate],
			     [UUIDLIB="-luuid"],
			     AC_MSG_ERROR(No uuid generation function))
fi
AC_SUBST(UUIDLIB)


dnl The AAF SDK is required to compile the whole transfertop2 example app
AC_ARG_WITH([aafsdk],
            [AS_HELP_STRING([--with-aafsdk=path],
				[set path to AAF SDK, which is required for building the complete transfertop2 example])],
            [],
            [with_aafsdk=no])
if test x"$with_aafsdk" != xno; then
	AC_CHECK_FILE($with_aafsdk/lib/debug/libaaflib.a,
				  [],
				  AC_ERROR(AAF SDK library not found at $with_aafsdk))
fi
AM_CONDITIONAL([HAVE_AAFSDK], [test x"$with_aafsdk" != xno])



dnl-----------------------------------------------------------------------------
dnl -- Checks for header files.
dnl-----------------------------------------------------------------------------

AC_CHECK_HEADERS([fcntl.h inttypes.h sys/time.h sys/timeb.h unistd.h wchar.h])


dnl-----------------------------------------------------------------------------
dnl -- Checks for typedefs, structures, and compiler characteristics.
dnl-----------------------------------------------------------------------------

AC_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T


dnl mingw doesn't support the 'z' printf format length modifier for size_t
case "$host" in
	*-*-*mingw32) AC_DEFINE([PRIszt], ["u"], [Define printf size_t format specifier]) ;;
			   *) AC_DEFINE([PRIszt], ["zu"], [Define printf size_t format specifier])
esac


dnl-----------------------------------------------------------------------------
dnl -- Checks for library functions
dnl-----------------------------------------------------------------------------

AC_SYS_LARGEFILE
AC_FUNC_FSEEKO


AC_CHECK_FUNCS([gettimeofday memmove memset sqrt strerror strncasecmp strerror_r])
AC_CHECK_FUNC([strdup],,
			  AC_ERROR(require implementation for missing strdup function))


dnl-----------------------------------------------------------------------------
dnl -- Compiler flags etc.
dnl-----------------------------------------------------------------------------

WARN_CFLAGS=
AC_APPEND_SUPPORTED_CFLAGS(WARN_CFLAGS, [-W -Wall])
AC_SUBST(WARN_CFLAGS)

LIBMXF_CFLAGS="$WARN_CFLAGS -I\$(top_srcdir)"
AC_SUBST(LIBMXF_CFLAGS)

LIBMXF_LIBADDLIBS="$UUIDLIB"
AC_SUBST(LIBMXF_LIBADDLIBS)

LIBMXF_LDADDLIBS="$LIBMXF_LIBADDLIBS \
	\$(top_builddir)/mxf/libMXF-$LIBMXF_MAJORMINOR.la"
AC_SUBST(LIBMXF_LDADDLIBS)

LIBMXF_LDFLAGS=
AC_APPEND_SUPPORTED_LDFLAGS(LIBMXF_LDFLAGS, [-Wl,--no-undefined])
AC_SUBST(LIBMXF_LDFLAGS)

if test x"$with_aafsdk" != xno; then
	AAFSDK_CXXFLAGS="-I$with_aafsdk/include"
	AAFSDK_LDFLAGS="-ldl -rdynamic"
	AAFSDK_LIBS="-L$with_aafsdk/lib/debug -laaflib -laafiid"
else
	AAFSDK_CXXFLAGS=
	AAFSDK_LDFLAGS=
	AAFSDK_LIBS=
fi
AC_SUBST(AAFSDK_CXXFLAGS)
AC_SUBST(AAFSDK_LDFLAGS)
AC_SUBST(AAFSDK_LIBS)


case "$host" in
	*-*-*mingw*) os=win ;;
	*-*-darwin*) os=mac
esac
AM_CONDITIONAL([IS_MACOS], [test x"$os" = xmac])
AM_CONDITIONAL([IS_WIN32], [test x"$os" = xwin])


dnl-----------------------------------------------------------------------------
dnl -- Package Config
dnl-----------------------------------------------------------------------------

pkgconfigdir="\$(libdir)/pkgconfig"
AC_SUBST(pkgconfigdir)

dnl add libraries to pkg config "Libs:" for static-only builds
if test x"$enable_shared" = xyes; then
	PC_ADD_LIBS=
	PC_ADD_PRIVATE_LIBS=$UUIDLIB
else
	PC_ADD_LIBS=$UUIDLIB
	PC_ADD_PRIVATE_LIBS=
fi
AC_SUBST(PC_ADD_LIBS)
AC_SUBST(PC_ADD_PRIVATE_LIBS)


dnl-----------------------------------------------------------------------------
dnl -- Config files
dnl-----------------------------------------------------------------------------

AC_CONFIG_FILES([
	Makefile
    mxf/Makefile
    examples/Makefile
    examples/reader/Makefile
    examples/writeavidmxf/Makefile
    examples/avidmxfinfo/Makefile
    examples/archive/Makefile
    examples/archive/write/Makefile
    examples/archive/info/Makefile
    examples/archive/test/Makefile
    examples/writeaviddv50/Makefile
    examples/transfertop2/Makefile
    test/Makefile
    tools/Makefile
    tools/MXFDump/Makefile
    tools/extract_avid_extensions/Makefile
    msvc_build/Makefile
    msvc_build/vs10/Makefile
    libMXF.pc])

AC_OUTPUT

