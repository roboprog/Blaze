/* 
 * File:   token_type.h
 * Author: rob
 *
 * Created on August 14, 2009, 12:52 PM
 */

#ifndef _TOKEN_TYPE_H
#define	_TOKEN_TYPE_H

#ifdef	__cplusplus
extern "C" {
#endif

/** enumeration of token types */
typedef enum t_token_type
    {
    TT_UNKNOWN = 0,                     /**< unknown token */
    TT_END_STMT,                        /**< end of statement (aka newline) */
    TT_STRING,                          /**< string (literal?) type */
    TT_KW_RUN,                          /**< run keyword */
    TT_KW_END,                          /**< end keyword */

    TT_OPEN_PAREN,                      /**< "(" char */
    TT_CLOSE_PAREN,                     /**< ")" char */
    TT_NAMESPACE_SEP,                   /**< ":" char, used after namespace prefix */

    TT_IDENT,                           /**< identifier, type not yet determined */

    TT_NAMESPACE,                       /**< namespace */
    TT_FUNC_NAME,                       /**< function name */
    TT_DATA_TYPE,                       /**< data type */

    TT_UNDEF  /**< dummy end of enum */
    } t_token_type;

#ifdef	__cplusplus
}
#endif

#endif	/* _TOKEN_TYPE_H */

