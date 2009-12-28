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
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
