# XView - OPEN LOOK Toolkit for X11

XView (X Window-System-based Visual/Integrated Environment for Workstations)
is a user-interface toolkit providing pre-built, interactive UI objects such
as canvases, scrollbars, menus, and control panels. The appearance and
functionality follow the
[OPEN LOOK](https://en.wikipedia.org/wiki/OPEN_LOOK) Graphical User
Interface specification.

This repository contains the XView 3.2p1.4 libraries and core clients,
maintained and ported for modern **RHEL/Fedora x86_64** systems.

## History

XView was originally developed by Sun Microsystems in the early 1990s as
part of the OpenWindows desktop environment for SunOS and Solaris. It was
released as open source and subsequently ported to Linux. This fork focuses
on keeping XView functional on modern Red Hat Enterprise Linux (RHEL 8 and
RHEL 9) with GCC, while preserving full ABI and API compatibility with the
original toolkit.

## Screenshots

See the [OpenWindows website](https://github.com/ElCoyote27/XView) for
screenshots and binary downloads.

## RPM Packages

The build produces four RPM sub-packages:

| Package | Description |
|---------|-------------|
| `xview` | Core runtime libraries (`libxview`, `libolgx`) and OpenWindows environment |
| `xview-clients` | Window managers (`olwm`, `olvwm`) and tools (`textedit`, `cmdtool`, `clock`, `props`) |
| `xview-devel` | Headers, static libraries, and Imake templates for XView development |
| `xview-devel-examples` | Sample programs with source code covering XView programming basics |

## Code Layout

```
XView/
  lib/
    libxview/       Core XView toolkit (~30 subsystems: panel, menu, canvas,
                    scrollbar, notice, notify, frame, icon, selection, ...)
    libolgx/        OPEN LOOK graphics library (rendering primitives)
    pixrect/        Legacy SunOS pixrect compatibility shim
  clients/
    olwm/           OPEN LOOK Window Manager
    olvwm-4.5/      OPEN LOOK Virtual Window Manager (24-bit color support)
    cmdtool/        Command tool / shell terminal
    textedit/       Text editor
    clock/          Analog/digital clock
    props/          Workspace properties
    xtoolplaces-1.7.1-1/  Session save/restore utility
  contrib/examples/ Per-component demo programs
  util/             Build utilities (cpp, xgettext, msgfmt, soelim)
  config/           Imake configuration (XView.cf, XView.tmpl)
  doc/              API documentation and release notes
  fonts/            OPEN LOOK fonts
  images/           Icons and pixmaps
scripts/
  build_zip.sh      Create source archive for RPM build
  build_rpms.sh     Build RPMs (32-bit, with optional GPG signing)
  publish_release.sh  Tag and push releases to GitHub/GitLab
  XView.spec        RPM spec file
```

## Build Requirements

- RHEL 8 or RHEL 9 (x86_64)
- `imake`, `bison`, `flex`, `ncurses-devel`
- `libX11-devel`, `libXext-devel`, `libXt-devel`, `libXpm-devel`
- 32-bit build environment (`linux32`)

## Building

### Quick iterative builds

```bash
ssh rh8x64
cd /path/to/XView/build/BUILD/rh8x64/XView
make                    # libraries
cd clients/olvwm-4.1 && make   # specific client
```

### Full RPM build

```bash
cd scripts/
./build_zip.sh          # creates build/SOURCES/XView-3.2p1.4-YYYYMMDD.zip
./build_rpms.sh --sign  # builds and signs RPMs
```

## Installation

Install prefix: `/usr/openwin/`

```bash
# From the yum/dnf repository:
dnf install xview xview-clients

# Start OpenWindows session:
startx /usr/openwin/bin/openwin
```

## Dependencies

- Runtime: `libX11`, `libXext`, `libXt`, `libXpm`, `ncurses`
- The [OWacomp](https://github.com/ElCoyote27/OWacomp) package provides
  additional DeskSet-style applications built on top of XView.

## License

Nonexclusive, royalty-free copyright and design patent license granted by
Sun Microsystems, Inc. See [LEGAL_NOTICE](XView/LEGAL_NOTICE) for full
terms.

## Author

Maintained by Vincent S. Cojot
