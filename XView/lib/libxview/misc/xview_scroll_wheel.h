/*
 * Private scroll wheel step sizing for XView (USE_SCROLL_WHEEL).
 * All tunables are expressed as preprocessor constants (no bare integers).
 */

#ifndef XVIEW_SCROLL_WHEEL_H
#define XVIEW_SCROLL_WHEEL_H

/*
 * Base step (lines/units) when the viewport-based portion is smaller.
 * Works with XVIEW_SCROLL_WHEEL_FLOOR_LINES for the requested "2 vs 3" mix.
 */
#define XVIEW_SCROLL_WHEEL_BASE_LINES 2

/*
 * Minimum step in client units when the viewport is large enough to allow it.
 * When the visible length is smaller, the step is limited to the viewport.
 */
#define XVIEW_SCROLL_WHEEL_FLOOR_LINES 3

/*
 * Only apply XVIEW_SCROLL_WHEEL_FLOOR_LINES when at least this many lines are
 * visible; shorter viewports use a 1-line floor so small files are not jumpy.
 */
#define XVIEW_SCROLL_WHEEL_APPLY_LINE_FLOOR_MIN_VIEW_LENGTH 8

/*
 * Portion of the visible length used to scale the step (before floor/ceiling).
 * step >= (view_length * NUM) / DEN after the base clamp, then floor/ceiling.
 */
#define XVIEW_SCROLL_WHEEL_VIEW_PORTION_NUMERATOR 1
#define XVIEW_SCROLL_WHEEL_VIEW_PORTION_DENOMINATOR 5

/*
 * Hard cap per tick: at most this fraction of the visible height (after other
 * clamps). Stops half-screen jumps on short files and narrow panes.
 */
#define XVIEW_SCROLL_WHEEL_MAX_STEP_PER_TICK_NUMERATOR 1
#define XVIEW_SCROLL_WHEEL_MAX_STEP_PER_TICK_DENOMINATOR 2

/*
 * Smallest allowed step when view_length is valid (always 1 line).
 */
#define XVIEW_SCROLL_WHEEL_ABSOLUTE_MIN_STEP 1

/*
 * view_length at or below this means no usable viewport for scaling; use
 * XVIEW_SCROLL_WHEEL_BASE_LINES as the step.
 */
#define XVIEW_SCROLL_WHEEL_MIN_VALID_VIEW_LENGTH 1

/*
 * When document size (entity stream length in characters) is at or below this,
 * textsw scroll-wheel motion is one line per tick (original behavior for small
 * files such as /etc/hosts).
 */
#define XVIEW_SCROLL_WHEEL_SINGLE_LINE_TEXT_MAX_CHARS 12288

/*
 * When a scrolling list has at most this many rows, wheel motion is one row
 * per tick; longer lists use xview_scroll_wheel_step(rows_displayed).
 */
#define XVIEW_SCROLL_WHEEL_SINGLE_LINE_LIST_MAX_ROWS 48

Pkg_private int xview_scroll_wheel_step(int view_length);

#endif /* XVIEW_SCROLL_WHEEL_H */
