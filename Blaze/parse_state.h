/* 
 * File:   parse_state.h
 * Author: rob
 *
 * Created on September 1, 2009, 12:33 PM
 */

#ifndef _PARSE_STATE_H
#define	_PARSE_STATE_H

#ifdef	__cplusplus
extern "C" {
#endif


/** enumeration for possible states during parsing (TODO: move into a header) */
typedef enum t_parse_state
    {
    PS_DUMMY = 0,                       /**< unknown state */
    PS_INIT,                            /**< file just loaded, about to scan */
    PS_RUN_END,                         /**< end of "run" line */
    PS_MOD_EXEC_BEGIN,                  /**< hit run, about to initialize module (run program) */
    PS_MOD_EXEC_END,                    /***< hit end concluding executable block and thus module */
    PS_NEXT_STMT,                       /**< just finished a statement, expecting another (or end) */
    PS_AWAIT_QUAL_SEP,                  /**< hit namespace, expecting seperator */

    PS_UNDEF  /**< dummy end-of-enum */
    } t_parse_state;


#ifdef	__cplusplus
}
#endif

#endif	/* _PARSE_STATE_H */

