/*
 * File:   bz_io.c
 * Author: rob
 * Define "I/O" object(s), and routines with native (C) implementations.
 *
 * Created on January 17, 2010, 4:34 PM
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

#include <stdio.h>

#include "bz_io.h"

// *** constants ***

// **** types ***

// *** data ***

// **** routines ***

    /**
     * Write a string (line) to stdout.
     *  Expects a single string parameter in call_ret
     */
    void                bz_puts
        (
        t_call_ret_frame *
                        call_ret
        )
    {
    char *              param_ptr;
    const t_bz_str *    bz_str;
    int                 error;

    // assume that call_ret and nested longjmp buffer are defined
    if ( call_ret->num_params < 1)
        {
        fprintf( "INTERNAL ERROR: no string buffer at %s:%d", __FILE__, __LINE__);
        longjmp( call_ret->jump, 1);  // === abort ===
        }  // no input string?

    param_ptr = ( (char *) call_ret) + sizeof( t_call_ret_frame);  // TODO: macro for this
    bz_str = (const t_bz_str *) ( (void * *) param_ptr)[ 0 ];  // TODO: indexing logic

    // TODO:  make actual FILE * analog, set up for stdout

    fwrite( bzc_str_data( call_ret->jump, bz_str), bz_str->size, 1, stdout);
    error = ferror( stdout);
    if ( error)
        {
        clearerr( stdout);
        fprintf( "TODO: I/O exception at %s:%d (%d)", __FILE__, __LINE__, error);
        longjmp( call_ret->jump, 1);  // === abort ===
        }  // I/O error (exception)?

    // TODO:  many things (suppress 2nd I/O call, portable newlines...?)
    fputc( '\n', stdout);
    error = ferror( stdout);
    if ( error)
        {
        clearerr( stdout);
        fprintf( "TODO: I/O exception at %s:%d (%d)", __FILE__, __LINE__, error);
        longjmp( call_ret->jump, 1);  // === abort ===
        }  // I/O error (exception)?

    }  // _________________________________________________________


/* *** EOF *** */