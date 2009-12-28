/* 
 * File:   memwrap.h
 * Author: rob
 *
 * Wrapper for common memory management tasks.
 *
 * Created on June 25, 2009, 1:13 PM
 */

#ifndef _MEMWRAP_H
#define	_MEMWRAP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <malloc.h>

/** clear the given buffer */
#define MCLEAR( buf)    memset( &( buf), '\0', sizeof( buf) )

/** extend a dynamic array by one element */
#define MEXTEND_ARRAY( a, n)    \
        (   \
        (n)++,  \
        (a) = realloc( (a), (n) * sizeof( a[0]) )   \
        )

/** free memory and null out the pointer */
#define MFREE_NULL( p)  ( ( p != NULL) ?   \
        ( free( (void *) p), p = NULL)  :    \
        p )

#ifdef	__cplusplus
}
#endif

#endif	/* _MEMWRAP_H */
