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
#include <inttypes.h>
#include <assert.h>
#include "../include/priority_queue.h"
#include "../include/huffman_tree.h"
#include "../include/utils.h"
#include "../include/bitpack.h"

#define SIZE_OF_CHAR_IN_BITS 8
#define SIZE_OF_UINT64_IN_BITS 64

/*
 * Function:        get_frequency_of_characters_from_file
 * Description:     Gets array of character frequencies from file
 * Parameters:      FILE *infile: pointer to file
 *                  Pointer to num_unique_chars, which will be updated
 *                  after the function is called
 * Return           int: frequencies of each character array
 */
int *get_frequency_of_characters_from_file(FILE *infile, int *num_unique_chars)
{
    assert(infile);
    int *freq_array = (int *)calloc(MAX_NUM_CHAR, sizeof(int));
    int _num_unique_chars = 0;

    // Create a table where the index is the character, value is
    // the frequency of that character in the file
    int c;
    while ((c = fgetc(infile)) != EOF)
    {
        if (freq_array[c] == 0)
            _num_unique_chars++;
        freq_array[c]++;
    }
    assert(_num_unique_chars > 0);

    *num_unique_chars = _num_unique_chars;
    fseek(infile, 0, SEEK_SET);
    return freq_array;
}

/*
 * Function:        create_unique_characters_freq_array
 * Description:     Builds array of unique character frequencies for Huffman 
 *                  tree building later on
 * Parameters:      int *freq_array: pointer to frequency array
 *                  int num_unique_char: length of freq_array
 * Return           Array_T
 */
Array_T create_unique_characters_freq_array(int *freq_array, int num_unique_char)
{
    // Allocate space for the Array_T to be returned
    Array_T freq_array_from_file = Array_new(num_unique_char, sizeof(Node));
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
    return freq_array_from_file;
}

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
void write_total_num_bits(int *freq_array, Array_T encoding, FILE *outfile)
{
    assert(freq_array && encoding && outfile);
    uint64_t total_num_bits = 0;
    for (int i = 0; i < Array_length(encoding); i++)
    {
        total_num_bits += 
                ((Encoded_value *)Array_get(encoding, i))->bit_length * freq_array[i];
    }
    fwrite(&total_num_bits, sizeof(uint64_t), 1, outfile);
}

/*
 * Function:        read_total_num_bits
 * Description:     Read the total number of bits compressed from the top of the
 *                  compressed file.
 * 
 * Parameters:      FILE *infile: pointer to file
 * Return:          void
 */
uint64_t read_total_num_bits(FILE *infile)
{
    assert(infile);
    uint64_t total_num_bits = 0;
    fread(&total_num_bits, sizeof(uint64_t), 1, infile);
    return total_num_bits;
}

/*
 * Function:        write_header
 * Description:     Write header to compressed file in the following
 *                  format. This allows decompressor to rebuild Huffman tree
 * 
 *                  <TOTAL_NUM_BITS><TOTAL_UNIQUE_CHAR>[char_1][freq_char_1]...
 * 
 * Parameters:      FILE *infile: pointer to file
 *                  Array_T of each character frequencies from provided file
 * Return:          void
 */
void write_header(Array_T freq_array, FILE *outfile)
{
    assert(outfile && freq_array);
    // Header format:
    // <TOTAL_UNIQUE_CHAR>[char_1][freq_char_1]...

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
        free(node);
    }
    return entries;
}

/*
 * Function:        write_body
 * Description:     Write body to compressed file
 * Parameters:      Array_T encoding: table contains character encodings
 *                  FILE *infile: pointer to the input file
 *                  FILE *outfile: pointer to the output file
 * Return:          void
 */
void write_body(Array_T encoding, FILE *infile, FILE *outfile)
{
    assert(infile && outfile && encoding);
    uint64_t word = 0;
    unsigned int current_lsb = 64;

    int c = 0;
    Encoded_value *curr = NULL;

    while (1)
    {
        while ((c = fgetc(infile)) != EOF)
        {
            curr = (Encoded_value *)Array_get(encoding, c);

            if (current_lsb < curr->bit_length)
                break;

            current_lsb -= curr->bit_length;
            word = Bitpack_newu(word, curr->bit_length, current_lsb, curr->bit_value);
        }

        if (c == EOF)
        {
            fwrite(&word, sizeof(uint64_t), 1, outfile);
            break;
        }
        else if (current_lsb > 0)
        {
            unsigned int back_bits_len = curr->bit_length - current_lsb;

            uint64_t front_bits = curr->bit_value >> back_bits_len;
            uint64_t back_bits = (curr->bit_value << (64 - back_bits_len)) >> (64 - back_bits_len);

            word = Bitpack_newu(word, current_lsb, 0, front_bits);
            fwrite(&word, sizeof(uint64_t), 1, outfile);
            word = 0;
            current_lsb = 64 - back_bits_len;
            word = Bitpack_newu(word, back_bits_len, current_lsb, back_bits);
        }
        else
        {
            fwrite(&word, sizeof(uint64_t), 1, outfile);
            current_lsb = 64 - curr->bit_length;
            word = Bitpack_newu(word, curr->bit_length, current_lsb, curr->bit_value);
        }
    }
    // fwrite(&word, sizeof(uint64_t), 1, outfile);
}

/*
 * Function:        read_body
 * Description:     Read body from compressed file and write to decompressed file
 * Parameters:      Huffman_Tree_T encoding: Huffman tree with character encodings
 *                  uint64_t total_num_bits: total number of encoded bits
 *                  FILE *infile: pointer to the compressed file
 *                  FILE *outfile: pointer to the decompressed file
 * Return:          void
 */
void read_body(Huffman_Tree_T encoding, uint64_t total_num_bits, FILE *infile, FILE *outfile)
{
    (void)outfile;
    assert(infile && outfile && encoding);
    Huffman_node *root = Huffman_tree_get_root(encoding);

    Huffman_node *curr = root;
    (void)curr;

    uint64_t word = 0;

    for (uint64_t i = 0; i < total_num_bits; i++)
    {
        int j = i % 64 + 1;
        if (j == 1)
        {
            fread(&word, sizeof(uint64_t), 1, infile);
            // continue;
        }
        // else
        // {
            uint64_t first_bit = Bitpack_getu(word, 1, 64 - j);
            
            if (first_bit == 0 && curr->left_node)
                curr = curr->left_node;
            else if (first_bit == 1 && curr->right_node)
                curr = curr->right_node;
                
            if (!curr->left_node && !curr->right_node)
            {
                printf("%c", curr->key);
                curr = root;
            }
        // }
    }
    // printf("%c", '\n');
}
