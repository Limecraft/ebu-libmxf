if ENABLE_ARCHIVE
noinst_PROGRAMS = test_write_archive_mxf
check_PROGRAMS = test_timecode_index
endif

test_write_archive_mxf_SOURCES = test_write_archive_mxf.c
test_write_archive_mxf_LDADD = $(top_builddir)/examples/archive/write/libwritearchivemxf-@LIBMXF_MAJORMINOR@.la $(LIBMXF_LDADDLIBS)

test_timecode_index_SOURCES = test_timecode_index.c
test_timecode_index_LDADD = $(top_builddir)/examples/archive/write/libwritearchivemxf-@LIBMXF_MAJORMINOR@.la $(LIBMXF_LDADDLIBS)


if ENABLE_ARCHIVE
TESTS = test_timecode_index \
	test_sd_25i_8b.test \
	test_sd_25i_10b.test \
	test_sd_29i_8b.test \
	test_1080_25i_8b.test \
	test_1080_25i_10b.test \
	test_1080_29i_8b.test \
	test_1080_25p_8b.test \
	test_1080_29p_8b.test \
	test_1080_50p_8b.test \
	test_1080_59p_8b.test \
	test_720_25p_8b.test \
	test_720_29p_8b.test \
	test_720_50p_8b.test \
	test_720_59p_8b.test
endif


AM_CFLAGS = $(LIBMXF_CFLAGS) "-I${top_srcdir}/examples/archive/write"


if ENABLE_ARCHIVE
.PHONY: create-data
create-data:
	${srcdir}/test_sd_25i_8b.test ${srcdir}
	${srcdir}/test_sd_25i_10b.test ${srcdir}
	${srcdir}/test_sd_29i_8b.test ${srcdir}
	${srcdir}/test_1080_25i_8b.test ${srcdir}
	${srcdir}/test_1080_25i_10b.test ${srcdir}
	${srcdir}/test_1080_29i_8b.test ${srcdir}
	${srcdir}/test_1080_25p_8b.test ${srcdir}
	${srcdir}/test_1080_29p_8b.test ${srcdir}
	${srcdir}/test_1080_50p_8b.test ${srcdir}
	${srcdir}/test_1080_59p_8b.test ${srcdir}
	${srcdir}/test_720_25p_8b.test ${srcdir}
	${srcdir}/test_720_29p_8b.test ${srcdir}
	${srcdir}/test_720_50p_8b.test ${srcdir}
	${srcdir}/test_720_59p_8b.test ${srcdir}
endif


EXTRA_DIST = \
	test_sd_25i_8b.test \
	test_sd_25i_10b.test \
	test_sd_29i_8b.test \
	test_1080_25i_8b.test \
	test_1080_25i_10b.test \
	test_1080_29i_8b.test \
	test_1080_25p_8b.test \
	test_1080_29p_8b.test \
	test_1080_50p_8b.test \
	test_1080_59p_8b.test \
	test_720_25p_8b.test \
	test_720_29p_8b.test \
	test_720_50p_8b.test \
	test_720_59p_8b.test \
	test_sd_25i_8b.md5 \
	test_sd_25i_10b.md5 \
	test_sd_29i_8b.md5 \
	test_1080_25i_8b.md5 \
	test_1080_25i_10b.md5 \
	test_1080_29i_8b.md5 \
	test_1080_25p_8b.md5 \
	test_1080_29p_8b.md5 \
	test_1080_50p_8b.md5 \
	test_1080_59p_8b.md5 \
	test_720_25p_8b.md5 \
	test_720_29p_8b.md5 \
	test_720_50p_8b.md5 \
	test_720_59p_8b.md5 \
	check.sh \
	create.sh

