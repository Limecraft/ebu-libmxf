SUBDIRS = mxf examples test tools msvc_build


ACLOCAL_AMFLAGS = -I m4


pkgconfig_DATA = libMXF-$(LIBMXF_MAJORMINOR).pc

libMXF-$(LIBMXF_MAJORMINOR).pc: libMXF.pc
	cp libMXF.pc libMXF-$(LIBMXF_MAJORMINOR).pc

CLEANFILES = libMXF-$(LIBMXF_MAJORMINOR).pc



EXTRA_DIST = autogen.sh

