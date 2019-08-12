/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: priority_queue.h
*
*   Description: Header file for implementation of a priority queue,
*   which will be used to create the Huffman Coding Tree
*
*   See comments on top of each function to understand the interface
*   of implemented data structure
*
****************************************************************/

#include "../hanson/include/array.h"

#ifndef PRIORITY_QUEUE_INCLUDED
#define PRIORITY_QUEUE_INCLUDED
#define T Priority_Queue_T

/* structure of Node in Priority Queue entries */
struct Node
{
    void *obj; // void pointer to the object the node contains
    int value; // value of priority queue indexing
};

typedef struct Node Node;

typedef struct T *T;

/*
 * Function:        Priority_queue_new
 * Description:     Allocates heap data structures for usage
 * Parameters:      int type: specifies whether priority queue
 *                  is a min-heap or max-heap. 
 *                  *   0 for min-heap
 *                  *   1 for max-heap
 *                  *   others, raises C.R.E
 * 
 * Return:          Pointer to newly created priority queue 
 */
extern T Priority_queue_new(int type);

/*
 * Function:        Priority_queue_free
 * Description:     Deallocates heap data structure after done using
 * Parameters:      T *priority_queue: double pointer to
 *                  struct `Priority_Queue_T`
 * Return:          void     
 */
extern void Priority_queue_free(T *priority_queue);

/*
 * Function:        Priority_queue_build
 * Description:     Build heap given queue and entries array
 * Parameters:      T priority_queue: pointer to struct `Priority_Queue_T`
 *                  Array_T entries: All entries in the heap
 * Return:          void     
 */
extern void Priority_queue_build(T priority_queue, Array_T entries);

/*
 * Function:        Priority_queue_size
 * Description:     Gets size of priority queue
 * Parameters:      T priority_queue: pointer to struct `Priority_Queue_T`
 * Return:          int
 */
extern int Priority_queue_size(T priority_queue);

/*
 * Function:        Priority_queue_insert
 * Description:     Inserts object to heap data structure
 * Parameters:      *   T priority_queue: pointer to struct `Priority_Queue_T`
 *                  *   void pointer: Object inserted
 *                  *   int value: value associated to the object for heapifying
 *                  
 * Return:          void
 */
extern void Priority_queue_insert(T priority_queue, void *item, unsigned int value);

/*
 * Function:        Priority_queue_top
 * Description:     Gets max/min node depending on type of heap
 * Parameters:      *   T priority_queue: pointer to struct `Priority_Queue_T`            
 *                  
 * Return:          void pointer: max/min node in the queue
 */
extern void *Priority_queue_top(T priority_queue);

/*
 * Function:        Priority_queue_pop
 * Description:     Pops the node with maximum or minimum value depending on
 *                  type of heap. If priority queue is empty, raise Exception.
 * Parameters:      *   T priority_queue: pointer to struct `Priority_Queue_T`  
 *                  
 * Return:          void pointer: max/min node in the queue
 */
extern void *Priority_queue_pop(T priority_queue);

// extern void Priority_queue_map(T priority_queue,
//                       void apply(const void *key, void **value, void *cl),
//                       void *cl);

#undef T
#endif
