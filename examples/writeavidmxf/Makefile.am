if ENABLE_WRITEAVIDMXF
lib_LTLIBRARIES = libwriteavidmxf-@LIBMXF_MAJORMINOR@.la
endif

libwriteavidmxf_@LIBMXF_MAJORMINOR@_la_SOURCES = \
	package_definitions.c \
	write_avid_mxf.c
libwriteavidmxf_@LIBMXF_MAJORMINOR@_la_LDFLAGS = -version-info $(LIBMXF_LIBVERSION)
libwriteavidmxf_@LIBMXF_MAJORMINOR@_la_LIBADD = $(LIBMXF_LDADDLIBS)



if ENABLE_WRITEAVIDMXF
bin_PROGRAMS = writeavidmxf
endif

writeavidmxf_SOURCES = main.c
writeavidmxf_LDADD = libwriteavidmxf-@LIBMXF_MAJORMINOR@.la $(LIBMXF_LDADDLIBS)


AM_CFLAGS = $(LIBMXF_CFLAGS)


if ENABLE_WRITEAVIDMXF
library_includedir = $(includedir)/libMXF-@LIBMXF_MAJORMINOR@/mxf/examples/writeavidmxf
library_include_HEADERS = \
	package_definitions.h \
	write_avid_mxf.h
endif

