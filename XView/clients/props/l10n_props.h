/*
 * @(#)l10n_props.h 1.1 90/12/14
 */

/*
 * Maximum number of choices per choice item (choices read from config file)
 */
#define	MAX_CHOICES	12

/*
 * This should be defined by some of the /usr/include files, but not
 * (yet?).
 */
#define	LOCALE_NAME_LEN		20


typedef struct	_l10n_config_list_item {
	/*
	 * value is locale name, and locale name has to be in ASCII.
	 */
	char			*value;

#ifdef OW_I18N
	/*
	 * label could be locale depended any characters.
	 */
	wchar_t			*label;
#else
	char			*label;
#endif 

	/*
	 * the following is a copy of "label", this is temporary until
	 * *_WCS attr become available.
	 */
	char			*mbs_label;

	struct _l10n_config_list_item	*next;

} l10n_config_list_item_t;


typedef struct	l10n_config_list {
#ifdef OW_I18N
	/*
	 * name is should be in ASCII, but from performance point of
	 * view, better to be in the wide char here.
	 */
	wchar_t			*name;
#else
	char			*name;
#endif 

	/*
	 * Class name for defaults database(Xrm).  Has to be char
	 * (portable character only).
	 */
	char			*class;

	/*
	 * Class type for defaults -- D_string, D_boolean, etc.
	 */
	Deftype			class_type;

#ifdef OW_I18N
	/*
	 * When reading from file, the label will converted by this
	 * function.  This is usefull for data like time format which
	 * actually generated by strftime function (file contains
	 * format for strftime, not string itself).
	 */
	wchar_t			*(*convert_label)();
#endif /* OW_I18N */

	int			default_value;

	int			initial_value;

	int			current_value;

	l10n_config_list_item_t	*items;

} l10n_config_list_t;


typedef struct _l10n_config_sss {
	char			*locale;
	l10n_config_list_t	*list;
	struct _l10n_config_sss	*next;
} l10n_config_sss_t;

