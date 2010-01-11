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


#include "rt/bz_str.h"
#include "parser.h"

/**
 * Quick and dirty testing bogons
 */
static
void                    dev_test_bogons( void)
    {
    jmp_buf             on_err;
    t_bz_str            str;

    if ( setjmp( on_err) )
        {
        // TODO:  *handling* of error
        fprintf( stderr, "GAME OVER at %s:%d", __FILE__, __LINE__);
        exit( 1);  // === abort ===
        }  // problem?

    bzc_str_c2bz( &on_err, &str, "Hello");
    puts( bzc_str_data( &on_err, &str) );
    bz_str_done( &on_err, &str);

    bzc_str_c2bz( &on_err, &str, "I don't know why you say goodbye");
    puts( bzc_str_data( &on_err, &str) );
    bz_str_done( &on_err, &str);

    bzc_str_c2bz( &on_err, &str, "Hello");
    puts( bzc_str_data( &on_err, &str) );
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
