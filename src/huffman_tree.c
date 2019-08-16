/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: huffman_tree.c
*
*   Description: Implementation of a Huffman tree which will be used
*                to create the encoding for the compressor
*
*   See comments on top of each function to understand the interface
*   of implemented data structure
*
****************************************************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../hanson/include/array.h"
#include "../hanson/include/arrayrep.h"
#include "../hanson/include/except.h"
#include "../include/priority_queue.h"
#include "../include/huffman_tree.h"

#define T Huffman_Tree_T

/* structure of Huffman Tree */
struct T
{
    Array_T encoding_table;
    Huffman_node *root;
};

/* Helper function prototypes */
static void Huffman_tree_postorder_free(Huffman_node *root);
static void add_leaf_to_table(Huffman_node *root, Array_T encoding, 
                                unsigned int length, uint64_t value);

/*
 * Function:        Huffman_tree_new
 * Description:     Allocates space for data structure
 * Return:          Pointer to newly created Huffman Tree
 */
T Huffman_tree_new()
{
    T huffman_tree = malloc(sizeof(*huffman_tree));
    assert(huffman_tree != NULL);

    huffman_tree->encoding_table = NULL;
    huffman_tree->root = NULL;

    return huffman_tree;
}

/*
 * Function:        Huffman_tree_free
 * Description:     Deallocates data structure after done using
 * Parameters:      T huffman_tree: double pointer to
 *                  struct `Huffman_Tree_T`
 * Return:          void
 */
void Huffman_tree_free(T *huffman_tree)
{
    assert(huffman_tree && *huffman_tree);
    Huffman_node *root = (*huffman_tree)->root;
    Huffman_tree_postorder_free(root);

    if ((*huffman_tree)->encoding_table)
    {
        Array_free(&((*huffman_tree)->encoding_table));
    }
    free(*huffman_tree);
}

/**
 * Static helper function to perform Huffman tree deletion
 */
static void Huffman_tree_postorder_free(Huffman_node *root)
{
    if (!root)
        return;
    Huffman_tree_postorder_free(root->left_node);
    Huffman_tree_postorder_free(root->right_node);
    free(root);
}

/*
 * Function:        Huffman_tree_build
 * Description:     Builds huffman tree given the array of node entries
 * Parameters:      T huffman_tree: pointer to struct `Huffman_Tree_T`
 *                  Array_T entries: All node entries (char and frequency)
 * Return:          void     
 */
void Huffman_tree_build(T huffman_tree, Array_T entries)
{
    Priority_Queue_T min_queue = Priority_queue_new(0);
    Priority_queue_build(min_queue, entries);

    while (Priority_queue_size(min_queue) > 1)
    {
        // Extract first min nodes
        Node *first_element = (Node *)Priority_queue_pop(min_queue);
        Node *second_element = (Node *)Priority_queue_pop(min_queue);

        // Create new parent node from 2 extracted min nodes
        Huffman_node *obj = malloc(sizeof(Huffman_node));
        assert(obj);
        obj->left_node = (Huffman_node *)first_element->obj;
        obj->right_node = (Huffman_node *)second_element->obj;

        int new_freq = first_element->value + second_element->value;
        obj->frequency = new_freq;
        obj->key = '-';

        Priority_queue_insert(min_queue, obj, new_freq);
    }
    // Assign extracted root node to root attributes
    // of the Huffman tree
    Node *root = (Node *)Priority_queue_pop(min_queue);
    huffman_tree->root = (Huffman_node *)root->obj;
    Priority_queue_free(&min_queue);
}

/*
 * Function:        Huffman_tree_create_encoding_table
 * Description:     Builds a dictionary with fle characters as key and binary
 *                  encoding as value
 * Parameters:      T huffman_tree: pointer to struct `Huffman_Tree_T`
 * Return           Array_T (pointer to struct `Array_T`)
 */
Array_T Huffman_tree_create_encoding_table(T huffman_tree)
{
    assert(huffman_tree->root);
    
    // Allocate dictionary as an array of capacity 256
    Array_T encoding = Array_new(MAX_NUM_CHAR, sizeof(Encoded_value));

    add_leaf_to_table(huffman_tree->root, encoding, 0, 0);
    if (huffman_tree->encoding_table)
        Array_free(&huffman_tree->encoding_table);
    huffman_tree->encoding_table = encoding;

    return huffman_tree->encoding_table;
}

// Helper function to add leaf node to encoding table
static void add_leaf_to_table(Huffman_node *root, Array_T encoding, 
                                unsigned int length, uint64_t value)
{
    // Base case: leaf node
    if (!(root->left_node) && !(root->right_node))
    {
        Encoded_value *encoded_val = malloc(sizeof(Encoded_value));
        assert(encoded_val);
        encoded_val->bit_value = value;
        encoded_val->bit_length = length;

        // printf("Bit value: %"PRIu64", Bit length: %d\n", value, length);
        Array_put(encoding, (int)(root->key), encoded_val);
        free(encoded_val);
        return;
    }
    // Recursively calculate encoding value til leave node is reached
    add_leaf_to_table(root->left_node, encoding, length + 1, value << 1);
    add_leaf_to_table(root->right_node, encoding, length + 1, (value << 1) + 0x1);
}

/*
 * Function:        Huffman_tree_get_root
 * Description:     Returns the root of Huffman Tree
 * Parameters:      T huffman_tree: pointer to struct `Huffman_Tree_T`
 * Return           Pointer to struct `Huffman_node`
 */
Huffman_node *Huffman_tree_get_root(T huffman_tree)
{
    assert(huffman_tree && huffman_tree->root);
    return huffman_tree->root;
}
