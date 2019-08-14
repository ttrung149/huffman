/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: utils.h
*
*   Description: Header file for utils module, containing files io
*   and helper functions for the compressor
*
*   See comments on top of each function to understand the interface
*
****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../hanson/include/array.h"

#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

/*
 * Function:        get_frequency_of_characters_from_file
 * Description:     Gets array of Priority_queue node for Huffman 
 *                  tree building later on
 * Parameters:      FILE *infile: pointer to file
 * Return           Pointer to struct `Array_T`
 */
extern Array_T get_frequency_of_characters_from_file(FILE *infile);
/*
 * Function:        write_header
 * Description:     Write header to compressed file in the following
 *                  format. This allows decompressor to rebuild Huffman tree
 * 
 *                  <TOTAL_NUM_CHAR><TOTAL_UNIQUE_CHAR>[char_1][freq_char_1]...
 * 
 * Parameters:      int size: size of infile
 *                  FILE *infile: pointer to file
 *                  Pointer to struct `Array_T`
 * Return:          void
 */
extern void write_header(int size, Array_T freq_array, FILE *outfile);

/*
 * Function:        read_header
 * Description:     Read header in compressed file. Returns an Array_T so
 *                  decompressor can rebuild Huffman tree
 * Parameters:      FILE *infile: pointer to file
 * Return:          Pointer to struct `Array_T`
 */
extern Array_T read_header(FILE *infile);
#endif
