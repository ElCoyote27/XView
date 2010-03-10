#!/bin/bash
CUR_DATE=`date '+%Y%m%d'`
TMP_DIR=$(cd `dirname $0`;pwd)
SRC_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)
SPEC_FILE=${BASE_DIR}/${SRC_DIR}/OWacomp.spec
RPM_BASE_DIR=${BASE_DIR}/build

# Get version from library
if [ -f ${BASE_DIR}/libdeskset/ds_relname.h ]; then
        CUR_VERSION=`awk '{if ($2 ~ /_RELEASE/ ) print $3}' ${BASE_DIR}/libdeskset/ds_relname.h|sed -e 's/"//g' -e 's/v//'`
else
        echo "Unable to find version in ${BASE_DIR}/libdeskset/ds_relname.h!" ; exit 1
fi

# Find spec file...
if [ ! -f ${SPEC_FILE} ]; then
	echo "Unable to find spec file ${SPEC_FILE}!" ; exit 1
fi

# Make sure the base dirs are all there...
for mydir in ${RPM_BASE_DIR}/SOURCES ${RPM_BASE_DIR}/SRPMS ${RPM_BASE_DIR}/RPMS ${RPM_BASE_DIR}/SPECS ${RPM_BASE_DIR}/BUILD ${RPM_BASE_DIR}/tmp
do
	if [ ! -d ${mydir} ]; then
		mkdir -p ${mydir} || exit 1
	fi	
done

#
TMP_REL=`echo ${RPM_BASE_DIR}/SOURCES/OWacomp-${CUR_VERSION}-*.zip|xargs -n1|tail -1`
# Sanity check
if [ ! -f ${TMP_REL} ]; then
	echo "Missing zip file: ${TMP_REL}!" ; exit 1
fi
BASE_RELEASE=`basename $TMP_REL .zip|sed -e "s/OWacomp-${CUR_VERSION}-//"`

# In case we missed them:
grep -q "^Version: ${CUR_VERSION}\$" ${SPEC_FILE}
if [ $? -eq 1 ]; then
	echo "Version mismatch! Editing ${SPEC_FILE} with \"Version: ${CUR_VERSION}\"..."
	perl -pi -e "s@^Version: .*\$@Version: ${CUR_VERSION}@" ${SPEC_FILE}
fi

grep -q "^%define BaseRelease ${BASE_RELEASE}\$" ${SPEC_FILE}
if [ $? -eq 1 ]; then
	echo "BaseRelease mismatch! Editing ${SPEC_FILE} with \"BaseRelease: ${BASE_RELEASE}\"..."
	perl -pi -e "s@^%define BaseRelease .*\$@%define BaseRelease ${BASE_RELEASE}@" ${SPEC_FILE}
fi

/usr/bin/rpmbuild -ba \
	--define "dist .el5" \
	--define "_topdir ${RPM_BASE_DIR}" \
	--define "_tmppath ${RPM_BASE_DIR}/tmp" \
	${SPEC_FILE}

