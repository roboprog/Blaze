/* 
 * File:   main.c
 * Author: rob
 *
 * Created on June 24, 2009, 12:40 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

/**
 * Interpret or compile the program(s) indicated.
 */
int                     main
    (
    int 		argc,
    char * *            argv
    )
    {

    // TODO:  arg parsing
    parse_file( argv[ 1 ]);
    puts( "TODO: run");
    return (EXIT_SUCCESS);
    }  // _________________________________________________________


/* *** EOF *** */
