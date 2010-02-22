#!/bin/bash
CUR_DATE=`date '+%Y%m%d'`
TMP_DIR=$(cd `dirname $0`;cd ..;pwd)
SRC_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)

# Get version from library
if [ -f ${BASE_DIR}/${SRC_DIR}/libdeskset/ds_relname.h ]; then
	CUR_VERSION=`awk '{if ($2 ~ /_RELEASE/ ) print $3}' ${BASE_DIR}/${SRC_DIR}/libdeskset/ds_relname.h|sed -e 's/"//g' -e 's/v//'`
else
	CUR_VERSION="ALPHA"
fi

ZIP_NAME="${HOME}/OpenWindows-${CUR_VERSION}-${CUR_DATE}.zip"
echo "Building ${ZIP_NAME} from ${BASE_DIR}/${SRC_DIR}.."
cd ${BASE_DIR}
#zip -9qr ${ZIP_NAME} ${SRC_DIR} -x */i386-Linux/*
zip -9r ${ZIP_NAME} ${SRC_DIR} -x *.o

