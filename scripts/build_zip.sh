#!/bin/bash
CUR_DATE=`date '+%Y%m%d'`
TMP_DIR=$(cd `dirname $0`;cd ..;pwd)
SRC_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)
ZIP_NAME="${HOME}/ow${CUR_DATE}.zip"
echo "Building ${ZIP_NAME} from ${BASE_DIR}/${SRC_DIR}.."
cd ${BASE_DIR}
#zip -9qr ${ZIP_NAME} ${SRC_DIR} -x */i386-Linux/*
zip -9qr ${ZIP_NAME} ${SRC_DIR}

