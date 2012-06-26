if ENABLE_READER
lib_LTLIBRARIES = libmxfreader-@LIBMXF_MAJORMINOR@.la
endif

libmxfreader_@LIBMXF_MAJORMINOR@_la_SOURCES = \
	mxf_essence_helper.c \
	mxf_index_helper.c \
	mxf_op1a_reader.c \
	mxf_opatom_reader.c \
	mxf_reader.c
libmxfreader_@LIBMXF_MAJORMINOR@_la_LDFLAGS = -version-info $(LIBMXF_LIBVERSION)
libmxfreader_@LIBMXF_MAJORMINOR@_la_LIBADD = $(LIBMXF_LDADDLIBS)


if ENABLE_READER
noinst_PROGRAMS = test_mxf_reader
endif

test_mxf_reader_SOURCES = test_mxf_reader.c
test_mxf_reader_LDADD = libmxfreader-@LIBMXF_MAJORMINOR@.la $(LIBMXF_LDADDLIBS)


AM_CFLAGS = $(LIBMXF_CFLAGS)



if ENABLE_READER
library_includedir = $(includedir)/libMXF-@LIBMXF_MAJORMINOR@/mxf/examples/reader
library_include_HEADERS = \
	mxf_essence_helper.h \
	mxf_index_helper.h \
	mxf_op1a_reader.h \
	mxf_opatom_reader.h \
	mxf_reader.h \
	mxf_reader_int.h
endif

