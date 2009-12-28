/**
 * Maintain the global and current context symbol table(s).
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
