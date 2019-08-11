/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: test_priority_queue.c
*
*   Description: Test driver for implementation of a priority queue,
*   which will be used to create the Huffman Coding Tree
*
*
****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../hanson/include/except.h"
#include "../include/priority_queue.h"

/* structure of Node in Priority Queue entries*/
struct Node {
    void *obj;          // void pointer to the object the node contains   
    int value;          // value of priority queue indexing
};

typedef struct Node Node;

int main() {
    const int TEST_SAMPLES = 100000;

    /* TEST MAX HEAP */
    printf("%s %d %s\n", "TESTING MAX-HEAP with", TEST_SAMPLES, "test samples");
    
    // Init space for array and priority queue 
    Priority_Queue_T max_q = Priority_queue_new(1);
    Array_T array = Array_new(TEST_SAMPLES, sizeof(Node));

    // Test max heap functionality by inserting in elements in ascending order
    printf("%s", "   - Initializing max heap: ");
    for (int i = 0; i < TEST_SAMPLES; i++) {
        Node *ptr = malloc(sizeof(Node)); // Allocatate space for node
        ptr->value = i;
        ptr->obj = NULL;
        Array_put(array, i, ptr);         // Add to array;
        free(ptr);
    }
    printf("%s\n", "Passed");

    // Build queue
    Priority_queue_build(max_q, array);

    // Compare top and pop nodes with index in descending order
    printf("%s", "   - Testing top, pop, and get size function: ");
    for (int i = TEST_SAMPLES - 1; i >= 0; i--) {
        Node *top = (Node *)Priority_queue_top(max_q);
        int size = Priority_queue_size(max_q);
        assert(top->value == i);
        assert(size == i + 1);
    
        Node *pop = (Node *)Priority_queue_pop(max_q);
        assert(pop->value == i);
    }
    printf("%s\n", "Passed");
   
    // Insertion test
    printf("%s", "   - Insertion test: ");
    for (int i = 0; i < TEST_SAMPLES; i++) {
        Node *ptr = malloc(sizeof(Node)); // Allocatate space for node
        ptr->value = i;
        ptr->obj = NULL;
        Priority_queue_insert(max_q, ptr, i);
    }

    for (int i = TEST_SAMPLES - 1; i >= 0; i--) {
        Node *top = (Node *)Priority_queue_top(max_q);
        int size = Priority_queue_size(max_q);
        assert(top->value == i);
        assert(((Node *)top->obj)->value == i);
        assert(size == i + 1);
    
        Node *pop = (Node *)Priority_queue_pop(max_q);
        free((Node*) pop->obj);
        assert(pop->value == i);
    }
    printf("%s\n", "Passed");

    TRY
        Priority_queue_pop(max_q);
    ELSE
        printf("%s \n", "   - Test for HEAP UNDERFLOW exception raised: Passed");
    END_TRY;

    printf("%s", "   - Deallocate queue and array: ");
    Array_free(&array);
    Priority_queue_free(&max_q);
    printf("%s\n", "Passed");
    printf("%s \n", "   - Done! All tests passed");

    printf("\n");

    /* TEST MIN HEAP */
    printf("%s %d %s\n", "TESTING MIN-HEAP with", TEST_SAMPLES, "test samples");
    
    // Init space for array and priority queue 
    Priority_Queue_T min_q = Priority_queue_new(0);
    Array_T test_array = Array_new(TEST_SAMPLES, sizeof(Node));

    // Test min heap functionality by inserting in elements in descending order
    printf("%s", "   - Initializing min heap: ");
    for (int i = TEST_SAMPLES - 1; i >= 0; i--) {
        Node *ptr = malloc(sizeof(Node)); // Allocatate space for node
        ptr->value = i;
        ptr->obj = NULL;
        Array_put(test_array, i, ptr);         // Add to array;
        free(ptr);
    }
    printf("%s\n", "Passed");

    // Build queue
    Priority_queue_build(min_q, test_array);

    // Compare top and pop nodes with index in ascending order
    printf("%s", "   - Testing top, pop, and get size function: ");
    for (int i = 0; i < TEST_SAMPLES; i++) {
        Node *top = (Node *)Priority_queue_top(min_q);
        int size = Priority_queue_size(min_q);
        assert(top->value == i);
        assert(size == TEST_SAMPLES - i);
    
        Node *pop = (Node *)Priority_queue_pop(min_q);
        assert(pop->value == i);
    }
    printf("%s\n", "Passed");

    // Insertion test
    printf("%s", "   - Insertion test: ");
    for (int i = TEST_SAMPLES - 1; i >= 0; i--) {
        Node *ptr = malloc(sizeof(Node)); // Allocatate space for node
        ptr->value = i;
        ptr->obj = NULL;
        Priority_queue_insert(min_q, ptr, i);
    }

    for (int i = 0; i < TEST_SAMPLES; i++)  {
        Node *top = (Node *)Priority_queue_top(min_q);
        int size = Priority_queue_size(min_q);
        assert(top->value == i);
        assert(((Node *)top->obj)->value == i);
        assert(size == TEST_SAMPLES - i);
    
        Node *pop = (Node *)Priority_queue_pop(min_q);
        free((Node*) pop->obj);
        assert(pop->value == i);
    }
    printf("%s\n", "Passed");
   
    TRY
        Priority_queue_pop(min_q);
    ELSE
        printf("%s \n", "   - Test for HEAP UNDERFLOW exception raised: Passed");
    END_TRY;

    printf("%s", "   - Deallocate queue and array: ");
    Array_free(&test_array);
    Priority_queue_free(&min_q);
    printf("%s\n", "Passed");
    printf("%s \n", "   - Done! All tests passed");

    return 0;
}
