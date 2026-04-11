#ifndef lint
#ifdef sccs
static char sccsid[] = "@(#)xview_scroll_wheel.c 1.1 26/04/11";
#endif
#endif

/*
 * Scroll wheel step: proportional to visible length, with a base and floor,
 * capped at one full viewport (ceiling).
 */

#include <xview/xview.h>
#include <xview_private/xview_scroll_wheel.h>

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
