/*	@(#)ev_impl.h 20.20 93/06/28 SMI	*/

/*
 *	(c) Copyright 1989 Sun Microsystems, Inc. Sun design patents 
 *	pending in the U.S. and foreign countries. See LEGAL NOTICE 
 *	file for terms of the license.
 */

#ifndef ev_impl_DEFINED
#define ev_impl_DEFINED

/*
 * Internal structures for entity_view implementation.
 *
 */

#				ifndef suntool_entity_view_DEFINED
#include <xview_private/ev.h>
#include <xview/window.h>
#				endif

/*
 * the purpose of struct ev_impl_line_data is to have a client_data,
 * separate from position for ft_set.
 *
 * The fields in struct ev_impl_line_seq are as follows:
 * pos		common to all finger tables, position of the finger.
 * considered	the last Es_index considered, relative to pos,
 *		in deciding what character starts the next line.
 * damaged	first Es_index, relative to pos, damaged by either
 *		insertion or deletion.
 * blit_down	temporary, only found in tmp_line_table, for telling
 *		the paint routine what to blit down.
 * blit_up	same as blit_down but for blitting up.
 */
struct ev_impl_line_data {
	Es_index		considered;
	Es_index		damaged;
	int			blit_down;
	int			blit_up;
};
typedef struct ev_impl_line_seq *Ev_impl_line_seq;
struct ev_impl_line_seq {
	Es_index		pos;
	Es_index		considered;
	Es_index		damaged;
	int			blit_down;
	int			blit_up;
};
/* flag values for Ev_impl_line_seq->flags */
#define	EV_LT_BLIT_DOWN		0x0000001

typedef struct ev_index_range {
	Es_index		first, last_plus_one;
} Ev_range;


typedef struct op_bdry_datum *	Op_bdry_handle;
struct op_bdry_datum {
	Es_index		pos;
	Ev_mark_object		info;
	unsigned		flags;
	opaque_t		more_info;
};

typedef struct ev_overlay_object {
	struct pixrect		*pr;
	int			 pix_op;
	short			 offset_x, offset_y;
	unsigned		 flags;
} Ev_overlay_object;
typedef Ev_overlay_object *	Ev_overlay_handle;
#define	EV_OVERLAY_RIGHT_MARGIN	0x00000001

#define	EI_OP_EV_OVERLAY	0x01000000

	/* op_bdry flags (in addition to EV_SEL_* in entity_view.h) */
#define EV_BDRY_END		EV_SEL_CLIENT_FLAG(0x1)
				/* ... otherwise _BEGIN */
#define	EV_BDRY_OVERLAY		EV_SEL_CLIENT_FLAG(0x2)
#define EV_BDRY_TYPE_ONLY	(EV_BDRY_END|EV_SEL_BASE_TYPE(0xFFFFFFFF))
#define EV_BDRY_EXACT_MATCH	(EV_BDRY_TYPE_ONLY|EV_SEL_PENDING_DELETE)

/*   The following struct is used to cache information about the coordinate
 * of a position in a view.  The definition of when the cache is
 * valid is encapsulated in the EV_CACHED_POS_INFO_IS_VALID macro below.
 */
typedef struct ev_pos_info {
	Es_index		 index_of_first, pos;
	int			 edit_number;
	int			 lt_index;
	struct pr_pos		 pr_pos;
} Ev_pos_info;
#define	EV_NOT_IN_VIEW_LT_INDEX	-1
#define	EV_NULL_DIM		-10000

/*   The following struct is used to cache information about the physical
 * lines that are visible in a view.  The definition of when the cache is
 * valid is encapsulated in the EV_CACHED_LINE_INFO_IS_VALID macro below.
 *
 *   It is also used to cache the last sought line number from
 * ev_position_for_physical_line().  If the next sought line number
 * is greater than the cached one and the cache is valid, then the
 * search may be started from the cached position.  In this usage,
 * line_count is ignored, and cache validity is only based on
 * EV_CHAIN_PRIVATE->edit_number.
 */
typedef struct ev_physical_line_info {
	Es_index		 index_of_first;
	int			 edit_number;
	int			 first_line_number;	/* 0-origin */
	int			 line_count;
} Ev_physical_line_info;

/*   Caret_pr_pos is set to EV_NULL_DIM when the caret is not displayed.
 * This field is required because the insert_pos may move BEFORE the caret is
 * taken down.
 */
typedef struct ev_private_data_object *Ev_pd_handle;
struct ev_private_data_object {
	struct pr_pos		 caret_pr_pos;
	short			 left_margin, right_margin;
	Ev_right_break		 right_break;
	Ev_pos_info		 cached_insert_info;
	Ev_physical_line_info	 cached_line_info;
	long unsigned		 state;
};
#ifdef lint
#define EV_PRIVATE(view_formal)	(Ev_pd_handle)(view_formal ? 0 : 0)
#else
#define EV_PRIVATE(view_formal)	((Ev_pd_handle) view_formal->private_data)
#endif

#define	EV_VIEW_FIRST(view_formal)	ft_position_for_index( \
		(view_formal)->line_table, 0)

	/* Bit flags for EV_PRIVATE(view)->state */
#define	EV_VS_INSERT_WAS_IN_VIEW	0x00000001
#define	EV_VS_INSERT_WAS_IN_VIEW_RECT	0x00000002
#define	EV_VS_DAMAGED_LT		0x00000004
#define	EV_VS_DELAY_UPDATE		0x00000008
#define	EV_VS_NO_REPAINT_TIL_EVENT	0x00000010
#define	EV_VS_SET_CLIPPING		0x00000020
#define EV_VS_BUFFERED_OUTPUT           0x00000040
#define	EV_VS_UNUSED			0xfffffff0

typedef struct ev_chain_private_data_object *Ev_chain_pd_handle;
struct ev_chain_private_data_object {
	Es_index		  insert_pos;
	Ev_mark_object		  selection[2];
	Ev_mark_object		  secondary[2];
	Ev_line_table		  op_bdry;
	int			  auto_scroll_by,
				  lower_context, upper_context;
	int			(*notify_proc)();
	int			  notify_level;
	int			  edit_number;
	int			  caret_is_ghost;
	int			  glyph_count;
	struct pixrect		 *caret_pr;
	struct pr_pos		  caret_hotpoint;
	struct pixrect		 *ghost_pr;
	struct pr_pos		  ghost_hotpoint;
	Ev_physical_line_info	  cache_pos_for_file_line;
#ifdef OW_I18N
	int			  updated;	/* contents update flag */
#endif
};
#ifdef lint
#define EV_CHAIN_PRIVATE(chain_formal)					\
	((Ev_chain_pd_handle)((chain_formal) ? 0 : 0 ))
#define	EV_CACHED_POS_INFO_IS_VALID(view_formal, pos_formal, cache_formal) \
	((view_formal) && (pos_formal) && (cache_formal))
#define	EV_CACHED_LINE_INFO_IS_VALID(view_formal)			\
	((view_formal))
#else
#define EV_CHAIN_PRIVATE(chain_formal)					\
	((Ev_chain_pd_handle) (chain_formal)->private_data)
#define	EV_CACHED_POS_INFO_IS_VALID(view_formal, pos_formal, cache_formal) \
    (	((cache_formal)->pos == (pos_formal)) &&			   \
	((cache_formal)->index_of_first == EV_VIEW_FIRST(view_formal)) &&  \
	((cache_formal)->edit_number ==	     				   \
	 EV_CHAIN_PRIVATE((view_formal)->view_chain)->edit_number)  )
#define	EV_CACHED_LINE_INFO_IS_VALID(view_formal)			\
    (	(EV_PRIVATE(view_formal)->cached_line_info.index_of_first ==	\
	 EV_VIEW_FIRST(view_formal)) &&					\
	(EV_PRIVATE(view_formal)->cached_line_info.edit_number ==	\
	 EV_CHAIN_PRIVATE((view_formal)->view_chain)->edit_number)  )
#endif

	/* break_action bits for ev_display_internal */
#define EV_QUIT			0x00000001
#define EV_Q_DORBREAK		0x00000002
#define EV_Q_LTMATCH		0x00000004

#define EV_BUFSIZE 200

struct range {
	int		ei_op;
	int		last_plus_one;
	int		next_i;
	unsigned	op_bdry_state;
};


#endif

/*
 * Struct for use by ev_process and friends.
 */
typedef struct _ev_process_object {
	Ev_handle		 view;
	Rect			 rect;
	struct ei_process_result result;
	struct pr_pos		 ei_xy;
	Es_buf_object		 esbuf;
	Es_buf_object		 whole_buf;
	int			 esbuf_status;
	Es_index		 last_plus_one;
	Es_index		 pos_for_line;
	unsigned		 flags;
}	Ev_process_object;
#define	EV_PROCESS_PROCESSED_BUF	0x0000001

typedef Ev_process_object *Ev_process_handle;


#ifdef notdef

/*
 * The assertions being maintained for the line_table entries follow.
 * The view is tiled from the top to the bottom by a series of strips,
 *   each of the same height and width, except that the last strip may
 *   not be full height.
 * A strip is painted with entities from the left edge to the right.
 * The line_table has one entry for each strip, plus an additional
 *   entry.  The entry for a strip records the index of the first
 *   entity painted in the strip (that is, the entity painted at the
 *   left edge of the strip).  If no entities are painted in the strip,
 *   then the line_table entry contains the length of the entity
 *   stream.
 * The additional line_table entry contains whatever entry would have
 *   been made if the view was one strip longer.
 */

		/* INITIALIZATION and FINALIZATION */
Pkg_private	Ev_chain
ev_create_chain(esh, eih, sizeof_finger_data)
	Es_handle	esh;
	Ei_handle	eih;
/*
 * Allocates and initializes an Ev_chain_object, returning a handle for the
 *   object.
 */

Pkg_private	Ev_handle
ev_create_view(chain, pw, rect)
	Ev_chain	chain;
	Xv_Window	pw;
	struct rect	*rect;
/*
 * Allocates and initializes an ev_object, returning a handle for the object.
 * Note: creation of a view does NOT cause it to be displayed.
 */

Pkg_private	void 
ev_destroy(view)
	Ev_handle view;
/*
 * Deallocates the indicated ev_object and all other structures assigned to,
 *   and accessible from that object.
 */

Pkg_private	Ev_chain
ev_destroy_chain_and_views(chain)
	Ev_chain	chain;
/*
 * Deallocates the indicated Ev_chain_object and all other structures
 *   assigned to, and accessible from that object, AFTER first destroying
 *   each of the views in the chain.
 */

Pkg_private	void
ev_set_chain_options(chain, options)
	Ev_chain	chain;
	int		options;

Pkg_private	void
ev_set_options(view, options)
	Ev_handle	view;
	int		options;


		/* GEOMETRIC UTILITIES */
Pkg_private	Ev_handle
ev_view_above(this_view)
	Ev_handle	this_view;
/*
 * Returns the view that has the largest rect.r_top less than this_view's.
 */

Pkg_private	Ev_handle
ev_view_below(this_view)
	Ev_handle	this_view;
/*
 * Returns the view that has the smallest rect.r_top greater than this_view's.
 */

Pkg_private	Ev_handle
ev_highest_view(chain)
	Ev_chain	chain;
/*
 * Returns the view that has the smallest rect.r_top.
 */

Pkg_private	Ev_handle
ev_lowest_view(chain)
	Ev_chain	chain;
/*
 * Returns the view that has the largest rect.r_top.
 */


		/* DISPLAY UTILITIES */
Pkg_private	void
ev_clear_rect(view, rect)
	Ev_handle		 view;
	register struct rect	*rect;
/*
 * Paints a background pattern within the indicated view and rectangle (which
 *   should be within that view's rectangle).
 */

Pkg_private	ev_line_table
ev_ft_for_rect(eih, rect)
	Ei_handle		 eih;
	struct rect		*rect;
/*
 * Allocates a line_table of a size appropriate to the indicated
 *   entity_interpreter and rectangle.
 */

Pkg_private	void
ev_set_rect(view, rect, intersect_rect)
	register ev_handle	 view;
	struct rect		*rect,
				*intersect_rect;
/*
 * Changes the rectangle for the view to the indicated new rectangle after
 *   clearing the old view rectangle.
 * Also adjusts line_table to match new size.
 * If the intersect_rect is not null, and it intersects the new rect, then
 *   the view is displayed in the intersection of the two rects.
 */

Pkg_private	ev_range
ev_get_selection_range(private, type, mode)
	Ev_chain_pd_handle	 private;
	unsigned		 type;
	int			*mode;
/*
 * INTERNAL UTILITY: computes range occupied by selection of specified type.
 * If mode is non-zero, *mode is set to the selection mode
 *   (e.g., EV_SEL_PD_PRIMARY).
 */

Pkg_private	void
ev_set_selection(chain, first, last_plus_one, type)
	Ev_chain	chain;
	Es_index	first, last_plus_one;
	unsigned	type;
/*
 * Sets the selection of the indicated type to be the indicated interval.
 */

Pkg_private	int
ev_get_selection(chain, first, last_plus_one, type)
	Ev_chain	 chain;
	Es_index	*first, *last_plus_one;
	unsigned	 type;
/*
 * Gets the interval for the selection of the indicated type.  If no such
 *   interval exists, *first is set to ES_INFINITY.
 * Returns the value of the selection mode (e.g., EV_SEL_PD_PRIMARY).
 */

Pkg_private	void
ev_clear_selection(chain, type)
	Ev_chain	chain;
	unsigned	 type;
/*
 * Removes the selection of the indicated type from the display and the
 *   internal state.
 */

Pkg_private	void
ev_view_range(view, first, last_plus_one)
	Ev_handle	 view;
	Es_index	*first, *last_plus_one;
/*
 * Fills the first and last_plus_one targets with the corresponding entity
 *   positions for the indicated view.
 */

Pkg_private	void
ev_xy_in_view(view, pos, lt_index, rect)
	Ev_handle	 view;
	Es_index	 pos;
	int		*lt_index;
	struct rect	*rect;
/* Given a position in the underlying entity_stream, this routine determines
 *   whether the position is visible in the view, and if not, how it is
 *   related to the view.
 * Returns:
 *  EV_XY_VISIBLE	iff pos is visible in view,
 *  EV_XY_ABOVE		if pos is above view,
 *  EV_XY_BELOW		if pos is below view,
 *  EV_XY_RIGHT		if pos is to the right of view,
 * Only when the return is EV_XY_VISIBLE is lt_index set to the line_table 
 *   index containing the position and rect is set to the rectangle beginning
 *   at the position.
 */

Pkg_private	void
ev_display_range(chain, first, last_plus_one)
	Ev_chain	chain;
	Es_index	first, last_plus_one;
/*
 * For all views, displays the entities in the interval [first..last_plus_one).
 */

Pkg_private	void
ev_display_view(view)
	Ev_handle	view;
/*
 * Redisplays the indicated view from scratch.
 */

Pkg_private	void
ev_display_views(chain)
	Ev_chain	chain;
/*
 * Redisplays all the views on the indicated chain from scratch.
 */

Pkg_private	void
ev_set_start(view, start)
	Ev_handle	view;
	Es_index	start;
/*
 * Changes the view to have the entity identified by start as the first
 *   entity visible in the view, and then repaints the view.
 */

Pkg_private	Es_index
ev_scroll_lines(view, line_count)
	Ev_handle	view;
	int		line_count;
/*
 * Scrolls the view forward (line_count positive) or backward (line_count
 *   negative) by the indicated line_count.
 * Returns the entity index for the first visible entity in the view after
 *   the scroll.
 */

Pkg_private	void
ev_fill_esbuf(esbuf, ptr_to_last_plus_one)
	Ei_esbuf_handle	 esbuf;
	Es_index	*ptr_to_last_plus_one;
/*
 * Fills the provided buffer with entities from the entity_stream.
 * Returns non-zero value iff READ_AT_EOF.
 * If return is 0, then at least one entity was read, and the index one past
 *   the last entity read is set through ptr_to_last_plus_one.
 */

Pkg_private	void
ev_range_info(op_bdry, pos, range)
	Ev_line_table		 op_bdry;
	Es_index		 pos;
	struct range		*range;
/*
 * Fills the indicated range with the information associated with pos.
 */

Pkg_private	struct Ei_process_result
ev_display_internal(view, rect, line, stop_plus_one, ei_op, break_action)
	Ev_handle	 view;
	struct rect	*rect;
	int		 line;
	Es_index	 stop_plus_one;
	int		 ei_op, break_action;
/*
 * The main workhorse display routine.
 * WARNING: This routine is overloaded, too complex, and buggy!
 */

Pkg_private	void
ev_line_for_y(view, y)
	Ev_handle	view;
	int		y;
/*
 * Returns the line_table index for the indicated y coordinate, which is in
 *   the pixwin's coordinate system (thus y=0 may not be in the view).
 */

Pkg_private	Es_index
ev_index_for_line(view, line)
	Ev_handle	view;
	int		line;
/*
 * Returns the entity index for the specified line in the specified view.
 * If line is out of range, it is forced to 0.
 */

Pkg_private	struct rect
ev_rect_for_line(view, line)
	Ev_handle	view;
	int		line;
/*
 * Returns the rectangle bounding the indicated line in the view.
 * This rectangle is in the pixwin's coordinate system.
 */

Pkg_private	Ev_handle
ev_resolve_xy_to_view(views, x, y)
	Ev_chain	 views;
	int		 x, y;
/*
 * Returns the view containing the indicated point (in the pixwin's coordinate
 *   system), or 0 if no such view exists.
 */

Pkg_private	Es_index
ev_resolve_xy(views, x, y)
	Ev_chain	 views;
	int		 x, y;
/*
 * Returns the index of the entity containing the indicated point (in the
 *   pixwin's coordinate system), or ES_INFINITY if no such index exists.
 */

Pkg_private	void
ev_set_esh(chain, esh, reset)
	Ev_chain	chain;
	Es_handle	esh;
	unsigned	reset;
/*
 * Changes the entity_stream underlying the views, then repaints all views.
 * If reset is non-zero, the views are repositioned to the beginning of the
 *   new stream before being displayed.
 */

#endif

#ifdef __STDC__
Pkg_private void ev_display_in_rect(Ev_handle view, Rect *rect);
Pkg_private void ev_clear_rect(Ev_handle view, struct rect *rect);
Pkg_private void ev_set_start(Ev_handle view, Es_index start);
Pkg_private void ev_display_view(Ev_handle view);
Pkg_private void ev_view_range(Ev_handle view, Es_index *first, Es_index *last_plus_one);
Pkg_private void ev_display_line(Ev_handle view, int width_before, int lt_index, Es_index first, Es_index last_plus_one);
Pkg_private int es_make_buf_include_index(Es_buf_handle esbuf, Es_index index, int desired_prior_count);
Pkg_private unsigned ev_span(Ev_chain views, Es_index position, Es_index *first, Es_index *last_plus_one, int group_spec);
Pkg_private void ev_lt_paint(Ev_handle view, Ev_line_table *new_lt, Ev_line_table *old_lt);
Pkg_private void ev_clear_to_bottom(Ev_handle view, Rect *rect, int new_top, unsigned clear_current_first);
Pkg_private void ev_add_margins(Ev_handle view, Rect *rect);
Pkg_private Ev_finger_handle ev_add_finger(Ev_finger_table *fingers, Es_index pos, opaque_t client_data, Ev_mark id_handle);
Pkg_private Es_index ev_index_for_line(Ev_handle view, int line);
Pkg_private void ev_find_in_esh(Es_handle esh, CHAR *pattern, int pattern_length, Es_index position, unsigned count, int flags, Es_index *first, Es_index *last_plus_one);
Pkg_private int ev_newlines_in_esh(Es_handle esh, Es_index first, Es_index last_plus_one);
Pkg_private int ev_xy_in_view(Ev_handle view, Es_index pos, int *lt_index, Rect *rect);
Pkg_private void ev_update_view_display(Ev_handle view);
Pkg_private void ev_notify(Ev_handle view, ...);
Pkg_private void ev_remove_op_bdry(Ev_finger_table *op_bdry, Es_index pos, unsigned type, unsigned mask);
Pkg_private void ev_extend_to_view_bottom(Ev_handle view, struct rect *rect);
Pkg_private Es_index ev_line_start(Ev_handle view, Es_index position);
Pkg_private void ev_scroll_if_old_insert_visible(Ev_chain views, Es_index insert_pos, Es_index delta);
Pkg_private void ev_update_chain_display(Ev_chain views);
Pkg_private void ev_check_insert_visibility(Ev_chain views);
Pkg_private int ev_check_cached_pos_info(Ev_handle view, Es_index pos, Ev_pos_info *cache);
Pkg_private int ev_get_selection(Ev_chain chain, Es_index *first, Es_index *last_plus_one, unsigned type);
Pkg_private int ev_delete_span(Ev_chain views, Es_index first, Es_index last_plus_one, Es_index *delta);
Pkg_private Es_index ev_lt_delta(Ev_handle view, Es_index before_edit, Es_index delta);
Pkg_private void ev_lt_format(Ev_handle view, Ev_line_table *new_lt, Ev_line_table *old_lt);
Pkg_private void ev_remove_finger(Ev_finger_table *fingers, Ev_mark_object mark);
Pkg_private void ev_update_after_edit(Ev_chain views, Es_index last_plus_one, Es_index delta, Es_index old_length, Es_index min_insert_pos);
Pkg_private void ev_view_range(Ev_handle view, Es_index *first, Es_index *last_plus_one);
Pkg_private void ev_paint_view(Ev_handle e_view, Xv_window xv_win, XEvent *xevent);
Pkg_private int ev_line_for_y(Ev_handle view, int y);
Pkg_private void ev_destroy(Ev_handle view);
Pkg_private int ev_fill_esbuf(Es_buf_handle esbuf, Es_index *ptr_to_last_plus_one);
Pkg_private void ev_range_info(Ev_line_table op_bdry, Es_index pos, struct range *range);
Pkg_private void ev_update_lt_after_edit(Ev_line_table *table, Es_index before_edit, long int delta);
Pkg_private void ev_clear_selection(Ev_chain chain, unsigned type);
Pkg_private Es_index ev_input_partial(Ev_chain views, CHAR *buf, int buf_len);
Pkg_private void ev_set_glyph_pr(Ev_chain chain, Ev_mark_object mark, struct pixrect *pr);
Pkg_private int ev_rect_for_ith_physical_line(Ev_handle view, int phys_line, Es_index *first, Rect *rect, int skip_white_space);
#else
Pkg_private void ev_display_in_rect();
Pkg_private void ev_clear_rect();
Pkg_private void ev_set_start();
Pkg_private void ev_display_view();
Pkg_private void ev_view_range();
Pkg_private void ev_display_line();
Pkg_private int es_make_buf_include_index();
Pkg_private unsigned ev_span();
Pkg_private void ev_lt_paint();
Pkg_private void ev_clear_to_bottom();
Pkg_private void ev_add_margins();
Pkg_private Ev_finger_handle ev_add_finger();
Pkg_private Es_index ev_index_for_line();
Pkg_private void ev_find_in_esh();
Pkg_private int ev_newlines_in_esh();
Pkg_private int ev_xy_in_view();
Pkg_private void ev_update_view_display();
Pkg_private void ev_notify();
Pkg_private void ev_remove_op_bdry();
Pkg_private void ev_extend_to_view_bottom();
Pkg_private Es_index ev_line_start();
Pkg_private void ev_scroll_if_old_insert_visible();
Pkg_private void ev_update_chain_display();
Pkg_private void ev_check_insert_visibility();
Pkg_private int ev_check_cached_pos_info();
Pkg_private int ev_get_selection();
Pkg_private int ev_delete_span();
Pkg_private Es_index ev_lt_delta();
Pkg_private void ev_lt_format();
Pkg_private void ev_remove_finger();
Pkg_private void ev_update_after_edit();
Pkg_private void ev_view_range();
Pkg_private void ev_paint_view();
Pkg_private int ev_line_for_y();
Pkg_private void ev_destroy();
Pkg_private int ev_fill_esbuf();
Pkg_private void ev_range_info();
Pkg_private void ev_update_lt_after_edit();
Pkg_private void ev_clear_selection();
Pkg_private Es_index ev_input_partial();
Pkg_private void ev_set_glyph_pr();
Pkg_private int ev_rect_for_ith_physical_line();
#endif

#define EV_INSERT_VISIBLE_IN_VIEW(_view)\
    ev_check_cached_pos_info(_view, EV_CHAIN_PRIVATE(_view->view_chain)->insert_pos, &EV_PRIVATE(_view)->cached_insert_info)
