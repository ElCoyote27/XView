#ifndef lint
#ifdef sccs
static char     sccsid[] = "@(#)sb_scroll.c 1.41 93/06/28";
#endif
#endif

/*
 *	(c) Copyright 1989 Sun Microsystems, Inc. Sun design patents 
 *	pending in the U.S. and foreign countries. See LEGAL NOTICE 
 *	file for terms of the license.
 */

/*
 * Module:	sb_scroll.c
 * 
 * Description:
 * 
 * Maps events into actions
 * 
 */


/*
 * Include files:
 */

#include <xview_private/sb_impl.h>
#include <xview/win_notify.h>

/*
 * Declaration of Functions Defined in This File (in order):
 */
Xv_public void  scrollbar_default_compute_scroll_proc();

Pkg_private int scrollbar_scroll();
Pkg_private int scrollbar_scroll_to_offset();
Pkg_private int scrollbar_scroll_by_client_units();
Pkg_private int xview_scroll_wheel_step();

static int      scrollbar_offset_to_client_units();
static unsigned long scrollbar_absolute_offset();


/******************************************************************/

Pkg_private int
scrollbar_scroll(sb, pos, motion)
    Xv_scrollbar_info *sb;
    int             pos;
    Scroll_motion   motion;
{
    long unsigned   voffset = 0, vstart = 0;
    int             result = SCROLLBAR_POSITION_UNCHANGED;
    int             available_cable;

    if (motion == SCROLLBAR_NONE)
	return (result);

    /* translate position into client space */
    available_cable = scrollbar_available_cable(sb);

    if (sb->compute_scroll_proc != NULL) {
	sb->compute_scroll_proc(SCROLLBAR_PUBLIC(sb), pos, available_cable,
				motion, &voffset, &sb->object_length);
    }
    if (sb->normalize_proc != NULL) {
	sb->normalize_proc(SCROLLBAR_PUBLIC(sb), voffset, motion, &vstart);
    } else {
	vstart = voffset;
    }

    if (vstart != sb->view_start) {
	result = scrollbar_scroll_to_offset(sb, vstart);
    }
    scrollbar_position_elevator(sb, sb->painted, motion);

    return (result);
}

Pkg_private int
scrollbar_scroll_to_offset(sb, view_start)
    Xv_scrollbar_info *sb;
    long unsigned   view_start;
{
    extern Notify_arg win_copy_event();
    extern void     win_free_event();

    /* do bounds checking */
    if (sb->view_length > sb->object_length)
      view_start = 0;
    else if (view_start > sb->object_length) {
	view_start = sb->object_length;
    } else if (view_start < 0) {
	view_start = 0;
    }
    if (view_start != sb->view_start) {

	sb->last_view_start = sb->view_start;
	sb->view_start = view_start;

	(void) win_post_id_and_arg(sb->managee,
				   SCROLLBAR_REQUEST, NOTIFY_SAFE,
				   SCROLLBAR_PUBLIC(sb), win_copy_event,
				   win_free_event);
	return (XV_OK);
    } else {
	return (SCROLLBAR_POSITION_UNCHANGED);
    }
}

/*
 * Move the scrollbar thumb by delta client units (signed). Used for scroll
 * wheel multi-line steps; clamps to [0, object_length - view_length].
 */
Pkg_private int
scrollbar_scroll_by_client_units(sb, delta)
    Xv_scrollbar_info *sb;
    int             delta;
{
    unsigned long max_start;
    long            pos;

    if (delta == 0) {
	return SCROLLBAR_POSITION_UNCHANGED;
    }

    if (sb->view_length > sb->object_length) {
	max_start = 0;
    } else {
	max_start = sb->object_length - sb->view_length;
    }

    pos = (long) sb->view_start + (long) delta;
    if (pos < 0) {
	pos = 0;
    } else if ((unsigned long) pos > max_start) {
	pos = (long) max_start;
    }

    return scrollbar_scroll_to_offset(sb, (unsigned long) pos);
}

Pkg_private int
xview_scroll_wheel_step(view_length)
    int view_length;
{
    int ceiling;
    int proportional;
    int step;
    int effective_floor;
    int smooth_cap;

    if (view_length < XVIEW_SCROLL_WHEEL_MIN_VALID_VIEW_LENGTH) {
	return XVIEW_SCROLL_WHEEL_BASE_LINES;
    }

    ceiling = view_length;

    proportional = (view_length * XVIEW_SCROLL_WHEEL_VIEW_PORTION_NUMERATOR)
	/ XVIEW_SCROLL_WHEEL_VIEW_PORTION_DENOMINATOR;

    step = proportional;
    if (step < XVIEW_SCROLL_WHEEL_BASE_LINES) {
	step = XVIEW_SCROLL_WHEEL_BASE_LINES;
    }

    if (view_length >= XVIEW_SCROLL_WHEEL_APPLY_LINE_FLOOR_MIN_VIEW_LENGTH) {
	if (XVIEW_SCROLL_WHEEL_FLOOR_LINES < ceiling) {
	    effective_floor = XVIEW_SCROLL_WHEEL_FLOOR_LINES;
	} else {
	    effective_floor = ceiling;
	}
    } else {
	effective_floor = XVIEW_SCROLL_WHEEL_ABSOLUTE_MIN_STEP;
    }

    if (step < effective_floor) {
	step = effective_floor;
    }

    if (step > ceiling) {
	step = ceiling;
    }

    smooth_cap = (view_length * XVIEW_SCROLL_WHEEL_MAX_STEP_PER_TICK_NUMERATOR)
	/ XVIEW_SCROLL_WHEEL_MAX_STEP_PER_TICK_DENOMINATOR;
    if (smooth_cap < XVIEW_SCROLL_WHEEL_ABSOLUTE_MIN_STEP) {
	smooth_cap = XVIEW_SCROLL_WHEEL_ABSOLUTE_MIN_STEP;
    }
    if (step > smooth_cap) {
	step = smooth_cap;
    }

    return step;
}

Xv_public void
scrollbar_default_compute_scroll_proc(scroll_public, pos, length, motion,
				      offset, object_length)
    Scrollbar       scroll_public;
    int             pos;
    int             length;
    Scroll_motion   motion;
    unsigned long  *offset;
    unsigned long  *object_length;
{
    Xv_scrollbar_info *sb = SCROLLBAR_PRIVATE(scroll_public);
    int             minus_movement;
    unsigned long   pixel_offset;

    pixel_offset = sb->view_start * sb->pixels_per_unit;

    switch (motion) {
      case SCROLLBAR_ABSOLUTE:
	/* pos is position in the cable */
	pixel_offset = scrollbar_absolute_offset(sb, pos, length);
	break;

      case SCROLLBAR_POINT_TO_MIN:
	pixel_offset += (pos - sb->pixels_per_unit);
	break;

      case SCROLLBAR_PAGE_FORWARD:
	if (sb->page_length != SCROLLBAR_DEFAULT_LENGTH) {
	    /* page scrolling */
	    pixel_offset += (sb->page_length * sb->pixels_per_unit);
	} else {
	    /* display scrolling */
	    pixel_offset += (sb->view_length * sb->pixels_per_unit);
	}
	break;

      case SCROLLBAR_LINE_FORWARD:
	pixel_offset += sb->pixels_per_unit;
	break;

      case SCROLLBAR_MIN_TO_POINT:
	if (pos > pixel_offset) {
	    *offset = 0;
	} else {
	    pixel_offset -= (pos - sb->pixels_per_unit);
	}
	break;

      case SCROLLBAR_PAGE_BACKWARD:
	if (sb->page_length != SCROLLBAR_DEFAULT_LENGTH) {
	    /* page scrolling */
	    minus_movement = sb->page_length * sb->pixels_per_unit;
	} else {
	    /* display scrolling */
	    minus_movement = sb->view_length * sb->pixels_per_unit;
	}
	if (minus_movement > pixel_offset) {
	    pixel_offset = 0;
	} else {
	    pixel_offset -= minus_movement;
	}
	break;

      case SCROLLBAR_LINE_BACKWARD:
	if (sb->pixels_per_unit > pixel_offset) {
	    pixel_offset = 0;
	} else {
	    pixel_offset -= sb->pixels_per_unit;
	}
	break;

      case SCROLLBAR_TO_END:
	pixel_offset = Max_offset(sb) * sb->pixels_per_unit;
	break;

      case SCROLLBAR_TO_START:
	pixel_offset = 0;
	break;

      default:
	break;
    }

    scrollbar_offset_to_client_units(sb, pixel_offset, motion, offset);
    *object_length = sb->object_length;
}

static int
scrollbar_offset_to_client_units(sb, pixel_offset, motion, view_start)
    Xv_scrollbar_info *sb;
    long unsigned   pixel_offset;
    Scroll_motion   motion;
    long unsigned  *view_start;	 /* RETURN */
{
    *view_start = sb->view_start;

    switch (motion) {
      case SCROLLBAR_ABSOLUTE:
      case SCROLLBAR_MIN_TO_POINT:
      case SCROLLBAR_TO_END:
      case SCROLLBAR_TO_START:
      case SCROLLBAR_LINE_FORWARD:
      case SCROLLBAR_LINE_BACKWARD:
	*view_start  = pixel_offset / sb->pixels_per_unit;
	break;

      case SCROLLBAR_POINT_TO_MIN:
	*view_start = ((pixel_offset % sb->pixels_per_unit) == 0) ? 
	                pixel_offset / sb->pixels_per_unit : 
		        pixel_offset / sb->pixels_per_unit + 1;
	break;

      case SCROLLBAR_PAGE_BACKWARD:
	if (sb->page_length != SCROLLBAR_DEFAULT_LENGTH && sb->page_length != 0) {

	    long unsigned pixels_per_page = sb->pixels_per_unit * sb->page_length;
	    long unsigned page = pixel_offset / pixels_per_page;
	    
	    /* If not on a page boundary round up */
	    if ( (page * pixels_per_page) != pixel_offset )
	      page++;
	    
	    *view_start = page * sb->page_length;
	} else {
	    *view_start = pixel_offset / sb->pixels_per_unit;
	}
	break;

      case SCROLLBAR_PAGE_FORWARD:
	if (sb->page_length != SCROLLBAR_DEFAULT_LENGTH && sb->page_length != 0) {

	    long unsigned pixels_per_page = sb->pixels_per_unit * sb->page_length;
	    long unsigned page = pixel_offset / pixels_per_page;
	    
	    *view_start = page * sb->page_length;
	} else {
	    *view_start = pixel_offset / sb->pixels_per_unit;
	}
	break;

      default:
	break;
    }

    if ( *view_start > Max_offset(sb) )
      *view_start = Max_offset(sb);

    return (XV_OK);
}


static unsigned long
scrollbar_absolute_offset(sb, pos, length)
    Xv_scrollbar_info *sb;
    int             pos;
    int             length;
{
    if (length <= 0)
	return (0);
    else
	return (Max_offset(sb) * pos / length * sb->pixels_per_unit);
}
