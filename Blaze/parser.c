/**
 * Parse a source file into parse-tree tokens which can be run or saved.
 */

/*
    blaze: mongrel language mashing perl and pascal concepts (among others)

    Copyright (C) 2009, Robin R Anderson
    roboprog@yahoo.com
    PO 1608
    Shingle Springs, CA 95682

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// *** import ****

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define __USE_GNU
#include <string.h>

#include "memwrap.h"
#include "symtab.h"
#include "parse_state.h"

#include "parser.h"

// *** constants ***

/** whitespace chars (to ignore, ideally) */
#define WHITESPACE  " \t\r\n"

/** numeric constant type chars (excluding minus sign) */
#define NUMERIC     "0123456789."

/** keyword / identifier type chars */
#define WORD        "_" \
        "abcdefghijklmnopqrstuvwzyz"    \
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"    \
        "0123456789"

// **** types ***

/** used mapping of literals / reserved words to token types */
typedef struct t_token_mapping
    {
    const char *        literal;        /**< literal symbol or keyword */
    t_token_type        type;           /**< type */
    } t_token_mapping;

/** parse state transition table entry */
typedef struct t_parse_st
    {
    t_parse_state       from;           ///< starting state
    t_token_type        token;          ///< type of token encountered
    t_parse_state       to;             ///< resulting state
    // TODO:  assertion / resolution callback
    } t_parse_st;

/** buffer for an individual token */
typedef struct t_token
    {
    t_token_type        type;           ///< type of token
    const char *        text;           ///< text token
    } t_token;

/** buffer for each input line */
typedef struct t_logical_line
    {
    int                 linenum;        ///< line number of start of line
    int                 span;           ///< how many input lines made up this logical line
    const char *        text;           ///< text of program line
    t_token *           tokens;         ///< tokens from initial parse
    int                 num_tokens;     ///< how many tokens?
    } t_logical_line;

// *** data ***

/**
 * Mapping table to get type enum value for keywords and symbols.
 *  Try to put high-frequency symbols at top, until better search implemented.
 */
static const
t_token_mapping         KEYWORDS [] =
    {
        { "(",          TT_OPEN_PAREN },
        { ")",          TT_CLOSE_PAREN },
        { ":",          TT_NAMESPACE_SEP },
        { "run",        TT_KW_RUN },
        { "end",        TT_KW_END },

        { NULL }
    };

/** state transition table for parsing syntax check */
static const
t_parse_st              STATE_TABLE[] =
    {
    //  from-state              token type      to-state
        { PS_INIT,              TT_KW_RUN,      PS_RUN_END},
        { PS_RUN_END,           TT_END_STMT,    PS_NEXT_STMT},

        { PS_NEXT_STMT,         TT_KW_END,      PS_MOD_EXEC_END},
        { PS_NEXT_STMT,         TT_NAMESPACE,   PS_AWAIT_QUAL_SEP},
        { PS_NEXT_STMT,         TT_FUNC_NAME,   PS_NEXT_STMT},  // TODO: optional arg list

        { PS_AWAIT_QUAL_SEP,    TT_NAMESPACE_SEP,
                                                PS_NEXT_STMT },  // TODO: really want func/var name

        { PS_UNDEF }  // table terminator
    };

// **** routines ***

/** issue message and give up.  TODO:  setjmp/longmp */
#define MABORT( m)  ( fprintf( stderr, "ERROR: %s\n" m), exit( 1) )

/**
 * Read a logical line, concatenating input lines as needed.
 * Set line_buf->span to 0 when EOF is detected.
 * TODO:  find a GNU routine to replace this.
 */
static
void                    read_logical_line
    (
    FILE *              infile,         ///< input file handle
    t_logical_line *    line_buf        ///< line buffer to which text is allocated
    )
    {
    char *              text;
    char *              newline;

    line_buf->span = 0;
    text = malloc( 256);
    if ( fgets( text, 256, infile) == NULL)
        {
        // TODO:  error checking
        free( text);
        return;  // === abort ===
        }  // (presumed) eof?

    ( line_buf->span)++;
    newline = strchr( text, '\n');
    if ( newline != NULL)
        {
        *newline = '\0';
        }  // terminated line
    // else:  final
    // TODO:  large-line append loop
    line_buf->text = text;
    }  // _________________________________________________________

/**
 * Save the specified token (allocate string in array).
 */
static
void                    save_token
    (
    t_logical_line *    line_buf,       ///< line buffer from which we parse,
                                        ///  and to which we append the token-trackers
    const char *        token_src,      ///< input buffer from which to copy
    int                 token_len,      ///< length to grab
    t_token_type        type            ///< tentative type of this token
    )
    {
    char *              new_token;

    if ( ! MEXTEND_ARRAY( line_buf->tokens, line_buf->num_tokens) )
        {
        MABORT( "out of memory allocating token reference");
        // === abort ===
        }  // out of memory?

    new_token = strndup( token_src, token_len);
    if ( ! new_token)
        {
        MABORT( "out of memory allocating token buffer");
        // === abort ===
        }  // out of memory?

    line_buf->tokens[ line_buf->num_tokens - 1 ].text = new_token;
    line_buf->tokens[ line_buf->num_tokens - 1 ].type = type;
    }  // _________________________________________________________

/**
 * Split the input line buffer into identifiable tokens (i.e. - "lex" it).
 * TODO:  lex/yacc (flex/bison)?
 */
static
void                    tokenize_line
    (
    t_logical_line *    line_buf        ///< line buffer from which we parse,
                                        ///  and to which we append the token-trackers
    )
    {
    const char *        t;  // alias for text (avoid typing and possible non-optomizing)
    int                 is_in_string;
    int                 tot_len;
    int                 offset;
    int                 token_len;
    const char *        new_token;

    t = line_buf->text;  // invariant anyway
    is_in_string = 0;
    tot_len = strlen( t);
    for ( offset = 0; offset < tot_len; /* inc in loop */)

        {
        // printf( ".%d:[%c]\n", ( offset + 1), t[ offset ]);
        if ( is_in_string)
            {
            token_len = strcspn( (t + offset), "\"");
            // TODO:  deal w/ special chars
            save_token( line_buf, t + offset, token_len, TT_STRING);
            offset += token_len;
            if ( t[ offset ] != '"')
                {
                MABORT( "unterminated string");
                // === abort ===
                }  // unterminated string?

            offset++;
            is_in_string = 0;
            }  // in quoted string?
        else
            {
            offset += strspn( (t + offset), WHITESPACE);
            if ( t[ offset ] == '"')
                {
                is_in_string = 1;
                offset++;
                continue;  // === skip ===
                }  // start of string?
            else if ( isdigit( t[ offset ] ) )
                {
                token_len = strspn( (t + offset), NUMERIC);
                }  // start of numeric literal?
            else if ( isalpha( t[ offset ] ) || ( t[ offset ] == '_') )
                {
                token_len = strspn( (t + offset), WORD);
                // TODO:  non english chars?
                }  // start of "word" / identifier?
            else
                {
                token_len = 1;
                }  // special char?

            save_token( line_buf, t + offset, token_len, TT_UNKNOWN);
            offset += token_len;
            }  // not in a string?
        }  // get each token

        save_token( line_buf, "", 0, TT_END_STMT);
    }  // _________________________________________________________

/**
 * Re-examine the tokens on the current line,
 *  refine the "type" information for each token.
 */
static
void                    typify_line_tokens
    (
    t_logical_line *    line_buf        ///< line buffer from which we parse,
                                        ///  and to which we append the token-trackers
    )
    {
    int                 tk;
    t_token *           token;
    const t_token_mapping *
                        literal;

    for ( tk = 0; tk < line_buf->num_tokens; tk++)

        {
        token = &( line_buf->tokens[ tk ]);
        if ( ( token->type == TT_STRING) || ( token->type == TT_END_STMT) )
            {
            continue;  // === done ===
            }  // already know it's a string (or end-ln/stmt)?

        token->type = TT_IDENT;  // identifier, unless we identify it otherwise:
        for ( literal = KEYWORDS; literal->literal != NULL; literal++)

            {
            if ( strcmp( token->text, literal->literal) == 0)
                {
                token->type = literal->type;
                break;  // === found ===
                }  // match?

            }  // check each keyword/literal-symbol from table

        if ( token->type != TT_IDENT)
            {
            continue;  // === done ===
            }  // already know what this is?

        token->type = get_symbol_type( token->text);
        }  // recheck each token

    }  // _________________________________________________________

/**
 * Return the state transition table entry for a token and starting state.
 */
static
const t_parse_st *      get_tokens_st_trans_entry
    (
    t_token_type        type,           ///< type of token
    t_parse_state       state           ///< initial input parsing state.
    )
    {
    const t_parse_st *  tbl_entry;

    // TODO:  tuning of linear search!

    for ( tbl_entry = STATE_TABLE; tbl_entry->from != PS_UNDEF; tbl_entry++)

        {
        if ( tbl_entry->from != state)
            {
            continue;  // === skip ===
            }  // not the current starting state?

        if ( tbl_entry->token == type)
            {
            return tbl_entry;  // === found ===
            }  // matching token type (and starting state)?

        }  // check eash state transition entry

    return NULL;  // fail
    }  // _________________________________________________________

/**
 * Check that the keywords and symbols in the current line constitute
 *  a valid state transition in the current context.
 */
static
t_parse_state           check_state_transition
    (
    const t_logical_line *
                        line_buf,       ///< line buffer from which we parse,
                                        ///  and to which we append the token-trackers
    t_parse_state       state           ///< initial input parsing state.
    )
    {
    t_parse_state       cur_state;
    int                 ln;
    const t_token *     tk;
    const t_parse_st *  tbl_entry;

    cur_state = state;
    for ( ln = 0; ln < line_buf->num_tokens; ln++)

        {
        tk = line_buf->tokens + ln;
        tbl_entry = get_tokens_st_trans_entry( tk->type, cur_state);
        if ( tbl_entry == NULL)
            {
            // TODO: error message
            return PS_UNDEF;  // === abort ===
            }  // invalid / undefined transition?

        // TODO:  run callback from table to assemble parse tree
        cur_state = tbl_entry->to;
        printf( "(%d -> %d) ", (int) tk->type, (int) cur_state);  // TEMP (very)
        }  // check each token

    return cur_state;
    }  // _________________________________________________________

/**
 *
 * Compile / tokenize the given input file.
 * Return null if error (error will be printed to stderr)
 * TODO:  implement a return value, and better error strategy.
 */
void                    parse_file
    (
    const char *        file_name           ///< name of file to be tokenized.
    )
    {
    FILE *              infile;
    t_logical_line      line_buf;
    int                 ln;
    int                 is_fubar;
    t_parse_state       state;

    infile = fopen( file_name, "r");
    if ( infile == NULL)
        {
        fprintf( stderr, "Failed to open file: \"%s\"\n", file_name);
        return;  // === abort ===
        }  // failed to open file?

    // cycle through the lines, generate parse tree

    state = PS_INIT;
    is_fubar = 0;
    MCLEAR( line_buf);
    for (   line_buf.linenum = 1;
            read_logical_line( infile, &line_buf), line_buf.span > 0;
            line_buf.linenum += line_buf.span)

        {
        // printf( "%d:%s\n", line_buf.linenum, line_buf.text);

        tokenize_line( &line_buf);
        typify_line_tokens( &line_buf);

        for ( ln = 0; ln < line_buf.num_tokens; ln++)
            
            {
            printf( "%d.%d:{%s}, type %d\n", line_buf.linenum, ( ln + 1),
                    line_buf.tokens[ ln ].text,
                    (int) line_buf.tokens[ ln ].type);
            }  // dump each token (debug)

        printf( "Pre-line state: %d\n", (int) state);
        state = check_state_transition( &line_buf, state);
        printf( "Post-line state: %d %s\n", (int) state,
                ( ( state == PS_UNDEF) ? "(UNDEF!)" : "") );

        // TODO:  generate/append parse tree

        // take out the trash
        for ( ln = 0; ln < line_buf.num_tokens; ln++)
            { MFREE_NULL( line_buf.tokens[ ln ].text); }
        line_buf.num_tokens = 0;
        MFREE_NULL( line_buf.tokens);
        MFREE_NULL( line_buf.text);
        }  // tokenize each logical line

    fclose( infile);
    puts( "TODO: return parse tree");
    if ( is_fubar)
        {
        fputs( "FUBAR!\n", stderr);
        return;  // === abort ===
        }  // fouled up?

    // TODO:  return a meaningful data structure
    }  // _________________________________________________________


/* *** EOF *** */
