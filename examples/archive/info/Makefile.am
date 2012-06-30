if ENABLE_ARCHIVE
lib_LTLIBRARIES = libarchivemxfinfo-@LIBMXF_MAJORMINOR@.la
endif

libarchivemxfinfo_@LIBMXF_MAJORMINOR@_la_SOURCES = archive_mxf_info_lib.c
libarchivemxfinfo_@LIBMXF_MAJORMINOR@_la_LDFLAGS = -version-info $(LIBMXF_LIBVERSION)
libarchivemxfinfo_@LIBMXF_MAJORMINOR@_la_LIBADD = $(LIBMXF_LDADDLIBS)


if ENABLE_ARCHIVE
bin_PROGRAMS = archive_mxf_info
endif

archive_mxf_info_SOURCES = archive_mxf_info.c
archive_mxf_info_LDADD = libarchivemxfinfo-@LIBMXF_MAJORMINOR@.la $(LIBMXF_LDADDLIBS)


AM_CFLAGS = $(LIBMXF_CFLAGS)



if ENABLE_ARCHIVE
library_includedir = $(includedir)/libMXF-@LIBMXF_MAJORMINOR@/mxf/examples/archive
library_include_HEADERS = archive_mxf_info_lib.h
endif

