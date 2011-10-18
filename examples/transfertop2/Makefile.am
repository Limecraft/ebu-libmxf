if ENABLE_TRANSFERTOP2
if HAVE_AAFSDK
noinst_PROGRAMS = test_avid_mxf_to_p2 test_avidp2transfer
else
noinst_PROGRAMS = test_avid_mxf_to_p2
endif
endif


if ENABLE_TRANSFERTOP2
noinst_LTLIBRARIES = libavidmxftop2.la
endif

libavidmxftop2_la_SOURCES = \
	xml_writer.c \
	avid_mxf_to_p2.c \
	xml_writer.h \
	icon_avid_to_p2.h \
	avid_mxf_to_p2.h


test_avid_mxf_to_p2_SOURCES = test_avid_mxf_to_p2.c
test_avid_mxf_to_p2_LDADD = libavidmxftop2.la $(LIBMXF_LDADDLIBS)


test_avidp2transfer_SOURCES = \
	avidp2transfer.cpp \
	avidp2transfer.h \
	test_avidp2transfer.cpp

test_avidp2transfer_CXXFLAGS = $(AM_CFLAGS) $(AAFSDK_CXXFLAGS)
test_avidp2transfer_LDFLAGS = $(AM_LDFLAGS) $(AAFSDK_LDFLAGS)
test_avidp2transfer_LDADD = libavidmxftop2.la $(AAFSDK_LIBS) $(LIBMXF_LDADDLIBS)


AM_CFLAGS = $(LIBMXF_CFLAGS)



EXTRA_DIST = make_p2testdrive.sh
