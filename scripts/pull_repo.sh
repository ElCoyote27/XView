#!/bin/bash
# Rev: $Id: pull_repo.sh,v 1.4 2013/01/03 10:41:51 raistlin Exp $

# Local variables
CUR_DATE=`date '+%Y%m%d'`
TMP_DIR=$(cd `dirname $0`;pwd)
DEST_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)
RPM_BASE_DIR=${BASE_DIR}/build
SRC_DIR=thor:World/Vincent/Code/GIT/XView

#
RSYNC_CMD=rsync
RSYNC_OPTIONS="-auvz --bwlimit=2048 --stats --delete \
	--exclude=`basename ${BASE_DIR}`/build/BUILD \
	--exclude=`basename ${BASE_DIR}`/build/tmp"

# Main routine
${RSYNC_CMD} ${RSYNC_OPTIONS} ${SRC_DIR} `dirname ${BASE_DIR}`
