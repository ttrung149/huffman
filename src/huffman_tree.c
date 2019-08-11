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

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../hanson/include/array.h"
#include "../hanson/include/arrayrep.h"
#include "../hanson/include/table.h"
#include "../hanson/include/except.h"
#include "../include/priority_queue.h"
#include "../include/huffman_tree.h"

#define T Huffman_Tree_T

/* structure of a Huffman Node */
typedef struct Huffman_node Huffman_node;
struct Huffman_node
{
    int frequency;
    char key;
    Huffman_node *left_node;
    Huffman_node *right_node;
};

/* structure of Huffman Tree */
struct T
{
    Table_T encoding_table;
    Huffman_node *root;
};

/* structure of Node in Priority Queue entries */
struct Node
{
    void *obj; // void pointer to the object the node contains
    int value; // value of priority queue indexing
};
typedef struct Node Node;

/* Helper function prototypes */
static void Huffman_tree_postorder_free(Huffman_node *root);

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
        Table_free(&((*huffman_tree)->encoding_table));
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
 * Return           Table_T (pointer to struct `Table_T`)
 */
Table_T Huffman_tree_create_encoding_table(T huffman_tree);
