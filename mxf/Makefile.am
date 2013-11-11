lib_LTLIBRARIES = libMXF-@LIBMXF_MAJORMINOR@.la

libMXF_@LIBMXF_MAJORMINOR@_la_SOURCES = \
	mxf_app.c \
	mxf_avid.c \
	mxf_avid_dictionary.c \
	mxf_avid_dictionary_data.h \
	mxf_avid_metadictionary.c \
	mxf_avid_metadictionary_data.h \
	mxf_cache_file.c \
	mxf_data_model.c \
	mxf_essence_container.c \
	mxf_file.c \
	mxf_header_metadata.c \
	mxf_index_table.c \
	mxf_labels_and_keys.c \
	mxf_list.c \
	mxf_logging.c \
	mxf_memory_file.c \
	mxf_page_file.c \
	mxf_partition.c \
	mxf_primer.c \
	mxf_rw_intl_file.c \
	mxf_stream_file.c \
	mxf_tree.c \
	mxf_utils.c \
	mxf_uu_metadata.c \
	mxf_version.c

if IS_WIN32
libMXF_@LIBMXF_MAJORMINOR@_la_SOURCES += mxf_win32_file.c
endif


libMXF_@LIBMXF_MAJORMINOR@_la_CFLAGS = $(LIBMXF_CFLAGS)
libMXF_@LIBMXF_MAJORMINOR@_la_LDFLAGS = $(LIBMXF_LDFLAGS) -version-info $(LIBMXF_LIBVERSION)
libMXF_@LIBMXF_MAJORMINOR@_la_LIBADD = $(LIBMXF_LIBADDLIBS)

library_includedir = $(includedir)/libMXF-@LIBMXF_MAJORMINOR@/mxf
library_include_HEADERS = \
	mxf.h \
	mxf_app.h \
	mxf_app_extensions_data_model.h \
	mxf_app_types.h \
	mxf_avid.h \
	mxf_avid_dictionary.h \
	mxf_avid_extensions_data_model.h \
	mxf_avid_labels_and_keys.h \
	mxf_avid_metadictionary.h \
	mxf_baseline_data_model.h \
	mxf_cache_file.h \
	mxf_data_model.h \
	mxf_essence_container.h \
	mxf_extensions_data_model.h \
	mxf_file.h \
	mxf_header_metadata.h \
	mxf_index_table.h \
	mxf_labels_and_keys.h \
	mxf_list.h \
	mxf_logging.h \
	mxf_macros.h \
	mxf_memory_file.h \
	mxf_page_file.h \
	mxf_partition.h \
	mxf_primer.h \
	mxf_rw_intl_file.h \
	mxf_stream_file.h \
	mxf_tree.h \
	mxf_types.h \
	mxf_utils.h \
	mxf_uu_metadata.h \
	mxf_version.h \
	mxf_win32_file.h


