/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: test_huffman_tree.c
*
*   Description: Test driver for Huffman Tree implementation
*
****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../hanson/include/array.h"
#include "../include/huffman_tree.h"
#include "../include/priority_queue.h"

int main()
{
    Array_T array = Array_new(6, sizeof(Node));
    Node *node_1 = malloc(sizeof(Node));
    Huffman_node *obj_1 = malloc(sizeof(Huffman_node));
    obj_1->frequency = 10;
    obj_1->key = 'a';
    obj_1->left_node = NULL;
    obj_1->right_node = NULL;
    node_1->value = 10;
    node_1->obj = obj_1;

    Node *node_2 = malloc(sizeof(Node));
    Huffman_node *obj_2 = malloc(sizeof(Huffman_node));
    obj_2->frequency = 30;
    obj_2->key = 'b';
    obj_2->left_node = NULL;
    obj_2->right_node = NULL;
    node_2->value = 30;
    node_2->obj = obj_2;

    Node *node_3 = malloc(sizeof(Node));
    Huffman_node *obj_3 = malloc(sizeof(Huffman_node));
    obj_3->frequency = 12;
    obj_3->key = 'c';
    obj_3->left_node = NULL;
    obj_3->right_node = NULL;
    node_3->value = 12;
    node_3->obj = obj_3;

    Node *node_4 = malloc(sizeof(Node));
    Huffman_node *obj_4 = malloc(sizeof(Huffman_node));
    obj_4->frequency = 3;
    obj_4->key = 'd';
    obj_4->left_node = NULL;
    obj_4->right_node = NULL;
    node_4->value = 3;
    node_4->obj = obj_4;

    Node *node_5 = malloc(sizeof(Node));
    Huffman_node *obj_5 = malloc(sizeof(Huffman_node));
    obj_5->frequency = 1;
    obj_5->key = 'e';
    obj_5->left_node = NULL;
    obj_5->right_node = NULL;
    node_5->value = 1;
    node_5->obj = obj_5;

    Node *node_6 = malloc(sizeof(Node));
    Huffman_node *obj_6 = malloc(sizeof(Huffman_node));
    obj_6->frequency = 120;
    obj_6->key = 'f';
    obj_6->left_node = NULL;
    obj_6->right_node = NULL;
    node_6->value = 120;
    node_6->obj = obj_6;

    Array_put(array, 0, node_1);
    Array_put(array, 1, node_2);
    Array_put(array, 2, node_3);
    Array_put(array, 3, node_4);
    Array_put(array, 4, node_5);
    Array_put(array, 5, node_6);

    Huffman_Tree_T a = Huffman_tree_new();
    Huffman_tree_build(a, array);
    Table_T encoding = Huffman_tree_create_encoding_table(a);

    Encoded_value *test_1 = (Encoded_value *)Table_get(encoding, &(obj_1->key));
    printf("Obj 1's value in encoding table: %llu \n", test_1->bit_value);
    Encoded_value *test_2 = (Encoded_value *)Table_get(encoding, &(obj_2->key));
    printf("Obj 2's value in encoding table: %llu \n", test_2->bit_value);
    Encoded_value *test_3 = (Encoded_value *)Table_get(encoding, &(obj_3->key));
    printf("Obj 3's value in encoding table: %llu \n", test_3->bit_value);
    Encoded_value *test_4 = (Encoded_value *)Table_get(encoding, &(obj_4->key));
    printf("Obj 4's value in encoding table: %llu \n", test_4->bit_value);
    Encoded_value *test_5 = (Encoded_value *)Table_get(encoding, &(obj_5->key));
    printf("Obj 5's value in encoding table: %llu \n", test_5->bit_value);
    Encoded_value *test_6 = (Encoded_value *)Table_get(encoding, &(obj_6->key));
    printf("Obj 6's value in encoding table: %llu \n", test_6->bit_value);

    Huffman_node *root = Huffman_tree_get_root(a);
    printf("Root frequency: %d\n", root->frequency);

    Huffman_tree_free(&a);
    Array_free(&array);
    free(node_1);
    free(node_2);
    free(node_3);
    free(node_4);
    free(node_5);
    free(node_6);

    return 0;
}
