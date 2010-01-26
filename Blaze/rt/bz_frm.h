/* 
 * File:   bz_frm.h
 * Author: rob
 * Define stack frame data structure.
 * Created on December 28, 2009, 10:02 PM
 */

#ifndef _BZ_FRM_H
#define	_BZ_FRM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "bz_obj.h"

    // TODO:  consider the use of so many pointers:  what about relocation / reallocation?

    /** hold information about parameters / return vals for a function */
    typedef struct t_ret_buf
        {
        t_bz_size       size;           ///< total size of stack frame's inline data
        // TODO:  return reference list?
        }
        t_ret_buf;

    /** hold information about parameters / return vals for a function */
    typedef struct t_call_ret_frame
        {
        t_bz_size       size;           ///< total size of stack frame's inline data
        jmp_buf *       jump;           ///< longjmp buffer, in case of error
        struct t_stk_frame *
                        parent;         ///< pointer to enclosing frame.
        t_ret_buf       ret;            ///< return values
        int             num_params;     ///< number of input parameter pointers

        // append data (t_bz_obj instances) at runtime...
        }
        t_call_ret_frame;

    // TODO:  reimagine this
    /** hold information about parameters / variables / return vals for a function */
    typedef struct t_stk_frame
        {
        t_bz_size       size;           ///< total size of stack frame's inline data
        struct t_stk_frame *
                        parent;         ///< pointer to enclosing frame.
        t_call_ret_frame *
                        call_ret;       ///< input params and return values
        t_bz_size       var_off;        ///< offset (in bytes) of variables
        t_bz_size       var_sz;         ///< size (in bytes) of variables

        // append data (t_bz_obj instances) at runtime...
        }
        t_stk_frame;

#ifdef	__cplusplus
}
#endif

#endif	/* _BZ_FRM_H */

