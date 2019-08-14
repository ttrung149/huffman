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

    Array_T array = get_frequency_of_characters_from_file(infile);
    Huffman_Tree_T huffman_tree = Huffman_tree_new();
    Huffman_tree_build(huffman_tree, array);

    Huffman_node *root = Huffman_tree_get_root(huffman_tree);
    printf("Root frequency: %d\n", root->frequency);

    FILE *outfile = fopen("tests/header.txt", "wb");
    write_header(root->frequency, array, outfile);
    fclose(outfile);

    FILE *outfile_1 = fopen("tests/header.txt", "r");
    Array_T entries = read_header(outfile);
    fclose(outfile_1);

    Array_free(&entries);
    Huffman_tree_free(&huffman_tree);
    Array_free(&array);

    fclose(infile);
    fclose(outfile);
    return 0;
}
