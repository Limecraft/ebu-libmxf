#!/bin/sh

MD5TOOL=../../../test/file_md5


MD5_FILE=$1
shift


if ! ./test_write_archive_mxf --regtest $@ 3 /tmp/libmxf_test.mxf >/dev/null 2>/dev/null
then
  rm -f /tmp/libmxf_test.mxf
  exit 1
fi


$MD5TOOL < /tmp/libmxf_test.mxf > ${MD5_FILE}

rm -f /tmp/libmxf_test.mxf /tmp/libmxf_test.mxf.md5


exit $RESULT
