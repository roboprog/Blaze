/* 
 * File:   symtab.h
 * Author: rob
 *
 * Created on August 14, 2009, 12:48 PM
 */

#ifndef _SYMTAB_H
#define	_SYMTAB_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "token_type.h"

/**
 * Return the type of the given identifier by looking it up in the symbol table.
 *  Return TT_UNKNOWN if the identifier is not found.
 */
t_token_type            get_symbol_type
    (
    const char *        identifier          /**< name of identifier to be categorized */
    )
    ;

#ifdef	__cplusplus
}
#endif

#endif	/* _SYMTAB_H */

