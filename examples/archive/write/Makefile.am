if ENABLE_ARCHIVE
lib_LTLIBRARIES = libwritearchivemxf-@LIBMXF_MAJORMINOR@.la
endif

libwritearchivemxf_@LIBMXF_MAJORMINOR@_la_SOURCES = \
	timecode_index.c \
	write_archive_mxf.c
libwritearchivemxf_@LIBMXF_MAJORMINOR@_la_LDFLAGS = -version-info $(LIBMXF_LIBVERSION)
libwritearchivemxf_@LIBMXF_MAJORMINOR@_la_LIBADD = $(LIBMXF_LDADDLIBS)


if ENABLE_ARCHIVE
noinst_PROGRAMS = update_archive_mxf
endif

update_archive_mxf_SOURCES = update_archive_mxf.c
update_archive_mxf_LDADD = libwritearchivemxf-@LIBMXF_MAJORMINOR@.la $(LIBMXF_LDADDLIBS)


AM_CFLAGS = $(LIBMXF_CFLAGS)



if ENABLE_ARCHIVE
library_includedir = $(includedir)/libMXF-@LIBMXF_MAJORMINOR@/mxf/examples/archive
library_include_HEADERS = write_archive_mxf.h timecode_index.h
endif

