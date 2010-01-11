/* 
 * File:   bz_str.h
 * Author: rob
 * Define "string" object, and routines with native (C) implementations.
 *
 * Created on December 29, 2009, 1:17 PM
 */

#ifndef _BZ_STR_H
#define	_BZ_STR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "bz_obj.h"

/** 15 bytes plus \0 will be most stored in-line in frame */
#define BZ_STR_MAX_INLINE 16

    /** hold information about a string */
    typedef struct t_bz_str
        {
        t_bz_obj        i;              ///< inherited fields
        int             usage;          ///< flag to indicate "encoding",
                                        ///  0 = unknown / bytes / 7-bit,
                                        ///  other values (utf-8, html, sql...)
                                        ///  defined / registered at run-time
        t_bz_size       size;           ///< length in bytes,
                                        ///   not accounting for multi-byte chars,
                                        ///   NOT including an extra '\0' terminator.
        char *          allocated;      ///< externally allocated data,
                                        ///   if applicable.
        char            inline_bytes [ BZ_STR_MAX_INLINE ];
                                        ///< marker for start of inline data,
                                        ///   if applicable.

        // append runtime data following...
        }
        t_bz_str;

    /** initialize the string runtime library */
    void                bzc_str_rt_init( void)
        ;

    /** C callable routine to init an immutable blaze string from a C string */
    void                bzc_str_c2bz
        (
        jmp_buf *       jump,           ///< longjmp buffer, in case of error
        t_bz_str *      bz_str,         ///< blaze string struct to init
        const char *    src             ///< source string constant
        )
        ;

    /** C callable routine to init a mutable blaze string from a C string */
    void                bzc_str_m_c2bz
        (
        jmp_buf *       jump,           ///< longjmp buffer, in case of error
        t_bz_str *      bz_str,         ///< blaze string struct to init
        const char *    src             ///< source string constant
        )
        ;

    /** TODO: init a string from another blaze string / expression */

    /** destroy a string */
    void                bz_str_done
        (
        jmp_buf *       jump,           ///< longjmp buffer, in case of error
        t_bz_str *      bz_str          ///< blaze string struct to destroy
        )
        ;

    /** return a pointer to the start of the active byte buffer for the string */
    const char *        bzc_str_data
        (
        jmp_buf *       jump,           ///< longjmp buffer, in case of error
        t_bz_str *      bz_str          ///< blaze string struct to get data from
        )
        ;

#ifdef	__cplusplus
}
#endif

#endif	/* _BZ_STR_H */

