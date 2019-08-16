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
#include <stdint.h>
#include <inttypes.h>
#include "../hanson/include/array.h"

#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

/*
 * Function:        get_frequency_of_characters_from_file
 * Description:     Gets array of character frequencies from file
 * Parameters:      FILE *infile: pointer to file
 *                  Pointer to num_unique_chars, which will be updated
 *                  after the function is called
 * Return           int: frequencies of each character array
 */
extern int *get_frequency_of_characters_from_file(FILE *infile, int *num_unique_chars);

/*
 * Function:        create_unique_characters_freq_array
 * Description:     Builds array of unique character frequencies for Huffman 
 *                  tree building later on
 * Parameters:      int *freq_array: pointer to frequency array
 *                  int num_unique_char: length of freq_array
 * Return           Array_T
 */
extern Array_T create_unique_characters_freq_array(int *freq_array, int num_unique_char);

/*
 * Function:        write_total_num_bits
 * Description:     Write the total number of bits compressed to the top of the
 *                  compressed file.
 * 
 * Parameters:      FILE *outfile: pointer to file
 *                  int *freq_array
 *                  Array_T encoding
 * Return:          void
 */
extern void write_total_num_bits(int *freq_array, Array_T encoding, FILE *outfile);

/*
 * Function:        read_total_num_bits
 * Description:     Read the total number of bits compressed from the top of the
 *                  compressed file.
 * 
 * Parameters:      FILE *infile: pointer to file
 * Return:          void
 */
extern uint64_t read_total_num_bits(FILE *infile);

/*
 * Function:        write_header
 * Description:     Write header to compressed file in the following
 *                  format. This allows decompressor to rebuild Huffman tree
 * 
 *                  <TOTAL_UNIQUE_CHAR>[char_1][freq_char_1]...
 * 
 * Parameters:      FILE *infile: pointer to file
 *                  Array_T of each character frequencies from provided file
 * Return:          void
 */
extern void write_header(Array_T freq_array, FILE *outfile);

/*
 * Function:        read_header
 * Description:     Read header in compressed file. Returns an Array_T so
 *                  decompressor can rebuild Huffman tree
 * Parameters:      FILE *infile: pointer to file
 * Return:          Pointer to struct `Array_T`
 */
extern Array_T read_header(FILE *infile);

/*
 * Function:        write_body
 * Description:     Write body to compressed file
 * Parameters:      Array_T encoding: table contains character encodings
 *                  FILE *infile: pointer to the input file
 *                  FILE *outfile: pointer to the output file
 * Return:          void
 */
extern void write_body(Array_T encoding, FILE *infile, FILE *outfile);

/*
 * Function:        read_body
 * Description:     Read body from compressed file and write to decompressed file
 * Parameters:      Huffman_Tree_T encoding: Huffman tree with character encodings
 *                  uint64_t total_num_bits: total number of encoded bits
 *                  FILE *infile: pointer to the compressed file
 *                  FILE *outfile: pointer to the decompressed file
 * Return:          void
 */
extern void read_body(Huffman_Tree_T encoding, uint64_t total_num_bits,
                        FILE *infile, FILE *outfile);
#endif
