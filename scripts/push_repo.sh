#!/bin/bash
# Rev: $Id: push_repo.sh,v 1.2 2010/05/18 08:34:14 vcojot Exp $

# Local variables
CUR_DATE=`date '+%Y%m%d'`
TMP_DIR=$(cd `dirname $0`;pwd)
SRC_DIR=$(basename $TMP_DIR)
BASE_DIR=$(dirname $TMP_DIR)
RPM_BASE_DIR=${BASE_DIR}/build
DEST_DIR=thor:Vincent/Code

# Main routine
rsync -avz --exclude=${RPM_BASE_DIR}/BUILD/\* ${BASE_DIR} ${DEST_DIR}
