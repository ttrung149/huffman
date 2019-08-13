/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: huffman_tree.h
*
*   Description: Header file for implementation of a Huffman tree
*   which will be used to create the encoding for the compressor
*
*   See comments on top of each function to understand the interface
*   of implemented data structure
*
****************************************************************/

#include "../hanson/include/array.h"

#ifndef HUFFMAN_TREE_INCLUDED
#define HUFFMAN_TREE_INCLUDED
#define T Huffman_Tree_T

#define MAX_NUM_CHAR 256

/* structure of a Huffman Node */
typedef struct Huffman_node Huffman_node;
struct Huffman_node
{
    int frequency;
    char key;
    Huffman_node *left_node;
    Huffman_node *right_node;
};
typedef struct T *T;

/* structure of the encoded value in encoding table */
struct Encoded_value
{
    uint64_t bit_value;
    int bit_length;
};
typedef struct Encoded_value Encoded_value;

/*
 * Function:        Huffman_tree_new
 * Description:     Allocates space for data structure
 * Return:          Pointer to newly created Huffman Tree
 */
extern T Huffman_tree_new();

/*
 * Function:        Huffman_tree_free
 * Description:     Deallocates data structure after done using
 * Parameters:      T huffman_tree: double pointer to
 *                  struct `Huffman_Tree_T`
 * Return:          void
 */
extern void Huffman_tree_free(T *huffman_tree);

/*
 * Function:        Huffman_tree_build
 * Description:     Builds huffman tree given the array of node entries
 * Parameters:      T huffman_tree: pointer to struct `Huffman_Tree_T`
 *                  Array_T entries: All node entries (char and frequency)
 * Return:          void     
 */
extern void Huffman_tree_build(T huffman_tree, Array_T entries);

/*
 * Function:        Huffman_tree_create_encoding_table
 * Description:     Builds a dictionary with fle characters as key and binary
 *                  encoding as value
 * Parameters:      T huffman_tree: pointer to struct `Huffman_Tree_T`
 * Return           Array_T (pointer to struct `Array_T`)
 */
extern Array_T Huffman_tree_create_encoding_table(T huffman_tree);

/*
 * Function:        Huffman_tree_get_root
 * Description:     Returns the root of Huffman Tree
 * Parameters:      T huffman_tree: pointer to struct `Huffman_Tree_T`
 * Return           Pointer to struct `Huffman_node`
 */
extern Huffman_node *Huffman_tree_get_root(T huffman_tree);

#undef T
#endif
