Summary: XView libraries for X11
Name: xview
%define BaseRelease 20250403
Version: 3.2p1.4
Release: 25.29%{?dist}
Distribution: RHEL 8 (Ootpa)
Packager: Vincent S. Cojot <openlook@NOSPAM.cojot.name>
Source0: XView-%{version}-%{BaseRelease}.zip
Source3: Xinitrc.ol
Source4: openwin
Source5: startx.openwin
Source6: openwin.Xdefaults
Source7: openwin-init
Source8: openwin-menu
Source9: openwin-menu-programs
Source10: openwin-menu-clocks
Source11: openwin-menu-d
Source12: openwin-menu-e
Source13: openwin-menu-g
Source14: openwin-menu-s
Source15: openwin-menu-screensave
Source16: openwin-menu-t
Source17: openwin-menu-u
Source18: openwin-menu-xlock
Source28: openwin-menu-OWacomp-stub
Source19: openwin.sh
Source20: openwin.csh
Source21: OpenWin
Source22: toolwait
Source23: owplaces
Source24: Xmodmap.ol
Source25: OpenWindows.desktop
Source26: OWdefaults
Source67: VirtualDesktop
Source50: audio.xpm
Source51: mozicon16.xpm
Source52: xv.xpm
Source54: openwin-i386.conf
Source55: openwin-x86_64.conf
Source63: host_ia32.def
Source64: host_x86_64.def
Patch0: http://ftp.debian.org/debian/pool/main/x/xview/xview_3.2p1.4-24.diff
Patch1: olvwm-4.4.patch
Patch2: xview_xv_error.patch
Patch3: xview_WM_TRANSIENT.SCC.diff
Patch4: xview_scroll_mouse.patch
Patch5: xview_build.patch
Patch6: xview_glibc28_regexp.patch
Patch7: xview_3.2p1.4-25_amd64.diff
Patch8: virtual_c-regexp-fix.patch 
Patch9: xview-sysv-wait-and-signals.patch
License: Distributable
Group: X11/Libraries
ExclusiveArch: i386 i686 x86_64
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-%{_arch}-soft
URL: http://freshmeat.net/projects/XView
BuildRequires: imake
BuildRequires: libX11-devel, libXext-devel, libXt-devel
BuildRequires: libXpm-devel
BuildRequires: bison
BuildRequires: flex
%if "%{?dist}" == ".fc17"
Requires: flex-static
%endif
BuildRequires: ncurses-devel
Requires: libXpm, libX11, libXext, libXt, ncurses, xorg-x11-server-utils, xorg-x11-utils, xorg-x11-fonts-100dpi, xorg-x11-fonts-75dpi, xorg-x11-fonts-misc
%define _enable_debug_packages 1

%changelog
* Thu Apr 03 2025 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.29
- Update /usr/openwin/lib/Xinitrc for debug-launch

* Sun Apr 28 2024 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.28
- Revert some of the previous patches (SIGSEV in olvwm when switching)

* Sun Apr 28 2024 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.27
- Add some extra patches.

* Mon Jan 1 2024 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.26
- Fix man_db.conf handling

* Mon Jan 1 2024 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.25
- Revert to 3.2p1.4-25.24 codebase as some OWacomp no longer compiles with xview-64bit-ggod

* Sun Dec 31 2023 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-26.4
- Yet another bump.

* Sun Dec 31 2023 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-26.3
- rebase on https://github.com/ggodd/xview-64bit due to formatting.

* Sat Dec 30 2023 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-26.2
- i686 and x86_64 builds working. Add -DSYSV_UCONTEXT.

* Sat Dec  9 2023 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-26.1
- Rebase on ggodd xview 64bit branch and attempt to build both arches.

* Sun Jun  4 2023 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.24.el5
- Blank release, global rebuild.

* Tue Dec  8 2020 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.22.el5
- Blank release, global rebuild.

* Tue Sep  5 2017 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.21.el5
- Blank release, global rebuild.

* Wed Nov  2 2016 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.19.el5
- Fixes for building under RHEL7.

* Tue Oct 11 2016 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.18.el5
- Run polkit-1 auth agent if found.

* Mon Oct 03 2016 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.17.el5
- Made user-side configs be sourced last to take precedence over system-wide.

* Mon Jul 20 2015 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.16.el5
- Rebuilt with sigs (RHEL5) issue..

* Sun Jan 19 2014 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.15.el5

* Sat Jan 18 2014 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.14.el5
- Some more minor fixes to openwin startup script (DISPLAY as :X isn't as good as :X.Z ).

* Thu May 23 2013 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.12.el5
- Some minor fixes to openwin env scripts.

* Tue Jan  8 2013 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.11.el5
- Initial attempt at building both 32bit and 64bit packages.

* Mon May 21 2012 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.10.el5
- Add xmkmf templates to /usr/share/X11/config

* Mon May 21 2012 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.9.el5
- Minor changes.

* Mon May 21 2012 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.8.el5
- Added back ssh-agent, if present, to Xinitrc.

* Wed Aug  4 2010 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.7.el5
- Revamped openwin-menu-programs again, added openwin-menu-OWacomp-stub as a stub.

* Mon Jun 21 2010 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.6.el5
- Revamped openwin-menu-programs, added back missing background file for olvwm.

* Mon May 31 2010 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-25.5.el5
- move diffs from 3.2p1.4-24 to 3.2p1.4-25 to xview_glibc28_regexp.patch.
- attempt to improve scroll mouse support patch.

* Tue May 18 2010 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-24.17.el5
- rebuilt olvwm4 tarball (fixes corrupted archive).
- Modified openwin-menus and added some OWacomp entries.
- Append to MANPATH, if present in the users env.

* Wed Mar 10 2010 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-24.15.el5
- Patch for _WM_TRANSIENT, thanks to Eskandar Ensafi.
- Added .el5 dependency for xorg-x11-fonts-misc (olcursor font)

* Wed Dec 30 2009 Vincent S. Cojot <openlook@NOSPAM.cojot.name> 3.2p1.4-24.11.el5
- use ssh-agent, if present.

* Mon Oct 19 2009 Vincent S. Cojot <openlook@NOSPAM.cojot.name>
- Changes to openwin.csh.
- Update to 3.2p1.4-24 from Martin Buck Debian patches (Bug fixes).

* Thu Apr 24 2008 Vincent S. Cojot <openlook@NOSPAM.cojot.name>
- Changes for RHEL5, gnome-sessions bugfixes, gnome-volume-manager.
- Update to 3.2p1.4-21.1 from Martin Buck Debian patches (Bug fixes).

* Tue May  2 2006 Vincent S. Cojot <openlook@NOSPAM.cojot.name>
- Update to 3.2p1.4-21 from Martin Buck Debian patches (Bug fixes).

* Thu Feb 10 2005 Vincent S. Cojot <coyote@NOSPAM.cojot.name>
- Update to 3.2p1.4-19 from Martin Buck Debian patches (Bug fixes).

* Mon Nov 29 2004 Vincent S. Cojot <coyote@NOSPAM.cojot.name>
- Update to 3.2p1.4-18 from Martin Buck Debian patches (Bug fixes).

* Mon Sep 20 2004 Vincent S. Cojot <coyote@NOSPAM.cojot.name>
- Add a few more defaults icons.
- Build debuginfo packages..

* Tue Jun  8 2004 Vincent S. Cojot <coyote@step.polymtl.ca>
- Initial attempt to get this to compile under RHAS3 (Update 2)

* Mon May  6 2002 Vincent S. Cojot <coyote@step.polymtl.ca>
- Update to 3.2p1.4-16 from Martin Buck Debian patches (Bug fixes).

* Mon Oct  8 2001 Vincent S. Cojot <coyote@step.polymtl.ca>
- Apply bit depth and icon depth patches for olvwm-4.1 from Martin's -14
  patches to olvwm-4.4 as well. Reverted to a cleaner patch that applies
  to the real olvwm4.src4 source tree.

* Sat Sep 22 2001 Vincent S. Cojot <coyote@step.polymtl.ca>
- Update to 3.2p1.4-14 from Martin Buck Debian patches (Bug fixes).

* Wed Aug  8 2001 Vincent S. Cojot <coyote@step.polymtl.ca>
- Update to 3.2p1.4-13.1 from Martin Buck Debian patches (13.1 adds
  patches for gcc-3.0 from LaMont Jones <lamont@smallone.fc.hp.com>.

* Wed Aug  8 2001 Vincent S. Cojot <coyote@step.polymtl.ca>
- Update to 3.2p1.4-13 from Martin Buck Debian patches.

* Wed Dec  6 2000 Vincent S. Cojot <coyote@step.polymtl.ca>
- Provide better and improved openwin-menu* stuff and show
  some of olvwm's capabilities.
- Includes /etc/profile.d/openwin*sh files to configure the
  environment for both bourne and C shells...

* Mon Dec  4 2000 Vincent S. Cojot <coyote@step.polymtl.ca>
- Update to 3.2p1.4-10 from Martin Buck Debian patches.
- Include olvwm-4.4 and build it instead of this older olvwm-4.1.

* Thu May 11 2000 Jack Howarth <howarth@bromo.med.uc.edu>
- Uses __va_copy() on powerpc since va_list is array and not pointer

* Thu Jun 3 1999 Volker Kuhlmann <v.kuhlmann@elec.canterbury.ac.nz>

- Compiled for Red Hat 6.0
- Fixed bug with properties program segfaulting (missing locale files)

* Sun Jul 5 1998 Volker Kuhlmann <v.kuhlmann@elec.canterbury.ac.nz>

- The xview rpms contributed for RH 5.0 don't work properly under 5.1. This
  uses the latest debian sources for xview and packs it up into rpms.

%description
XView provides a set of pre-built, user-interface objects such as
canvases, scrollbars, menus, and control panels.  The appearance and
functionality of these objects follow the OPEN LOOK Graphical User
Interface (GUI) specification.

This is the Sun implementation of the OpenLook interface standard, using
the xview libraries. While somewhat outdated and superseded by Motif,
or gtk, it is still very useful, especially in providing compatibility
with older installations.

It is possible that the openwin desktop takes up much less disk space
to install and memory to run than modern desktops, which would make it
a good candidate for old hardware.

%package clients
Requires: xview
Summary: OpenWindows clients.
Group: X11/Window
URL: http://freshmeat.net/projects/XView

%description clients
A number of clients and utilties for OpenWindows, including olwm, textedit,
and more. Also included is olvwm, the OpenWindows virtual window manager,
with support for 24-bit color modes. Now includes olvwm-4.4.

%package devel
Requires: xview
Summary: Header files and static libraries for XView development
Group: Development/Libraries
URL: http://freshmeat.net/projects/XView

%description devel
All the files needed to develop applications that, using the XView libraries,
meet the Open Look interface specifications.

%package devel-examples
Requires: xview-devel
Summary: A number of example programs and tutorials for the XView libraries.
Group: Development/Libraries
URL: http://freshmeat.net/projects/XView

%description devel-examples
Sample programs - with source code - that cover the basics of XView
programming are included in this package.

Also includes documents on the XView API (Application Programming Interface).

%prep
%{__rm} -rf %{buildroot} scripts $RPM_BUILD_ROOT
%setup -q -T -b 0 -n XView

%ifarch x86_64
	%{__install} -m0644 %{SOURCE64} config/host.def
%else
	%{__install} -m0644 %{SOURCE63} config/host.def
%endif
echo '  CFCLAGS += -g' >> $RPM_BUILD_DIR/XView/imake.append

%build
%{__mkdir} -p $RPM_BUILD_ROOT
OPENWINHOME=/usr/openwin bash Build-LinuxXView.bash libs clients olvwm contrib
cd $RPM_BUILD_DIR/XView/clients/xtoolplaces-1.7.1-1 && gmake -f Makefile.simple

%install
DESTDIR=$RPM_BUILD_ROOT bash Build-LinuxXView.bash instlibs instclients instolvwm instcontrib

%{__mkdir} -p $RPM_BUILD_ROOT/etc/profile.d
%{__install} -m0555 $RPM_SOURCE_DIR/openwin.sh $RPM_BUILD_ROOT/etc/profile.d/openwin.sh
%{__install} -m0555 $RPM_SOURCE_DIR/openwin.csh $RPM_BUILD_ROOT/etc/profile.d/openwin.csh

# RHEL3
%{__mkdir} -p $RPM_BUILD_ROOT/etc/X11/gdm/Sessions
%{__install} -m0555 $RPM_SOURCE_DIR/OpenWin $RPM_BUILD_ROOT/etc/X11/gdm/Sessions/OpenWin

# RHEL4
%{__mkdir} -p $RPM_BUILD_ROOT/etc/X11/dm/Sessions
%{__install} -m0555 $RPM_SOURCE_DIR/OpenWindows.desktop $RPM_BUILD_ROOT/etc/X11/dm/Sessions/OpenWindows.desktop

# RHEL5
%{__mkdir} -p $RPM_BUILD_ROOT/usr/share/xsessions
%{__install} -m0555 $RPM_SOURCE_DIR/OpenWindows.desktop $RPM_BUILD_ROOT/usr/share/xsessions/OpenWindows.desktop

%{__mkdir} -p $RPM_BUILD_ROOT/etc/ld.so.conf.d
%{__install} -m0644 $RPM_SOURCE_DIR/openwin-i386.conf $RPM_BUILD_ROOT/etc/ld.so.conf.d/openwin-i386.conf
%ifarch x86_64
	%{__install} -m0644 $RPM_SOURCE_DIR/openwin-x86_64.conf $RPM_BUILD_ROOT/etc/ld.so.conf.d/openwin-x86_64.conf
%endif

%{__mkdir} -p $RPM_BUILD_ROOT/usr/openwin/lib
%ifarch x86_64
	%{__mkdir} -p $RPM_BUILD_ROOT/usr/openwin/%{_lib}
	mv -iv $RPM_BUILD_ROOT/usr/openwin/lib/lib{xview,olgx}.so* $RPM_BUILD_ROOT/usr/openwin/%{_lib}
	mv -iv $RPM_BUILD_ROOT/usr/openwin/lib/lib{xview,olgx}.a $RPM_BUILD_ROOT/usr/openwin/%{_lib}
%endif

%{__mkdir} -p $RPM_BUILD_ROOT/usr/lib
ln -sf ../openwin/lib/.text_extras_menu $RPM_BUILD_ROOT/usr/lib/.text_extras_menu

%{__mkdir} -p $RPM_BUILD_ROOT/usr/X11R6/bin
%{__install} -m0555 $RPM_SOURCE_DIR/startx.openwin $RPM_BUILD_ROOT/usr/X11R6/bin

%{__mkdir} -p $RPM_BUILD_ROOT/usr/openwin/share/include/images
%{__install} -m0444 $RPM_SOURCE_DIR/xv.xpm $RPM_BUILD_ROOT/usr/openwin/share/include/images/xv.xpm
%{__install} -m0444 $RPM_SOURCE_DIR/audio.xpm $RPM_BUILD_ROOT/usr/openwin/share/include/images/audio.xpm
%{__install} -m0444 $RPM_SOURCE_DIR/mozicon16.xpm $RPM_BUILD_ROOT/usr/openwin/share/include/images/mozicon16.xpm
%{__install} -m0444 $RPM_SOURCE_DIR/VirtualDesktop $RPM_BUILD_ROOT/usr/openwin/share/include/images/VirtualDesktop

%{__mkdir} -p $RPM_BUILD_ROOT/usr/openwin/bin
%{__install} -m0555 $RPM_SOURCE_DIR/toolwait $RPM_BUILD_ROOT/usr/openwin/bin/toolwait
%{__install} -m0555 $RPM_SOURCE_DIR/owplaces $RPM_BUILD_ROOT/usr/openwin/bin/owplaces
%{__install} -m0755 $RPM_BUILD_DIR/XView/clients/xtoolplaces-1.7.1-1/xtoolplaces $RPM_BUILD_ROOT/usr/openwin/bin/xtoolplaces
%{__install} -m0555 $RPM_SOURCE_DIR/openwin $RPM_BUILD_ROOT/usr/openwin/bin/openwin

%{__mkdir} -p $RPM_BUILD_ROOT/usr/openwin/lib
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu-programs $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu-programs
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu-OWacomp-stub $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu-OWacomp-stub
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu-clocks $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu-clocks
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu-d $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu-d
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu-e $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu-e
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu-g $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu-g
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu-s $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu-s
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu-screensave $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu-screensave
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu-t $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu-t
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu-u $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu-u
%{__install} -m0444 $RPM_SOURCE_DIR/openwin-menu-xlock $RPM_BUILD_ROOT/usr/openwin/lib/openwin-menu-xlock

# %{__mkdir} -p $RPM_BUILD_ROOT/usr/openwin/lib/config
# %{__install} -m0444 config/XView.cf $RPM_BUILD_ROOT/usr/openwin/lib/config/XView.cf
# %{__install} -m0444 config/XView.lib $RPM_BUILD_ROOT/usr/openwin/lib/config/XView.lib
# %{__install} -m0444 config/XView.obj $RPM_BUILD_ROOT/usr/openwin/lib/config/XView.obj
# %{__install} -m0444 config/XView.prog $RPM_BUILD_ROOT/usr/openwin/lib/config/XView.prog
# %{__install} -m0444 config/XView.rules $RPM_BUILD_ROOT/usr/openwin/lib/config/XView.rules
# %{__install} -m0444 config/XView.tmpl $RPM_BUILD_ROOT/usr/openwin/lib/config/XView.tmpl

%{__mkdir} -p $RPM_BUILD_ROOT/usr/share/X11/config
%{__install} -m0444 config/XView.cf $RPM_BUILD_ROOT/usr/share/X11/config/XView.cf
%{__install} -m0444 config/XView.lib $RPM_BUILD_ROOT/usr/share/X11/config/XView.lib
%{__install} -m0444 config/XView.obj $RPM_BUILD_ROOT/usr/share/X11/config/XView.obj
%{__install} -m0444 config/XView.prog $RPM_BUILD_ROOT/usr/share/X11/config/XView.prog
%{__install} -m0444 config/XView.rules $RPM_BUILD_ROOT/usr/share/X11/config/XView.rules
%{__install} -m0444 config/XView.tmpl $RPM_BUILD_ROOT/usr/share/X11/config/XView.tmpl

%{__mkdir} -p $RPM_BUILD_ROOT/usr/openwin/lib/app-defaults
%{__install} -m0555 $RPM_SOURCE_DIR/Xinitrc.ol $RPM_BUILD_ROOT/usr/openwin/lib/Xinitrc
%{__install} -m0555 $RPM_SOURCE_DIR/openwin-init $RPM_BUILD_ROOT/usr/openwin/lib/openwin-init
### %{__install} -m0444 $RPM_SOURCE_DIR/openwin.Xdefaults $RPM_BUILD_ROOT/usr/openwin/lib/Xdefaults
%{__install} -m0444 $RPM_SOURCE_DIR/OWdefaults $RPM_BUILD_ROOT/usr/openwin/lib/Xdefaults
%{__install} -m0444 $RPM_SOURCE_DIR/Xmodmap.ol $RPM_BUILD_ROOT/usr/openwin/lib/Xmodmap

%{__mkdir} -p $RPM_BUILD_ROOT/usr/openwin/share/locale/C/props
%{__install} -m0444 contrib/misc/props-locale.C $RPM_BUILD_ROOT/usr/openwin/share/locale/C/props/C
%{__install} -m0444 contrib/misc/props-locale.basic_setting $RPM_BUILD_ROOT/usr/openwin/share/locale/C/props/basic_setting

# Strictly speaking, this requires perl, but we won't bother because everything else
# runs without perl and these scripts are not so important.
%{__install} -m0555 contrib/misc/capitalize $RPM_BUILD_ROOT/usr/openwin/bin
%{__install} -m0555 contrib/misc/insert_brackets $RPM_BUILD_ROOT/usr/openwin/bin
%{__install} -m0555 contrib/misc/remove_brackets $RPM_BUILD_ROOT/usr/openwin/bin
%{__install} -m0555 contrib/misc/shift_lines $RPM_BUILD_ROOT/usr/openwin/bin

%{__mkdir} -p $RPM_BUILD_ROOT/usr/openwin/share
cp -a doc $RPM_BUILD_ROOT/usr/openwin/share && %{__chmod} -R a+Xr,u+w $RPM_BUILD_ROOT/usr/openwin/share/doc
%{__install} -m0444 debian/changelog $RPM_BUILD_ROOT/usr/openwin/share/doc/ChangeLog

%{__mkdir} -p $RPM_BUILD_ROOT/usr/openwin/share/src/xview && %{__chmod} -R a+Xr,u+w $RPM_BUILD_ROOT/usr/openwin/share/src/xview
cp -a contrib/examples $RPM_BUILD_ROOT/usr/openwin/share/src/xview
find $RPM_BUILD_ROOT/usr/openwin/share/src/xview/examples/bin -type f -exec %{__chmod} 0755 {} \;
find $RPM_BUILD_ROOT/usr/openwin/share/src/xview -name "*.o" -exec rm -fv {} \;

#%{__install} -m0555 clients/olvwm-4.5/olvwm $RPM_BUILD_ROOT/usr/openwin/bin
#%{__install} -m0444 clients/olvwm-4.5/olvwm.info $RPM_BUILD_ROOT/usr/openwin/lib/help
#%{__install} -m0444 clients/olvwm-4.5/olvwm.man $RPM_BUILD_ROOT/usr/openwin/man/man1/olvwm.1
#%{__install} -m0444 clients/olvwm-4.5/olvwmrc.man $RPM_BUILD_ROOT/usr/openwin/man/man5/olvwm.5
#%{__install} -m0444 clients/olvwm-4.5/olvwm $RPM_BUILD_ROOT/usr/openwin/bin


%post
if [ -f /etc/man_db.conf ]; then
	if ! %{__grep} '^MANPATH_MAP[[:space:]]*/usr/openwin/bin' /etc/man_db.conf > /dev/null; then
		echo -e "MANPATH_MAP\t/usr/openwin/bin\t/usr/openwin/man" >> /etc/man_db.conf
		%{__chmod} 644 /etc/man_db.conf
		test -x /usr/bin/mandb && /usr/bin/mandb
	fi
	if ! %{__grep} '^MANDB_MAP[[:space:]]*/usr/openwin/man' /etc/man_db.conf > /dev/null; then
		echo -e "MANDB_MAP\t/usr/openwin/man\t/var/cache/man/openwin" >> /etc/man_db.conf
		%{__chmod} 644 /etc/man_db.conf
		test -x /usr/bin/mandb && /usr/bin/mandb
	fi
fi

/sbin/ldconfig

%postun

/sbin/ldconfig

%post clients
# Install stub for OWacomp menu
if [ ! -f /usr/openwin/lib/openwin-menu-OWacomp ]; then
	if [ -f /usr/openwin/lib/openwin-menu-OWacomp-stub ]; then
		%{__install} -m0444 /usr/openwin/lib/openwin-menu-OWacomp-stub /usr/openwin/lib/openwin-menu-OWacomp
	fi
fi

%post devel

%post devel-examples

%clean
%{__rm} -fr $RPM_BUILD_ROOT
%{__rm} -rf %{buildroot}

%files
%defattr(-,root,root)
%attr(0555,root,root) /etc/X11/gdm/Sessions/OpenWin
%attr(0555,root,root) /etc/X11/dm/Sessions/OpenWindows.desktop
%attr(0555,root,root) /usr/share/xsessions/OpenWindows.desktop
%attr(0755,root,root) /etc/profile.d/openwin.sh
%attr(0755,root,root) /etc/profile.d/openwin.csh
%attr(0644,root,root) /etc/ld.so.conf.d/openwin-i386.conf
%config /usr/openwin/lib/app-defaults
%dir /usr/openwin/lib
%ifarch x86_64
%attr(0644,root,root) /etc/ld.so.conf.d/openwin-x86_64.conf
%dir /usr/openwin/%{_lib}
%endif
%attr(0755,root,root) /usr/openwin/%{_lib}/libolgx.so.*
%attr(0755,root,root) /usr/openwin/%{_lib}/libxview.so.*
%attr(0755,root,root) /usr/openwin/%{_lib}/libolgx.so
%attr(0755,root,root) /usr/openwin/%{_lib}/libxview.so

%files clients
%defattr(-,root,root)
/usr/lib/.text_extras_menu
/usr/openwin/bin
/usr/openwin/include/bitmaps
/usr/openwin/include/images
/usr/openwin/lib/.text_extras_menu
/usr/openwin/lib/.textswrc
/usr/openwin/lib/.ttyswrc
%config /usr/openwin/lib/Xdefaults
%config /usr/openwin/lib/Xinitrc
%config /usr/openwin/lib/Xmodmap
%config /usr/openwin/lib/openwin-init
%config /usr/openwin/lib/help
%config /usr/openwin/lib/openwin-menu
%config /usr/openwin/lib/openwin-menu-programs
%config /usr/openwin/lib/openwin-menu-OWacomp-stub
%config /usr/openwin/lib/openwin-menu-clocks
%config /usr/openwin/lib/openwin-menu-d
%config /usr/openwin/lib/openwin-menu-e
%config /usr/openwin/lib/openwin-menu-g
%config /usr/openwin/lib/openwin-menu-s
%config /usr/openwin/lib/openwin-menu-screensave
%config /usr/openwin/lib/openwin-menu-t
%config /usr/openwin/lib/openwin-menu-u
%config /usr/openwin/lib/openwin-menu-xlock
%config /usr/openwin/lib/text_extras_menu
%config /usr/openwin/lib/textswrc
%config /usr/openwin/lib/ttyswrc
/usr/openwin/man
/usr/openwin/share/locale/C/props/C
/usr/openwin/share/locale/C/props/basic_setting
/usr/openwin/share/include/images/xv.xpm
/usr/openwin/share/include/images/audio.xpm
/usr/openwin/share/include/images/mozicon16.xpm
/usr/openwin/share/include/images/VirtualDesktop
%attr(0755,root,root) /usr/X11R6/bin/startx.openwin

%files devel
%defattr(-,root,root)
%config /usr/openwin/lib/config
/usr/openwin/include/olgx/*.h
/usr/openwin/include/olgx_private/*.h
/usr/openwin/include/pixrect/*.h
/usr/openwin/include/xview/*.h
/usr/openwin/include/xview_private/*.h
/usr/openwin/%{_lib}/libolgx.a
/usr/openwin/%{_lib}/libxview.a
/usr/share/X11/config/XView.*

%files devel-examples
%defattr(-,root,root)
/usr/openwin/share/doc
/usr/openwin/share/src

