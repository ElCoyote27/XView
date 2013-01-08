#!/bin/bash
CUR_DATE=`date '+%Y%m%d'`
TMP_DIR=$(cd `dirname $0`;pwd)
SRC_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)
SPEC_FILE=${BASE_DIR}/${SRC_DIR}/XView.spec
RPM_BASE_DIR=${BASE_DIR}/build
rpmextras=""

# Find spec file...
if [ ! -f ${SPEC_FILE} ]; then
	echo "Unable to find spec file ${SPEC_FILE}!" ; exit 1
fi

# Make sure the base dirs are all there...
for mydir in ${RPM_BASE_DIR}/SOURCES ${RPM_BASE_DIR}/SRPMS ${RPM_BASE_DIR}/RPMS ${RPM_BASE_DIR}/SPECS ${RPM_BASE_DIR}/BUILD ${RPM_BASE_DIR}/tmp ${RPM_BASE_DIR}/BUILD/`uname -i`
do
	if [ ! -d ${mydir} ]; then
		mkdir -vp ${mydir} || exit 1
	fi	
done

#
#grep -q "^%define BaseRelease ${BASE_RELEASE}\$" ${SPEC_FILE}
#if [ $? -eq 1 ]; then
#	echo "BaseRelease mismatch! Editing ${SPEC_FILE} with \"BaseRelease: ${BASE_RELEASE}\"..."
#	perl -pi -e "s@^%define BaseRelease .*\$@%define BaseRelease ${BASE_RELEASE}@" ${SPEC_FILE}
#fi

# Checks for libhal
#if [ -x /usr/bin/pkg-config ]; then
#	/usr/bin/pkg-config  --silence-errors hal
#	libhal=$?
#	/usr/bin/pkg-config  --silence-errors dbus-glib-1
#	dbus=$?
#	if [ $dbus -eq 0 -a $libhal -eq 0 ]; then
#		echo 'Using hal and dbus/dbus-glibc-1 for xvfilemgr..'
#		rpmextras="--with libhal"
#	else
#		echo 'Unable to use hal and/or dbus-glibc-1 for xvfilemgr, Skipping...'
#	fi
#fi

/usr/bin/rpmbuild -ba \
	${rpmextras} \
	--define "dist .el5" \
	--define "_topdir ${RPM_BASE_DIR}" \
	--define "_builddir ${RPM_BASE_DIR}/BUILD/`uname -i`" \
	--define "_tmppath ${RPM_BASE_DIR}/tmp" \
	${SPEC_FILE}
