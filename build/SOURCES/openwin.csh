# X11 legacy compat
setenv X11HOME "/usr"
setenv PATH_SOCKET "/tmp/.X11-unix"
setenv X11_PIPES "/tmp/.X11-pipe"

# OpenWindows initialization script (csh)
if ( ! $?OPENWINHOME ) then
	setenv OPENWINHOME /usr/openwin
endif
setenv GUIDEHOME ${OPENWINHOME}/lib/guide
setenv HELPPATH ${OPENWINHOME}/lib/help
setenv XAPPLRESDIR ${OPENWINHOME}/lib/app-defaults
set owpath="${OPENWINHOME}/bin"
echo ${PATH} | grep -q ${owpath}
if ( $status == 0 ) then
  exit
endif
setenv PATH "${owpath}:${PATH}"
