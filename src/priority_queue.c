/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: priority_queue.c
*
*   Description: Implementation of a priority queue in C,
*   which will be used to create the Huffman Coding Tree
*
*   See comments on top of each function to understand the interface
*   of implemented data structure
*
****************************************************************/

#include <assert.h>
#include <stdlib.h>
#include "../hanson/include/array.h"
#include "../hanson/include/arrayrep.h"
#include "../include/priority_queue.h"

#define T Priority_Queue_T

/* Macros to find left child, right child, parent index */
#define left_child(x) 2 * x + 1
#define right_child(x) 2 * x + 2
#define parent(x) (x - 1) / 2

/* structure of Priority Queue*/
struct T {
    unsigned int size;
    int type;           // min-heap or max heap
    Array_T entries;    // array of node entries
};

/* structure of Node in Priority Queue entries*/
struct Node {
    void *obj;          // void pointer to the object the node contains   
    unsigned int value; // value of priority queue indexing
};

typedef struct Node Node;

// static Node *create_node_from_obj(void *obj, unsigned int value) {
//     assert(obj);
//     Node *new_node = malloc(sizeof(Node));
//     assert(new_node);
//     new_node->obj = obj;
//     new_node->value = value;
//     return new_node;
// }

/*
 * Function:        Priority_queue_new
 * Description:     Allocates heap data structures for usage
 * Parameters:      int type: specifies whether priority queue
 *                  is a min-heap or max-heap. 
 *                  *   0 for min-heap
 *                  *   1 for max-heap
 *                  *   others, raises C.R.E
 *                  
 *                  unsigned int size: estimated size for the
 *                  number of nodes in the queue
 * 
 * Return:          Pointer to created priority queue 
 */
T Priority_queue_new(int type, unsigned int size) {
    assert(type == 0 || type == 1);
    
    T priority_queue = malloc(sizeof(*priority_queue));
    assert(priority_queue != NULL);

    Array_T entries = Array_new(size, sizeof(Node));
    assert(entries != NULL);

    priority_queue->type = type;
    priority_queue->size = size;
    priority_queue->entries = entries;

    return priority_queue;
}

/*
 * Function:        Priority_queue_free
 * Description:     Deallocates heap data structure after done using
 * Parameters:      T *priority_queue: double pointer to
 *                  struct `Priority_Queue_T`
 * Return:          void     
 */
void Priority_queue_free(T *priority_queue) {
    assert(priority_queue && *priority_queue);
    Array_free(&((*priority_queue)->entries));
    free(*priority_queue);
}

/*
 * Function:        Priority_queue_size
 * Description:     Gets length of priority queue
 * Parameters:      T *priority_queue: pointer to struct `Priority_Queue_T`
 * Return:          unsigned int
 */
unsigned int Priority_queue_size(T priority_queue) {
    assert(priority_queue);
    return priority_queue->size;
}

/*
 * Function:        Priority_queue_build
 * Description:     Build heap given queue and entries array
 * Parameters:      T priority_queue: pointer to struct `Priority_Queue_T`
 * Return:          void     
 */
void Priority_queue_build(T priority_queue, Array_T entries) {
    (void) priority_queue;
    (void) entries;
}

/*
 * Function:        Priority_queue_insert
 * Description:     Inserts object to heap data structure
 * Parameters:      *   T priority_queue: pointer to struct `Priority_Queue_T`
 *                  *   void pointer: Object inserted
 *                  *   int value: value associated to the object for heapifying
 *                  
 * Return:          void
 */
void Priority_queue_insert(T priority_queue, const void *item, unsigned int value) {
    (void) priority_queue;
    (void) item;
    (void) value;
}

/*
 * Function:        Priority_queue_top
 * Description:     Gets max/min node depending on type of heap
 * Parameters:      *   T priority_queue: pointer to struct `Priority_Queue_T`            
 *                  
 * Return:          void pointer: max/min node in the queue
 */
void *Priority_queue_top(T priority_queue) {
    (void) priority_queue;
    return NULL;
}

/*
 * Function:        Priority_queue_pop
 * Description:     Pops the node with maximum or minimum value depending on
 *                  type of heap
 * Parameters:      *   T priority_queue: pointer to struct `Priority_Queue_T`            
 *                  
 * Return:          void pointer: max/min node in the queue
 */
void *Priority_queue_pop(T priority_queue) {
    (void) priority_queue;
    return NULL;
}


// extern void Priority_queue_map(T priority_queue,
//                       void apply(const void *key, void **value, void *cl),
//                       void *cl);
