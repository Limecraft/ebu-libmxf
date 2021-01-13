bin_PROGRAMS = MXFDump

MXFDump_SOURCES = \
	MXFDump.cpp \
	AAFMetaDictionary.h \
	MXFLabels.h \
	MXFMetaDictionary.h

AM_CXXFLAGS = $(WARN_CFLAGS)

# MacOS X: require link to CoreServices library for functions such as FSOpenFork
if IS_MACOS
AM_LDFLAGS = -framework CoreServices
endif


EXTRA_DIST = README.txt

