#!/bin/bash
CUR_DATE=`date '+%Y%m%d'`
TMP_DIR=$(cd `dirname $0`;pwd)
SRC_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)
SPEC_FILE=${BASE_DIR}/${SRC_DIR}/OpenWindows.spec
RPM_BASE_DIR=${BASE_DIR}/rpms

# Find spec file...
if [ ! -f ${SPEC_FILE} ]; then
	echo "Unable to find spec file ${SPEC_FILE}!" ; exit 1
fi

# Make sure the base dirs are all there...
for mydir in ${RPM_BASE_DIR}/SRPMS ${RPM_BASE_DIR}/RPMS ${RPM_BASE_DIR}/SPECS ${RPM_BASE_DIR}/BUILD ${RPM_BASE_DIR}/tmp
do
	if [ ! -d ${mydir} ]; then
		mkdir -p ${mydir} || exit 1
	fi	
done

# perform build with hard-coded dist define...
/usr/bin/rpmbuild -ba \
	--define "dist .el5" \
	--define "_topdir ${RPM_BASE_DIR}" \
	--define "_tmppath ${RPM_BASE_DIR}/tmp" \
	${SPEC_FILE}

