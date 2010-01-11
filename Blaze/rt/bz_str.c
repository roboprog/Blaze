/*
 * File:   bz_str.c
 * Author: rob
 * Define "string" object, and routines with native (C) implementations.
 *
 * Created on January 4, 2010, 9:24 PM
 */

/*
    blaze: mongrel language mashing perl and pascal concepts (among others)

    Copyright (C) 2009, 2010, Robin R Anderson
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

#include "bz_str.h"

// *** constants ***

// **** types ***

/** module runtime data */
typedef struct t_mod_data
    {
    int                 is_init;        ///< non-0 if initialization has been done
    }
    t_mod_data;

// *** data ***

static
t_mod_data              M;

// **** routines ***

/** initialize the string runtime library */
void                    bzc_str_rt_init( void)
    {
    if ( M.is_init)
        {
        return;  // === done ===
        }  // initialized?

    // TODO:  stuff, as needed...
    M.is_init = 1;
    }  // _________________________________________________________

/** C callable routine to init an immutable blaze string from a C string */
void                    bzc_str_c2bz
    (
    jmp_buf *           jump,           ///< longjmp buffer, in case of error
    t_bz_str *          bz_str,         ///< blaze string struct to init
    const char *        src             ///< source string constant
    )
    {
    t_bz_size           num_str_bytes;
    int                 is_inline;

    if ( jump == NULL)
        {
        fprintf( "INTERNAL ERROR: no jump buffer at %s:%d", __FILE__, __LINE__);
        exit( 1);  // === abort ===
        }  // can't even throw up?

    if ( bz_str == NULL)
        {
        fprintf( "INTERNAL ERROR: no string buffer at %s:%d", __FILE__, __LINE__);
        longjmp( *jump, 1);  // === abort ===
        }  // nowhere for data?

    if ( src == NULL)
        {
        fprintf( "INTERNAL ERROR: no string source at %s:%d", __FILE__, __LINE__);
        longjmp( *jump, 1);  // === abort ===
        }  // no data?

    // memset( bz_str, '\0', sizeof( t_bz_str) );  // TODO:  eliminate need for this
    num_str_bytes = strlen( src) + 1;
    is_inline = ( num_str_bytes <= BZ_STR_MAX_INLINE);

    // TODO:  "object" constructor:
    bz_str->i.size = sizeof( t_bz_str);
    bz_str->i.class_selector = 0;  // TODO: class def index
    bz_str->i.ref_cnt = 1;  // presumably the caller is using it
    bz_str->i.is_mutable = 0;

    bz_str->usage = 0;  // bytes, 7bit ascii
    bz_str->size = num_str_bytes - 1;
    if ( is_inline)
        {
        bz_str->allocated = NULL;
        memcpy( bz_str->inline_bytes, src, num_str_bytes);
        }  // short string?
    else
        {
        bz_str->allocated = strdup( src);
        bz_str->inline_bytes[ 0 ] = '\0';
        }  // long string?
    // TODO:  fold asciiz string into a table, get offset????
    }  // _________________________________________________________

    /** destroy a string */
    void                bz_str_done
        (
        jmp_buf *       jump,           ///< longjmp buffer, in case of error
        t_bz_str *      bz_str          ///< blaze string struct to destroy
        )
    {
    if ( jump == NULL)
        {
        fprintf( "INTERNAL ERROR: no jump buffer at %s:%d", __FILE__, __LINE__);
        exit( 1);  // === abort ===
        }  // can't even throw up?

    if ( bz_str == NULL)
        {
        fprintf( "INTERNAL ERROR: no string buffer at %s:%d", __FILE__, __LINE__);
        longjmp( *jump, 1);  // === abort ===
        }  // nowhere for data?

    // TODO:  "object" destructor:
    ( bz_str->i.ref_cnt)--;  // TODO: check for 1 -> 0 transition

    if ( bz_str->allocated != NULL)
        {
        free( bz_str->allocated);
        bz_str->allocated = NULL;
        }  // allocated "large" string?
    // else: inline string will just go away
    }  // _________________________________________________________

    /** return a pointer to the start of the active byte buffer for the string */
    const char *        bzc_str_data
        (
        jmp_buf *       jump,           ///< longjmp buffer, in case of error

        t_bz_str *      bz_str          ///< blaze string struct to get data from
        )
    {
    if ( jump == NULL)
        {
        fprintf( "INTERNAL ERROR: no jump buffer at %s:%d", __FILE__, __LINE__);
        exit( 1);  // === abort ===
        }  // can't even throw up?

    if ( bz_str == NULL)
        {
        fprintf( "INTERNAL ERROR: no string buffer at %s:%d", __FILE__, __LINE__);
        longjmp( *jump, 1);  // === abort ===
        }  // nowhere for data?

    return ( bz_str->allocated != NULL ?
            bz_str->allocated :
            bz_str->inline_bytes);
    }  // _________________________________________________________


/* *** EOF *** */
