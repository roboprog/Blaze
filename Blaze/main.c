/* 
 * File:   main.c
 * Author: rob
 *
 * Created on June 24, 2009, 12:40 PM
 */

/*
    blaze: mongrel language mashing perl and pascal concepts (among others)

    Copyright (C) 2009, Robin R Anderson
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

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>


#include "rt/bz_io.h"
#include "rt/bz_str.h"
#include "parser.h"

/**
 * Quick and dirty testing bogons
 */
static
void                    dev_test_bogons( void)
    {
    jmp_buf             on_err;
    t_bz_size           cr_sz;
    t_call_ret_frame *  call_ret;
    char *              param_ptr;
    t_bz_str            str;

    if ( setjmp( on_err) )
        {
        // TODO:  *handling* of error
        fprintf( stderr, "GAME OVER at %s:%d", __FILE__, __LINE__);
        exit( 1);  // === abort ===
        }  // problem?

    // fake a "frame", as if called from actual "blaze" program
    cr_sz = sizeof( t_call_ret_frame) + sizeof( t_bz_str *);
    call_ret = malloc( (size_t) cr_sz);
    if ( call_ret == NULL)
        {
        fprintf( stderr, "ERROR: failed malloc at %s:%d", __FILE__, __LINE__);
        longjmp( on_err, 1);  // === abort ===
        }  // allocation failed?

    call_ret->size = cr_sz;
    call_ret->jump = &on_err;
    call_ret->parent = NULL;
    call_ret->num_params = 1;
    param_ptr = ( (char *) call_ret) + sizeof( t_call_ret_frame);  // TODO: macro for this
    *( (t_bz_str * *) param_ptr) = &str;

    // TODO:  make a function to create frames, create one for *each* call
    // TODO:  remove pointers from frames, use offsets
    //      (so that frames can be suballocated from a relocatable buffer)

    bzc_str_c2bz( &on_err, &str, "Hello");
    bz_puts( call_ret);
    bz_str_done( &on_err, &str);

    bzc_str_c2bz( &on_err, &str, "I don't know why you say goodbye");
    bz_puts( call_ret);
    bz_str_done( &on_err, &str);

    bzc_str_c2bz( &on_err, &str, "Hello");
    bz_puts( call_ret);
    bz_str_done( &on_err, &str);
    }  // _________________________________________________________

/**
 * Interpret or compile the program(s) indicated.
 */
int                     main
    (
    int 		argc,
    char * *            argv
    )
    {

    bzc_str_rt_init();

    dev_test_bogons();
    
    // TODO:  arg parsing
    parse_file( argv[ 1 ]);
    puts( "TODO: run");
    return (EXIT_SUCCESS);
    }  // _________________________________________________________


/* *** EOF *** */
