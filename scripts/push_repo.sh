#!/bin/bash
# Rev: $Id: push_repo.sh,v 1.3 2010/05/18 08:43:56 vcojot Exp $

# Local variables
CUR_DATE=`date '+%Y%m%d'`
TMP_DIR=$(cd `dirname $0`;pwd)
SRC_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)
RPM_BASE_DIR=${BASE_DIR}/build
DEST_DIR=thor:Vincent/Code

#
RSYNC_CMD=rsync
RSYNC_OPTIONS="-avnz --exclude=XView/build/BUILD"

# Main routine
${RSYNC_CMD} ${RSYNC_OPTIONS} ${BASE_DIR} ${DEST_DIR}
