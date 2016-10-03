#!/bin/bash
CUR_DATE=$(date '+%Y%m%d')
TMP_DIR=$(cd `dirname $0`;pwd)
SRC_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)
RPM_BASE_DIR=${BASE_DIR}/build

VERSION="$(awk '{ print $7 }' /etc/redhat-release|cut -c1)"
DIST=".el${VERSION}"
rpmextras=""

# Make sure the base dirs are all there...
for mydir in ${RPM_BASE_DIR}/BUILDROOT/ ${RPM_BASE_DIR}/BUILD/
do
	if [ -d ${mydir} ]; then
		cd ${mydir} && /bin/rm -rfv ./*
	fi	
done
