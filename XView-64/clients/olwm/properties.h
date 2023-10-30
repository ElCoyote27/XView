#ident	"@(#)properties.h	26.8	93/06/28 SMI"

/*
 *      (c) Copyright 1989 Sun Microsystems, Inc.
 */

/*
 *      Sun design patents pending in the U.S. and foreign countries. See
 *      LEGAL_NOTICE file for terms of the license.
 */

#ifndef _OLWM_PROPERTIES_H
#define _OLWM_PROPERTIES_H
#include "win.h"
/*
 * Open Look Window Attribute structure
 */
typedef struct {
    unsigned long	flags;
    Atom		win_type;
    Atom		menu_type;
    unsigned long	pin_initial_state;
    unsigned long	cancel;
} OLWinAttr;
#define OLWINATTRLENGTH (sizeof(OLWinAttr)/sizeof(unsigned long))

/* 
 * Values for flags in OLWinAttr
 */
#define WA_WINTYPE	(1<<0)
#define WA_MENUTYPE	(1<<1)
#define WA_PINSTATE	(1<<2)
#define WA_CANCEL	(1<<3)

/*
 * Values for flags of available top-level window-management properties
 */
#define WMClassAvail		(1<<0)
#define WMNameAvail		(1<<1)
#define WMIconNameAvail		(1<<2)
#define WMNormalHintsAvail	(1<<3)
#define WMHintsAvail		(1<<4)
#define WMTransientForAvail	(1<<5)
#define WMProtocolsAvail	(1<<6)
#define WMColormapWindowsAvail	(1<<7)
#define WMStateAvail		(1<<8)
#define OLWinAttrAvail		(1<<9)
#define OLDecorAddAvail		(1<<10)
#define OLDecorDelAvail		(1<<11)
#define OLWindowStateAvail	(1<<12)
#define OLLeftFooterAvail	(1<<13)
#define OLRightFooterAvail	(1<<14)
#ifdef OW_I18N_L4
#define OLLeftIMStatusAvail	(1<<15)
#define OLRightIMStatusAvail	(1<<16)
#endif

#define ENTIRE_CONTENTS		(10000000L)

Bool PropGetOLWindowState(Display *dpy, Window win, OLWindowState *winState);


#endif /* _OLWM_PROPERTIES_H */
