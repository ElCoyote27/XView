#!/bin/bash
# Rev: $Id: push_repo.sh,v 1.6 2010/05/20 17:07:24 vcojot Exp $

# Local variables
CUR_DATE=`date '+%Y%m%d'`
TMP_DIR=$(cd `dirname $0`;pwd)
SRC_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)
RPM_BASE_DIR=${BASE_DIR}/build
DEST_DIR=thor:Vincent/Code

#
RSYNC_CMD=rsync
RSYNC_OPTIONS="-avz \
	--exclude=`basename ${BASE_DIR}`/build/BUILD \
	--exclude=`basename ${BASE_DIR}`/build/tmp"

# Main routine
${RSYNC_CMD} ${RSYNC_OPTIONS} ${BASE_DIR} ${DEST_DIR}
