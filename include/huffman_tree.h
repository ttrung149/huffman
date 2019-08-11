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
#include "../hanson/include/table.h"

#ifndef HUFFMAN_TREE_INCLUDED
#define HUFFMAN_TREE_INCLUDED
#define T Huffman_Tree_T
typedef struct T *T;

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
 * Return           Table_T (pointer to struct `Table_T`)
 */
extern Table_T Huffman_tree_create_encoding_table(T huffman_tree);

#undef T
#endif
