#!/bin/bash
# $Id: rcs2git.sh,v 1.1 2017/05/11 20:17:22 raistlin Exp $
#
[ "$BASH" ] && function whence
{
	type -p "$@"
}
#
PATH_SCRIPT="$(cd $(/usr/bin/dirname $(whence -- $0 || echo $0));cd ..;pwd)"

OWTOOL="${HOME}/owgitscript.sh"
rm -f ${OWTOOL}
echo -n "Building ${OWTOOL}..."
cd ${PATH_SCRIPT}
for myd in $(find . -name RCS -type d)
do
	echo "cd ${PATH_SCRIPT}/$(dirname $myd)" >> ${OWTOOL}
	(cd $myd && rlog *,v | \
		awk -f ${PATH_SCRIPT}/scripts/rcs2data.awk| \
		sort | \
		awk -f ${PATH_SCRIPT}/scripts/data2sh.awk >> ${OWTOOL} )
done
echo " Done!"
