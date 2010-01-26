/* 
 * File:   bz_io.h
 * Author: rob
 *
 * Created on January 17, 2010, 3:40 PM
 */

#ifndef _BZ_IO_H
#define	_BZ_IO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "bz_frm.h"
#include "bz_str.h"

    /** initialize the I/O runtime library */
    void                bzc_io_rt_init( void)
        ;


    /**
     * Write a string (line) to stdout.
     *  Expects a single string parameter in call_ret
     */
    void                bz_puts
        (
        t_call_ret_frame *
                        call_ret
        )
        ;

    /**
     * Read a string (line) from stdin
     *  Expects no parameters in call_ret
     */
    void                bz_gets
        (
        t_call_ret_frame *
                        call_ret
        )
        ;


#ifdef	__cplusplus
}
#endif

#endif	/* _BZ_IO_H */

