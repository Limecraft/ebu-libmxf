SUBDIRS = mxf test examples tools msvc_build


ACLOCAL_AMFLAGS = -I m4


pkgconfig_DATA = libMXF-$(LIBMXF_MAJORMINOR).pc

libMXF-$(LIBMXF_MAJORMINOR).pc: libMXF.pc
	cp libMXF.pc libMXF-$(LIBMXF_MAJORMINOR).pc

CLEANFILES = libMXF-$(LIBMXF_MAJORMINOR).pc


BUILT_SOURCES = mxf_scm_version.h

mxf_scm_version.h:
	sh $(top_srcdir)/gen_scm_version.sh mxf_scm_version.h $(top_srcdir)/mxf_scm_version.h LIBMXF_SCM_VERSION

.PHONY: mxf_scm_version.h

DISTCLEANFILES = mxf_scm_version.h


EXTRA_DIST = \
	autogen.sh \
	gen_scm_version.sh \
	mxf_scm_version.h

