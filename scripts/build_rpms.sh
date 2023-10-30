#!/bin/bash
CUR_DATE=$(date '+%Y%m%d')
TMP_DIR=$(cd `dirname $0`;pwd)
SRC_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)
RPM_BASE_DIR=${BASE_DIR}/build
RPM_BUILD_DIR=${RPM_BASE_DIR}/BUILD/$(uname -n)
RPM_TMP_PATH=${RPM_BASE_DIR}/tmp/$(uname -n)

VERSION="$(lsb_release -sr|cut -f1 -d.)"
DIST=".el${VERSION}"
rpmextras=""

# Get version from library
CUR_VERSION="3.2p1.4"

# Find spec file...
if [ ! -f ${SPEC_FILE} ]; then
	echo "Unable to find spec file ${SPEC_FILE}!" ; exit 1
fi

# Make sure the base dirs are all there...
for mydir in ${RPM_BASE_DIR}/SOURCES ${RPM_BASE_DIR}/SRPMS ${RPM_BASE_DIR}/RPMS ${RPM_BASE_DIR}/SPECS ${RPM_BASE_DIR}/BUILD ${RPM_BUILD_DIR} ${RPM_TMP_PATH}
do
	if [ ! -d ${mydir} ]; then
		mkdir -p ${mydir} || exit 1
	fi
done

# Only build the source rpm for el6 (as of 201705)
case ${VERSION} in
	5)
		rpm_pkgs="-bb"
		;;
	6|7|8)
		rpm_pkgs="-ba"
		;;
esac

#
for ARCH_DIR in XView-32 XView-64
do
SPEC_FILE=${BASE_DIR}/${SRC_DIR}/${ARCH_DIR}.spec
TMP_REL=$(echo ${RPM_BASE_DIR}/SOURCES/${ARCH_DIR}-${CUR_VERSION}-*.zip|xargs -n1|tail -1)
# Sanity check
if [ ! -f ${TMP_REL} ]; then
	echo "Missing zip file: ${TMP_REL}!" ; exit 1
fi
BASE_RELEASE=$(basename $TMP_REL .zip|sed -e "s/${ARCH_DIR}-${CUR_VERSION}-//")

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

done

# Checks for libhal
if [ -x /usr/bin/pkg-config ]; then
	/usr/bin/pkg-config  --silence-errors hal
	libhal=$?
	/usr/bin/pkg-config  --silence-errors dbus-glib-1
	dbus=$?
	if [ $dbus -eq 0 -a $libhal -eq 0 ]; then
		echo 'Using hal and dbus/dbus-glibc-1 for xvfilemgr..'
		rpmextras="--with libhal"
	else
		echo 'Unable to use hal and/or dbus-glibc-1 for xvfilemgr, Skipping...'
	fi
fi

if [ "x$(uname -p)" = "xx86_64" ]; then
	BOOTSTRAP="setarch i686"
else
	BOOTSTRAP=
fi

# Build 32bit on el7
if [[ "${DIST}" = ".el7" ]]; then
	BOOTSTRAP="setarch i686"
echo ${BOOTSTRAP} /usr/bin/rpmbuild ${rpm_pkgs} \
	${rpmextras} --sign \
	--target i686 \
	--define "dist ${DIST}" \
	--define "_topdir ${RPM_BASE_DIR}" \
	--define "_builddir ${RPM_BUILD_DIR}" \
	--define "_tmppath ${RPM_TMP_PATH}" \
	${SPEC_FILE}
fi

# Build 64bit on el8
if [[ "${DIST}" = ".el8" ]]; then
	BOOTSTRAP="setarch x86_64"
echo ${BOOTSTRAP} /usr/bin/rpmbuild ${rpm_pkgs} \
	${rpmextras} --sign \
	--target x86_64 \
	--define "dist ${DIST}" \
	--define "_topdir ${RPM_BASE_DIR}" \
	--define "_builddir ${RPM_BUILD_DIR}" \
	--define "_tmppath ${RPM_TMP_PATH}" \
	${SPEC_FILE}
fi

