# X11 legacy compat
if [ "X${X11HOME}" = "X" ]; then
	X11HOME="/usr/X11R6"
fi

if [ "X${PATH_SOCKET}" = "X" ]; then
	PATH_SOCKET="/tmp/.X11-unix"
fi

if [ "X${X11_PIPES}" = "X" ]; then
	X11_PIPES="/tmp/.X11-pipe"
fi
export X11HOME PATH_SOCKET X11_PIPES

# OpenWindows initialization script (sh)
if [ "X${OPENWINHOME}" = "X" ]; then
	OPENWINHOME="/usr/openwin"
fi

if [ "X${XAPPLRESDIR}" = "X" ]; then
	XAPPLRESDIR=${OPENWINHOME}/lib/app-defaults
fi

if [ "X${GUIDEHOME}" = "X" ]; then
	GUIDEHOME="${OPENWINHOME}/lib/guide"
fi

if [ "X${HELPPATH}" = "X" ]; then
	HELPPATH="${OPENWINHOME}/lib/help"
fi

owman="${OPENWINHOME}/man"
if [ "X${MANPATH}" != "X" ]; then
	if ! echo $MANPATH |grep -q "${owman}" ; then
		MANPATH="${MANPATH}:${OPENWINHOME}/man"
	fi
fi

owpath="${OPENWINHOME}/bin"
if ! echo $PATH | grep -q "${owpath}" ; then
	PATH="${PATH}:${owpath}"
fi
export OPENWINHOME GUIDEHOME XAPPLRESDIR HELPPATH MANPATH PATH

