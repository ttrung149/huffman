/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: utils.c
*
*   Description: Implementation for utils module, containing files io
*   and helper functions for the compressor
*
*   See comments on top of each function to understand the interface
*
****************************************************************/
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
// #include "../hanson/include/except.h"
#include "../include/priority_queue.h"
#include "../include/huffman_tree.h"
#include "../include/utils.h"
// #include "../include/bitpack.h"

/*
 * Function:        get_frequency_of_characters_from_file
 * Description:     Gets array of Priority_queue node for Huffman 
 *                  tree building later on
 * Parameters:      FILE *infile: pointer to file
 * Return           Pointer to struct `Array_T`
 */
Array_T get_frequency_of_characters_from_file(FILE *infile)
{
    assert(infile);
    int *freq_array = (int *)calloc(MAX_NUM_CHAR, sizeof(int));
    int num_unique_chars = 0;

    // Create a table where the index is the character, value is
    // the frequency of that character in the file
    int c;
    while ((c = fgetc(infile)) != EOF) 
    {
        if (freq_array[c] == 0) num_unique_chars++;
        freq_array[c]++;
    }
    assert(num_unique_chars > 0);

    // Allocate space for the Array_T to be returned
    Array_T freq_array_from_file = Array_new(num_unique_chars, sizeof(Node));
    int array_index = 0;
    for (int i = 0; i < MAX_NUM_CHAR; i++)
    {
        // Create a Priority_queue Node from the key value pari in the table
        if (freq_array[i] != 0)
        {
            // Allocate space for Priority_queue Node
            Node *node = malloc(sizeof(Node));
            assert(node);
            node->value = freq_array[i];
            
            // Allocate space for Huffman_node (obj pointer of Priority_queue Node)
            Huffman_node *obj = malloc(sizeof(Huffman_node));
            assert(obj);
            obj->frequency = freq_array[i];
            obj->key = (char)i;
            obj->left_node = NULL;
            obj->right_node = NULL;
            node->obj = obj;

            // Put Priority_queue node to the allocated array
            Array_put(freq_array_from_file, array_index, node);
            array_index++;

            free(node);
            continue;
        }
    }
    free(freq_array);
    return freq_array_from_file;
}

/*
 * Function:        write_header
 * Description:     Write to header for compressed file in the following
 *                  format. This allows decompressor to rebuild Huffman tree
 * 
 *                  <TOTAL_NUM_CHAR><TOTAL_UNIQUE_CHAR>[char_1][freq_char_1]...
 * 
 * Parameters:      int size: size of infile
 *                  FILE *infile: pointer to file
 *                  Pointer to struct `Array_T`
 * Return:          void
 */
void write_header(int size, Array_T freq_array, FILE *outfile)
{
    assert(outfile && freq_array);
    // Header format: 
    //<TOTAL_NUM_CHAR><TOTAL_UNIQUE_CHAR>[char_1][freq_char_1]...
    
    // Write total number of characters in the file to compressed file
    putw(size, outfile);

    // Write number of unique characters in the file to compressed file
    int freq_array_length = Array_length(freq_array);
    putw(freq_array_length, outfile);
    
    // Write each unique character followed by the frequency to header
    for (int i = 0; i < freq_array_length; i++)
    {
        Node *curr_node = (Node *)Array_get(freq_array, i);
        char key = ((Huffman_node *)(curr_node->obj))->key;
        int value = curr_node->value;

        fputc(key, outfile);
        putw(value, outfile);
    }
}

/*
 * Function:        read_header
 * Description:     Read header in compressed file. Returns an Array_T so
 *                  decompressor can rebuild Huffman tree
 * Parameters:      FILE *infile: pointer to file
 * Return:          Pointer to struct `Array_T`
 */
Array_T read_header(FILE *infile)
{
    assert(infile);
    // Get total number of char in file
    int total_num_char = getw(infile);
    (void) total_num_char;

    // Get total number of unique char in file
    int freq_array_length = getw(infile);
    
    Array_T entries = Array_new(freq_array_length, sizeof(Node));
    for (int i = 0; i < freq_array_length; i++)
    {
        char key = fgetc(infile);
        int value = getw(infile);
        
        // printf("%c: %d\n", key, value);
        // Create new Priority_queue Node from header
        Node *node = malloc(sizeof(Node));
        assert(node);
        node->value = value;

        // Create Huffman_node from header
        Huffman_node *obj = malloc(sizeof(Huffman_node));
        assert(obj);
        obj->frequency = value;
        obj->key = key;
        obj->left_node = NULL;
        obj->right_node = NULL;
        node->obj = obj;

        // Insert Priority_queue Node to allocated array
        Array_put(entries, i, node);
        free(obj);
        free(node);
    }

    return entries;
}
