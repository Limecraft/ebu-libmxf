if ENABLE_AVIDMXFINFO
lib_LTLIBRARIES = libavidmxfinfo-@LIBMXF_MAJORMINOR@.la
endif

libavidmxfinfo_@LIBMXF_MAJORMINOR@_la_SOURCES = avid_mxf_info.c
libavidmxfinfo_@LIBMXF_MAJORMINOR@_la_LDFLAGS = -version-info $(LIBMXF_LIBVERSION)
libavidmxfinfo_@LIBMXF_MAJORMINOR@_la_LIBADD = $(LIBMXF_LDADDLIBS)


if ENABLE_AVIDMXFINFO
bin_PROGRAMS = avidmxfinfo
endif

avidmxfinfo_SOURCES = main.c
avidmxfinfo_LDADD = libavidmxfinfo-@LIBMXF_MAJORMINOR@.la $(LIBMXF_LDADDLIBS)


AM_CFLAGS = $(LIBMXF_CFLAGS)



if ENABLE_AVIDMXFINFO
library_includedir = $(includedir)/libMXF-@LIBMXF_MAJORMINOR@/mxf/examples/avidmxfinfo
library_include_HEADERS = avid_mxf_info.h
endif

