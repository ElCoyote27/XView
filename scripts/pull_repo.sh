#!/bin/bash
# Rev: $Id: pull_repo.sh,v 1.2 2012/05/21 10:31:32 vcojot Exp $

# Local variables
CUR_DATE=`date '+%Y%m%d'`
TMP_DIR=$(cd `dirname $0`;pwd)
DEST_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)
RPM_BASE_DIR=${BASE_DIR}/build
SRC_DIR=thor:Vincent/Code/XView

#
RSYNC_CMD=rsync
RSYNC_OPTIONS="-auvz --bwlimit=2048 --stats \
	--exclude=`basename ${BASE_DIR}`/build/BUILD \
	--exclude=`basename ${BASE_DIR}`/build/tmp"

# Main routine
${RSYNC_CMD} ${RSYNC_OPTIONS} ${SRC_DIR} `dirname ${BASE_DIR}`
