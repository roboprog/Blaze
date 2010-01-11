/* 
 * File:   bz_obj.h
 * Author: rob
 * Define root "object" data structure for runtime library.
 *
 * Created on December 28, 2009, 8:21 PM
 */

#ifndef _BZ_OBJ_H
#define	_BZ_OBJ_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <setjmp.h>
    
    /** provide a 64 bit "size_t" surrogate for the project */
    typedef unsigned long long  t_bz_size;

    /** hold information about a function (method?) */
    typedef struct t_bz_func
        {
        t_bz_size       size;           ///< total size of function's inline data
        int             is_native;      ///< non-0 for a native (C) implementation
        void *          ptr;            ///< loaded implementation

        // append func specific data following...
        }
        t_bz_func;

    /** hold information about a class */
    typedef struct t_bz_class
        {
        t_bz_size       size;           ///< total size of class's inline data

        // append class specific data following...
        }
        t_bz_class;

    /** hold information about an object */
    typedef struct t_bz_obj
        {
        t_bz_size       size;           ///< total size of object's inline data
        int             class_selector; ///< index into class def table
        int             ref_cnt;        ///< reference count
        int             is_mutable;     ///< 0 for an immmutable instance

        // append class specific data following...
        }
        t_bz_obj;

#if 0
    /** hold a pool of bytes for "folded" objects / primitives */
    typedef struct t_bz_arena
        {
        char *          buf;            ///< the buffer for every object in pool
        t_bz_size       size;           ///< total size of buffer
        struct t_bz_arena_entry_idx *
                        entry_list;     ///< index into entries
        struct t_bz_arena_free *
                        free_list;      ///< unused space within arena, in not null
        }
        t_bz_arena;
#endif  // 0 - dead code


#ifdef	__cplusplus
}
#endif

#endif	/* _BZ_OBJ_H */

