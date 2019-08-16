/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: main.c
*
*   Description: Main driver for Huffman compressor and
*   decompressor program
*
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/huffman_tree.h"
#include "../include/utils.h"

// Helper function definitions
void compress(char *infile_name, char *outfile_name);
void decompress(char *infile_name, char *outfile_name);

int main(int argc, char* argv[]) {
    if (argc != 3 && argc != 4) 
    {
        fprintf(stderr, "Usage: %s <{-c/--compress, -d/--decompress}> "
                "<input file name> [output file name]\n",
                argv[0]);
        exit(1);
    }
    else if ((!strcmp(argv[1], "-c")) || (!strcmp(argv[1], "--compress")))
    {
        char *input_file_name = argv[2];
        char *compressed_file_name = (argc == 4) ? argv[3] : "default_compressed";
        compress(input_file_name, compressed_file_name);
    }
    else if ((!strcmp(argv[1], "-d"))|| (!strcmp(argv[1], "--decompress")))
    {
        char *compressed_file_name = argv[2];
        char *decompressed_file_name = argv[3] ? argv[3] : "default_decompressed";
        decompress(compressed_file_name, decompressed_file_name);
    }
    else
    {
        fprintf(stderr, "Invalid command. Run `./huffman` for help\n");
        exit(1);
    }
}

/*
 * Function:        compress
 * Description:     Write compressed encoded data to file
 * Parameters:      FILE *infile: pointer to the input file
 *                  FILE *outfile: pointer to the output file
 * Return:          void
 */
void compress(char *infile_name, char *outfile_name) 
{
    FILE *infile = fopen(infile_name, "rb");
    if (!infile)
    {
        fprintf(stderr, "Input file `%s` does not exist!\n", infile_name);
        exit(1);
    }

    // Reads in from file 
    int freq_array_length = 0;
    int *_freq_array = get_frequency_of_characters_from_file(infile, &freq_array_length);
    Array_T freq_array = create_unique_characters_freq_array(_freq_array, freq_array_length);
    
    // Builds Huffman tree
    Huffman_Tree_T huffman_tree = Huffman_tree_new();
    Huffman_tree_build(huffman_tree, freq_array);
    Array_T encoding = Huffman_tree_create_encoding_table(huffman_tree);
    
    FILE *outfile = fopen(outfile_name, "wb");
    if (!outfile)
    {
        fprintf(stderr, "File `%s` cannot be opened!\n", outfile_name);
        exit(1);
    }

    // Writes header to compressed file
    write_total_num_bits(_freq_array, encoding, outfile);
    write_header(freq_array, outfile);
    
    // Writes compressed body
    write_body(encoding, infile, outfile);
    
    // Deallocates memory and close out files
    free(_freq_array);
    Array_free(&freq_array);
    Huffman_tree_free(&huffman_tree);
    fclose(infile);
    fclose(outfile); 
}

/*
 * Function:        decompress
 * Description:     Write decompressed decoded data to file
 * Parameters:      FILE *infile: pointer to the input file
 *                  FILE *outfile: pointer to the output file
 * Return:          void
 */
void decompress(char *infile_name, char *outfile_name) 
{
    FILE *infile = fopen(infile_name, "r");
    if (!infile)
    {
        fprintf(stderr, "Compressed file `%s` does not exist!\n", infile_name);
        exit(1);
    }

    // Reads in header and build Huffman tree for decoding
    uint64_t total_num_bits = read_total_num_bits(infile);
    Array_T entries = read_header(infile);

    Huffman_Tree_T huffman_tree = Huffman_tree_new();
    Huffman_tree_build(huffman_tree, entries);
    Huffman_tree_create_encoding_table(huffman_tree);

    FILE *outfile = fopen(outfile_name, "wb");
    if (!outfile)
    {
        fprintf(stderr, "File `%s` cannot be opened!\n", outfile_name);
        exit(1);
    }

    // Reads in body, decodes body, and write to outfile
    read_body(huffman_tree, total_num_bits, infile, outfile);
    
    // Deallocates memory and close out filse
    Array_free(&entries);
    Huffman_tree_free(&huffman_tree);
    fclose(infile);
    fclose(outfile); 
}

