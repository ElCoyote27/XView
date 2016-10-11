#!/bin/sh
# $XConsortium: xinitrc.cpp,v 1.4 91/08/22 11:41:34 rws Exp $
OPENWINHOME=/usr/openwin
export OPENWINHOME
#
sysresources=/etc/X11/Xresources
sysmodmap=/etc/X11/Xmodmap
sysxviewmodmap=${OPENWINHOME}/lib/Xmodmap
sysxviewresources=${OPENWINHOME}/lib/Xdefaults
xviewresources=${HOME}/.Xdefaults
userresources=${HOME}/.Xresources
usermodmap=${HOME}/.Xmodmap

# Display startup logo
if [ -x ${OPENWINHOME}/bin/xcenter -a -f ${OPENWINHOME}/etc/lxxview.xbm ]; then
    ${OPENWINHOME}/bin/xcenter -bitcenter ${OPENWINHOME}/etc/lxxview.xbm && sleep 2
fi

# merge in defaults and keymaps

# System-wide Xresources
if [ -f ${sysresources} ]; then
    echo     xrdb -merge ${sysresources}
    xrdb -merge ${sysresources}
fi

# System-wide X11 Xmodmap
if [ -f ${sysmodmap} ]; then
    echo xmodmap ${sysmodmap}
    xmodmap ${sysmodmap}
fi

# System-wide OpenWindows Xmodmap
if [ -f ${sysxviewmodmap} ]; then
    echo xmodmap ${sysxviewmodmap}
    xmodmap ${sysxviewmodmap}
fi

# System-wide Xdefaults
if [ -f ${sysxviewresources} ]; then
    xrdb -merge ${sysxviewresources}
fi

# User .Xresources
if [ -f ${userresources} ]; then
    echo xrdb -merge ${userresources}
    xrdb -merge ${userresources}
fi

# User Xdefaults
if [ -f ${xviewresources} ]; then
    xrdb -merge ${xviewresources}
fi

# User Xmodmap
if [ -f ${usermodmap} ]; then
    echo xmodmap ${usermodmap}
    xmodmap ${usermodmap}
fi

# Start ssh-agent
if [ -x /usr/bin/ssh-agent ]; then
	eval `/usr/bin/ssh-agent`
fi

# start some nice programs
if [ -x ${HOME}/.openwin-init ]; then
	${HOME}/.openwin-init
else
	if [ -x ${OPENWINHOME}/lib/openwin-init ]; then
		${OPENWINHOME}/lib/openwin-init
	fi
fi

# GNOME Volume Manager
if [ -x /usr/bin/gnome-volume-manager ]; then
        /usr/bin/gnome-volume-manager &
fi

# Polkit so users can run Gnome-Related tools
if [ -x /usr/libexec/polkit-gnome-authentication-agent-1 ]; then
	/usr/libexec/polkit-gnome-authentication-agent-1 &
fi

# Window Manager
if [ ! -z "$WINDOWMANAGER" ]; then
	xsetroot -def
	exec $WINDOWMANAGER
else
	exec olvwm
fi
