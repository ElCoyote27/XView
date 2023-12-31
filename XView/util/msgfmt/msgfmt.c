#ifndef lint
#ifdef sccs
static char     sccsid[] = "@(#)msgfmt.c 1.3 91/09/14";
#endif
#endif

#include "msgfmt.h"
#include <stdlib.h>
#include <string.h>

/*
 * msgfmt - Generate binary tree for runtime gettext() using psffm:
 *           "Portable Source File Format for Messages" file template.
 *	     This file may have previously been generated by the
 *	     c2psffm filter for c source files.
 */

int read_psffm(char *filename);
char *consume_whitespace(char *buf);
char expand_meta(char **buf);
off_t sortit(char *msgid, char *msgstr, int new);
void printlist(void);
int binary_compute(int i, int j, int more[], int less[]);
#ifdef USE_MMAP
void output_file(char *file);
#else
void output_file(char *file);
#endif
void freelist(void);
char *savestr(register char *cp);
int istail(register char *str, register char *of);

#define    ignore(a)    ((void) a)

off_t    mesgpt;

/*
 * Strings is a flat file of id, string pairs, used by cflg
 */

char    *strings =    "strings";

char	linebuf[MAX_VALUE_LEN];
char	*domain_name = DEFAULT_DOMAIN;

int    cflg = 0;
int    verbose = 0;
int    debug = 0;
int    readstd;

struct list_struct list;

void
main(argc, argv)
    int argc;
    char *argv[];
{

    argc--, argv++;
    while (argc > 0 && argv[0][0] == '-') {

        register char *cp = &(*argv++)[1];

        argc--;

        if (*cp == 0) {
            readstd++;
        }

        do switch (*cp++) {

/*
 *	cflag stuff not yet implemented.

        case 'c':
            cflg++;
            continue;
 */

	case 'd':
	    debug++;
	    break;

        case 'v':
            verbose++;
            continue;

        default:
/*
            fprintf(stderr,
                "usage: msgfmt [ -v ] [ -c ] [ - ] [ name ... ]\n");
*/
            fprintf(stderr,
                "usage: msgfmt [ -dv ] [ - ] [ name ... ]\n");
	    break;;

        } while (*cp);	/* do switch ... */

    } /* while (argc ... */


    while (readstd || argc > 0) {

        if (!readstd && freopen(argv[0], "r", stdin) == NULL) {
            perror(argv[0]);
	    exit(2);
	}

    	read_psffm(argv[0]);

        if (readstd == 0) {
            argc--; argv++;
	} else {
            readstd = 0;
	}
    }	/* while (readstd ... */

    exit(0);
}


/* 
 * read_psffm - read in "psffm" format file, check syntax, printing
 * 		error messages as needed, output binary tree to
 *		file <domain>
*/
int
read_psffm(filename)
    char *filename;
{

    static char current_domain[MAX_DOMAIN_LENGTH];
    static char msgfile[MAXPATHLEN];


    char *linebufptr;
    char *current_locale;
    char msgid [MAX_VALUE_LEN+1];
    char msgstr [MAX_VALUE_LEN+1];
    register char *bufptr;
    

    int linenum = 0;
    int	domain_set = 0;
    int whitespace = 0;
    int quotefound = 0;
    int ignored = 0;
    int indomain = 0;
    int inmsgid = 0;
    int inmsgstr = 0;
    char c;


    while (1) {
	memset(linebuf, 0, sizeof(linebuf));
        if (fgets(linebuf, sizeof(linebuf), stdin) == NULL) {
            if (ferror(stdin)) {
                perror(filename);
                exit(2);
            }
            break;
        }
	linenum ++;

	if (verbose) {
	    printf("Scanning line number %d: %s\n", linenum, linebuf);
	}

	linebufptr = linebuf;
	whitespace = 0;

        switch (*linebufptr) {
	case '#': 	/*   comment    */
	case '\n':
	ignored = 1;
	break;

	case '\"':
	case ' ':	/*   whitespace should be handled correctly */
	case '\t':
	    whitespace = 1;
	default:
	    ignored = 0;
	    break;
	}

	if (ignored) {
	    continue;
	}

	/*
	 * Process MSGID Tokens, must not have just seen one unless
	 * this line begins with whitespace -or- "
	 */

	if ((!strncmp(MSGID_TOKEN, linebuf, sizeof(MSGID_TOKEN)-1))
	    || (whitespace && inmsgid)) {
	    if (inmsgid && !whitespace) {
		fprintf(stderr, "Consecutive MSGID tokens encountered ");
		fprintf(stderr, "at line number: %d, exiting\n", linenum);
/*
		exit(1);
*/
	    }
	    if (inmsgstr) {
		sortit(msgid, msgstr, 1);

		memset(msgid, 0, sizeof(msgid));
		memset(msgstr, 0, sizeof(msgstr));
	    }


	    if (inmsgid) {
	        linebufptr = consume_whitespace(linebuf);
	    } else {
	        linebufptr = consume_whitespace(linebuf +
		    sizeof(MSGID_TOKEN)-1);
		bufptr = msgid;
	    }

	    inmsgid = 1;
	    inmsgstr = 0;
	    indomain = 0;
	    goto load_buffer;
	}

	/*
	 * Process MSGSTR Tokens, must not have just seen one unless
	 * this line begins with whitespace -or- "
	 */

	if ((!strncmp(MSGSTR_TOKEN, linebuf, sizeof(MSGSTR_TOKEN)-1))
	    || (whitespace && inmsgstr)) {
	    if (inmsgstr && !whitespace) {
		fprintf(stderr, "Consecutive MSGSTR tokens encountered ");
		fprintf(stderr, "at line number: %d, exiting\n", linenum);
/*
		exit(1);
*/
	    }

	    if (inmsgstr) {
	        linebufptr = consume_whitespace(linebuf);
	    } else {
	        linebufptr = consume_whitespace(linebuf +
		    sizeof(MSGSTR_TOKEN)-1);
		bufptr = msgstr;
	    }

	    inmsgstr = 1;
	    inmsgid = 0;
	    indomain = 0;
	    goto load_buffer;
	}

	/*
	 * Process DOMAIN Tokens, add message id and message string to
	 * sorted list if msgstr was being processed, 
	 * write out file for existing domain if it exists (domain_set = 1)
	*/

	if (!strncmp(DOMAIN_TOKEN, linebuf, sizeof(DOMAIN_TOKEN)-1)) {
	    if (inmsgstr) {
		sortit(msgid, msgstr, 1);
	    }

	    if (inmsgstr || inmsgid) {
		memset(msgid, 0, sizeof(msgid));
		memset(msgstr, 0, sizeof(msgstr));
	    }

	    if (domain_set) {
		output_file(msgfile);
	    }
	    domain_set = 1;
	    indomain = 1;
	    inmsgid = 0;
	    inmsgstr = 0;
		
	    linebufptr = consume_whitespace(linebuf+ sizeof(DOMAIN_TOKEN));
	    memset(current_domain, 0, sizeof(current_domain));
	    bufptr = current_domain;
	}

load_buffer:

	if (*linebufptr++ != '\"') {
	    fprintf(stderr, "Warning, Syntax at line number: %d, ",
		linenum);
	    fprintf(stderr, "Missing \", ignored\n");
	    --linebufptr;
	}

	quotefound = 0;

	while (c=*linebufptr++) {
	    switch (c) {
	    case '\n':
		if (!quotefound) {
		    fprintf(stderr, "Warning, Syntax at line number: %d, ",
			linenum);
		    fprintf(stderr, "Missing \" at EOL, ignored\n");
		}
		break;

	    case '\"':
		quotefound = 1;
	        break;

	    case '\\':
		*bufptr++ = expand_meta(&linebufptr);
		break;

	    default:
	        *bufptr++ = c;
	    }
	}

	if (indomain) {
	    memset(msgfile, 0, sizeof(msgfile));
	    strcpy(msgfile, current_domain);
	    strcat(msgfile, ".mo");
/*
	    strcpy(msgfile, LOCALEDIR);
	    strcat(msgfile, current_locale);
	    strcat(msgfile, "/");
	    strcat(msgfile, current_domain);
*/
	}
    }

    if (inmsgstr) {
	sortit(msgid, msgstr, 1);
    }

    if (inmsgstr || inmsgid) {
	memset(msgid, 0, sizeof(msgid));
	memset(msgstr, 0, sizeof(msgstr));
    }

    if (domain_set) {
	output_file(msgfile);
    }
    return(0);
}


char *
consume_whitespace(buf)
    char *buf;
{
    register char *bufptr = buf;
    char c;
    while (c = *bufptr++) {
	switch (c) {
	    case ' ':
	    case '\t' :
		continue;
	    default:
		return(bufptr-1);
	}
    }
}

char
expand_meta(buf)
    char **buf;
{
    register char c = **buf;

    switch (c) {
        case '"':
	    (*buf)++;
	    return ('\"');
	case '\\':
	    (*buf)++;
	    return ('\\');
        case 'b' :
	    (*buf)++;
	    return ('\b');
        case 'f' :
	    (*buf)++;
	    return ('\f');
        case 'n' :
	    (*buf)++;
	    return ('\n');
        case 'r' :
	    (*buf)++;
	    return ('\r');
        case 't' :
	    (*buf)++;
	    return ('\t');
        case 'v' :
	    (*buf)++;
	    return ('\v');
        default:
	    return ('\\');
    }
}



/*
 * sortit - insertion sort, place message identifier = str and
 * message string = msgstr into list sorted by message identifier
*/

off_t
sortit(msgid, msgstr, new)
    char *msgid, *msgstr;
    int new;
{
    int i, j, lessthan;
    register struct list_struct *hp, *hp0, *hp1;

    if (debug)
	fprintf(stderr,
	    "==> sortit(), msgid = %s, msgstr = %s\n", msgid, msgstr);
    lessthan = 0;
    hp = hp0 = &list;
    while (hp->hnext && !lessthan) {
        hp0 = hp;
        hp = hp->hnext;
        i = istail(hp->msgid, msgid);
        if (i < 0) {
            lessthan = 1;
            hp1 = hp;
            continue;
        }
        if (i == 0) {             /* found! */
            return(hp->hpt);
	}
    }
    if (!lessthan) {
        hp0 = hp;
    }
    if ((hp = (struct list_struct *) calloc(1, sizeof(*hp))) == NULL) {
        perror("msgfmt");
        exit(8);
    }
    hp->hpt = mesgpt;
    hp->msgid = savestr(msgid);
    hp->msg = savestr(msgstr);
    mesgpt += strlen(hp->msgid) + strlen(hp->msg);

    if (hp0->hnext) {
        hp->hnext = hp1;
        hp0->hnext = hp;
        hp->hnew = new;
    } else {
        hp->hnew = new;
        hp0->hnext = hp;
    }
    return(hp->hpt);
}

void
printlist()
{
    struct list_struct *hp1;

    hp1 = &list;
    fprintf(stderr, "dumping record at offset hpt = %ld\n", hp1->hpt);
    fprintf(stderr, "message id is %s\n", hp1->msgid);
    fprintf(stderr, "message string is %s\n", hp1->msg);

    while (hp1->hnext) {
	fprintf(stderr, "dumping record at offset hpt = %ld\n", hp1->hpt);
        fprintf(stderr, "message id is %s\n", hp1->hnext->msgid);
	fprintf(stderr, "message string is %s\n", hp1->hnext->msg);
        hp1 = hp1->hnext;
    }

}


/*
 * binary_compute is used for pre-computing a binary search. 
 */
int
binary_compute(i, j, more, less)
    int i,j;
    int more[],less[];
{
    int k;

    if (i > j ) {
        return -99;
    }
    k = (i + j)/2;

    less[k] = binary_compute(i, k-1, more, less);
    more[k] = binary_compute(k+1, j, more, less);
    return k;
}

/*
 * Write out static_message File contains static structure of messages.
 */
#ifdef USE_MMAP
void
output_file(file)
    char *file;
{
        FILE *xdotcf = fopen(file, "w");
        struct list_struct *lp;
        int     message_count;
        int     string_count_msgid=0;
        int     string_count_msg=0;
        int     msgid_index=0;
        int     msg_index=0;
        int     *less,*more;
        int     i;
 
        if (xdotcf == NULL) {
	    perror("static_messages");
	    exit(6);
	}
 
        message_count = 0;
        lp = &list;
        while (lp->hnext) { /* get offsets and counts */
                lp->hnext->msgid_offset = msgid_index;
                lp->hnext->msg_offset = msg_index;
                msgid_index += strlen(lp->hnext->msgid)+1;
                msg_index += strlen(lp->hnext->msg)+1;
                message_count++;
                lp = lp->hnext;
        }
        string_count_msgid = msgid_index;
        string_count_msg = msg_index;
        if ((less = (int *) calloc(message_count, sizeof(int))) == NULL) {
                perror("msgfmt output_file()");
                exit(8);
        }
        if ((more = (int *) calloc(message_count, sizeof(int))) == NULL) {
                perror("msgfmt output_file()");
                exit(8);
        }
        (void) binary_compute(0, message_count-1, more, less);
        if (message_count == 2) {
                less[1] = -99; /* kludge that works! */
        }
 
        /* write out the message.mo */
        i = (message_count-1)/2; /* this is the first message to check */
        (void) fwrite(&i, sizeof(int), 1, xdotcf);
        (void) fwrite(&message_count, sizeof(int), 1, xdotcf);
        (void) fwrite(&string_count_msgid, sizeof(int), 1, xdotcf);
        (void) fwrite(&string_count_msg, sizeof(int), 1, xdotcf);
        i = sizeof(struct list_struct) * message_count;
        (void) fwrite(&i, sizeof(int), 1, xdotcf);
        i = 0; /* used to get more and less */
        lp = &list;
        while (lp->hnext) { /* put out message struct */
                (void) fwrite(&less[i], sizeof(int), 1, xdotcf);
                (void) fwrite(&more[i], sizeof(int), 1, xdotcf);
                (void) fwrite(&lp->hnext->msgid_offset, sizeof(int), 1, xdotcf);
                (void) fwrite(&lp->hnext->msg_offset, sizeof(int), 1, xdotcf);
                i++;
                lp = lp->hnext;
        }
        lp = &list;
        while (lp->hnext) { /* put out messageid strings */
                (void) fwrite(lp->hnext->msgid, strlen(lp->hnext->msgid)+1, 1, xdotcf);            
                lp = lp->hnext;
        }
        lp = &list;
        while (lp->hnext) { /* put out message strings */
                (void) fwrite(lp->hnext->msg, strlen(lp->hnext->msg)+1, 1, xdotcf);
                lp = lp->hnext;
        }
        ignore(fclose(xdotcf));
        /* clear list */
        list.hpt =0;
        list.msgid_offset =0;
        list.msg_offset =0;
        list.msgid =(char )0;
        list.msg =(char )0;
        list.hnext = NULL;
        list.hnew = 0;
}

#else

vpod
output_file(file)
    char *file;
{
    FILE *xdotcf = fopen(file, "w");
    struct list_struct *lp;
    int    message_count;
    int    *less, *more;
    int    i;

    if (xdotcf == NULL){
        perror(file);
	 exit(6);
    }

    message_count = 0;
    lp = &list;
    while (lp->hnext) {
        message_count++;
        lp = lp->hnext;
    }
    if ((less = (int *) calloc(message_count, sizeof(int))) == NULL) {
        perror("msgfmt output_file()");
        exit(8);
    }
    if ((more = (int *) calloc(message_count, sizeof(int))) == NULL) {
        perror("msgfmt output_file()");
        exit(8);
    }
    binary_compute(0, message_count-1, more, less);
    if (message_count == 2) {
        less[1] = 0; /* kludge that works! */
    }

    

    /* put out messages in binary format */

    fprintf(xdotcf,"%d\n%d\n", message_count, (message_count-1)/2);
    lp = &list;
    while (lp->hnext) {
        fprintf(xdotcf,"%s\n", lp->hnext->msgid); /* message id */
        fprintf(xdotcf,"%d\n%d\n", *less++, *more++);
        fprintf(xdotcf,"%s\n", lp->hnext->msg); /* message id */
        lp = lp->hnext;
    }
    ignore(fclose(xdotcf));

    freelist();
}
#endif

/*
 * freelist() - frees all members of the sorted list after the list
 * 		is written out to the binary tree file, called when
 *		changing domains and when exiting the program
*/
void
freelist()
{
    register struct list_struct *hp, *hp0;

    hp0 = &list;
    hp = hp0->hnext;

    while (hp->hnext) {
        hp0 = hp;
        hp = hp->hnext;
        free(hp0);
    }
    free(hp);
    list.hnext = 0;
}

char *
savestr(cp)
    register char *cp;
{
    register char *dp;

    if ((dp = (char *) calloc(1, strlen(cp) + 1)) == NULL) {
        perror("msgfmt");
        exit(8);
    }
    return(strcpy(dp, cp));
}

int
istail(str, of)
    register char *str, *of;
{

        return(strcmp(of, str));
}