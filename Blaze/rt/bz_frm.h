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

    /** hold information about parameters / variables / return vals for a function */
    typedef struct t_stk_frame
        {
        t_bz_size       size;           ///< total size of stack frame's inline data
        struct t_stk_frame *
                        parent;         ///< pointer to enclosing frame.
        t_bz_size       param_off;      ///< offset (in bytes) of parameters
        t_bz_size       param_sz;       ///< size (in bytes) of parameters
        t_bz_size       var_off;        ///< offset (in bytes) of variables
        t_bz_size       var_sz;         ///< size (in bytes) of variables
        t_bz_size       ret_off;        ///< offset (in bytes) of return value(s)
        t_bz_size       ret_sz;         ///< size (in bytes) of return value(s)

        // append data (t_bz_obj instances) at runtime...
        }
        t_stk_frame;

#ifdef	__cplusplus
}
#endif

#endif	/* _BZ_FRM_H */

