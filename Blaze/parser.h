/* 
 * File:   parser.h
 * Author: rob
 *
 * Created on June 25, 2009, 12:50 PM
 */

#ifndef _PARSER_H
#define	_PARSER_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Compile / tokenize the given input file.
 *Return null if error (error will be printed to stderr)
 */
void                    parse_file
    (
    const char *        file_name           ///< name of file to be tokenized.
    )
    ;


#ifdef	__cplusplus
}
#endif

#endif	/* _PARSER_H */

