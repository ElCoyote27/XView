#!/bin/bash
CUR_DATE=`date '+%Y%m%d'`
#
[ "$BASH" ] && function whence
{
	type -p "$@"
}
#
BASE_DIR="$(cd $(/usr/bin/dirname $(whence -- $0 || echo $0));cd ..;pwd)"
for SRC_DIR in XView-32 XView-64
do

# Get version from library
if [ -f ${BASE_DIR}/${SRC_DIR}/lib/libxview/base/xview_impl.h ]; then
	CUR_VERSION="3.2p1.4"
else
	CUR_VERSION="ALPHA"
fi

ZIP_NAME="${BASE_DIR}/build/SOURCES/${SRC_DIR}-${CUR_VERSION}-${CUR_DATE}.zip"

echo "Building ${ZIP_NAME} from ${BASE_DIR}/${SRC_DIR} ..."
OUT_DIR=$(dirname ${ZIP_NAME})
if [ ! -d ${OUT_DIR} ]; then
	mkdir -p ${OUT_DIR}
fi

if [ -x /usr/bin/zip ]; then
	cd ${BASE_DIR}
	/usr/bin/zip -9qr ${ZIP_NAME} ${SRC_DIR} scripts -x '*.o' -x 'core' -x "${SRC_DIR}/build/*"
fi

done
