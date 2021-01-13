#!/bin/sh

MD5TOOL=../../../test/file_md5


MD5_FILE=$1
shift

OUTPUT_FILE=/tmp/libmxf_test_$$.mxf


if ! ./test_write_archive_mxf --regtest $@ 3 ${OUTPUT_FILE} >/dev/null 2>/dev/null
then
  rm -f ${OUTPUT_FILE}
  exit 1
fi


$MD5TOOL < ${OUTPUT_FILE} > ${MD5_FILE}

rm -f ${OUTPUT_FILE}


exit $RESULT
