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

        // append class specific data following...
        }
        t_bz_obj;

#ifdef	__cplusplus
}
#endif

#endif	/* _BZ_OBJ_H */

