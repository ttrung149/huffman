/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: test_utils.c
*
*   Description: Test driver for utils module
*
****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/huffman_tree.h"
#include "../include/utils.h"

int main() {
    FILE *infile = fopen("tests/test_utils_sample.txt", "rb");

    int freq_array_length = 0;
    int *_freq_array = get_frequency_of_characters_from_file(infile, &freq_array_length);
    Array_T freq_array = create_unique_characters_freq_array(_freq_array, freq_array_length);
    
    Huffman_Tree_T huffman_tree = Huffman_tree_new();
    Huffman_tree_build(huffman_tree, freq_array);

    Huffman_node *root = Huffman_tree_get_root(huffman_tree);
    printf("Root frequency: %d\n", root->frequency);
    Array_T encoding = Huffman_tree_create_encoding_table(huffman_tree);
    
    // Compress sample file to test_compressed
    FILE *outfile = fopen("tests/test_compressed.txt", "wb");
    write_total_num_bits(_freq_array, encoding, outfile);
    write_header(freq_array, outfile);
    write_body(encoding, infile, outfile);
    fclose(outfile);

    FILE *compressed = fopen("tests/test_compressed.txt", "r");
    
    // Decompress sample file to test_decompressed
    uint64_t total_num_bits = read_total_num_bits(outfile);

    printf("TOTAL NUM BITS: %llu \n", total_num_bits);
    Array_T entries = read_header(outfile);
    Huffman_Tree_T decompressed_huffman_tree = Huffman_tree_new();
    Huffman_tree_build(decompressed_huffman_tree, entries);
    Huffman_tree_create_encoding_table(decompressed_huffman_tree);

    FILE *decompressed = fopen("tests/test_decompressed.txt", "wb");
    read_body(decompressed_huffman_tree, total_num_bits, compressed, decompressed);
    
    fclose(compressed);
    fclose(decompressed);

    Array_free(&entries);
    Huffman_tree_free(&decompressed_huffman_tree);

    free(_freq_array);
    Huffman_tree_free(&huffman_tree);
    Array_free(&freq_array);

    fclose(infile);
    fclose(outfile);
    return 0;
}
