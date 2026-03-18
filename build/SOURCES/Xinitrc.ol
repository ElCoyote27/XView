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

# GNOME Keyring for application secrets (Chrome, etc.)
if [ -x /usr/bin/gnome-keyring-daemon ]; then
	eval $(/usr/bin/gnome-keyring-daemon --start --components=pkcs11,secrets)
	export GNOME_KEYRING_CONTROL
fi

# start some nice programs
if [ -x ${HOME}/.openwin-init ]; then
	if [ -x /usr/bin/dbus-launch ]; then
		/usr/bin/dbus-launch --exit-with-session ${HOME}/.openwin-init
	else
		${HOME}/.openwin-init
	fi
else
	if [ -x ${OPENWINHOME}/lib/openwin-init ]; then
		if [ -x /usr/bin/dbus-launch ]; then
			/usr/bin/dbus-launch --exit-with-session ${OPENWINHOME}/lib/openwin-init
		else
			${OPENWINHOME}/lib/openwin-init
		fi
	fi
fi

# Polkit authentication agent for UDisks2 mounting and other privileged actions
if [ -x /usr/libexec/polkit-gnome-authentication-agent-1 ]; then
	/usr/libexec/polkit-gnome-authentication-agent-1 &
fi

# UDisks2 polkit rule for passwordless removable media mounting
# Uncomment if your system requires an explicit polkit rule for
# udisksctl mount/eject to work without authentication prompts.
#ow_polkit_rule=/etc/polkit-1/rules.d/10-openwin-udisks2.rules
#if [ ! -f ${ow_polkit_rule} ] && [ -d /etc/polkit-1/rules.d ]; then
#	if [ -w /etc/polkit-1/rules.d ]; then
#		cat > ${ow_polkit_rule} << 'POLKIT_EOF'
#polkit.addRule(function(action, subject) {
#    if ((action.id == "org.freedesktop.udisks2.filesystem-mount" ||
#         action.id == "org.freedesktop.udisks2.filesystem-mount-other-seat" ||
#         action.id == "org.freedesktop.udisks2.eject-media") &&
#        subject.local && subject.active) {
#        return polkit.Result.YES;
#    }
#});
#POLKIT_EOF
#	fi
#fi

# Window Manager
if [ ! -z "$WINDOWMANAGER" ]; then
	xsetroot -def
	exec $WINDOWMANAGER
else
	exec olvwm
fi
