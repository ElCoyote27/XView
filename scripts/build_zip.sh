#!/bin/bash
CUR_DATE=`date '+%Y%m%d'`
#
[ "$BASH" ] && function whence
{
	type -p "$@"
}
#
BASE_DIR="$(cd $(/usr/bin/dirname $(whence -- $0 || echo $0));cd ..;pwd)"
SRC_DIR="XView"

# Get version from library
if [ -f ${BASE_DIR}/${SRC_DIR}/lib/libxview/base/xview_impl.h ]; then
	CUR_VERSION="3.2p1.4"
else
	CUR_VERSION="ALPHA"
fi

ZIP_NAME="${BASE_DIR}/build/SOURCES/XView-${CUR_VERSION}-${CUR_DATE}.zip"
SPEC_FILE="${BASE_DIR}/scripts/XView.spec"

# Update spec file with current version and date
if [ -f "${SPEC_FILE}" ]; then
	grep -q "^Version: ${CUR_VERSION}\$" "${SPEC_FILE}"
	if [ $? -eq 1 ]; then
		echo "Updating ${SPEC_FILE}: Version: ${CUR_VERSION}"
		perl -pi -e "s@^Version: .*\$@Version: ${CUR_VERSION}@" "${SPEC_FILE}"
	fi
	grep -q "^%define BaseRelease ${CUR_DATE}\$" "${SPEC_FILE}"
	if [ $? -eq 1 ]; then
		echo "Updating ${SPEC_FILE}: BaseRelease: ${CUR_DATE}"
		perl -pi -e "s@^%define BaseRelease .*\$@%define BaseRelease ${CUR_DATE}@" "${SPEC_FILE}"
	fi
fi

echo "Building ${ZIP_NAME} from ${BASE_DIR}/${SRC_DIR} ..."
OUT_DIR=$(dirname ${ZIP_NAME})
if [ ! -d ${OUT_DIR} ]; then
	mkdir -p ${OUT_DIR}
fi

# Exclude local arch build trees (gmake output), objects, and nested build dirs.
# Use *i386-Linux* not */i386-Linux/* — the latter misses paths with multiple
# segments before the arch directory (e.g. .../guide/i386-Linux/).
if [ -x /usr/bin/zip ]; then
	cd ${BASE_DIR}
	/usr/bin/zip -9qr ${ZIP_NAME} ${SRC_DIR} scripts \
		-x '*.o' \
		-x 'core' \
		-x "${SRC_DIR}/build/*" \
		-x '*i386-Linux*' \
		-x '*x86_64-Linux*' \
		-x '*sparc-SunOS*' \
		-x '*i386-SunOS*'
fi
