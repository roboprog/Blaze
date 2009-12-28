/**
 * Maintain the global and current context symbol table(s).
 */

// *** import ****

#include <stdlib.h>

#include "symtab.h"

// *** constants ***

// **** types ***

/** used mapping of literals / reserved words to token types */
typedef struct t_ident_mapping
    {
    const char *        literal;        /**< literal symbol or keyword */
    t_token_type        type;           /**< type */
    } t_ident_mapping;

// *** data ***

/** hard coded mappings for built-in identifiers */
static
t_ident_mapping         BUILTINS [] =
    {
        { "rt",         TT_NAMESPACE },
        { "puts",       TT_FUNC_NAME },

        { NULL }
    };


// **** routines ***

/**
 * Return the type of the given identifier by looking it up in the symbol table.
 *  Return TT_UNKNOWN if the identifier is not found.
 */
t_token_type            get_symbol_type
    (
    const char *        identifier          /**< name of identifier to be categorized */
    )
    {
    const t_ident_mapping *
                        ident;

    // TODO:  determine context

    // TODO:  better differentiation of namespace and other identifiers?

    for ( ident = BUILTINS; ident->literal != NULL; ident++)
        
        {
        if ( strcmp( ident->literal, identifier) == 0)
            {
            return ident->type;  // === found ===
            }  // match?

        }  // scan each table entry
    
    return TT_UNKNOWN;  // fail
    }  // _________________________________________________________


/* *** EOF *** */
