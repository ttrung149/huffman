/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: seq.h
*
*   Description: Header file for David R. Hanson's implementation 
*   of a dynamic array in C. 
*   
*   All rights reserved to David R. Hanson. 
*
*   For more information, see Hanson's source code on Github at:
*
*       https://github.com/drh/cii/blob/master/include/array.h
*
****************************************************************/

/* $Id$ */
#ifndef ARRAY_INCLUDED
#define ARRAY_INCLUDED
#define T Array_T
typedef struct T *T;
extern T    Array_new (int length, int size);
extern void Array_free(T *array);
extern int Array_length(T array);
extern int Array_size  (T array);
extern void *Array_get(T array, int i);
extern void *Array_put(T array, int i, void *elem);
extern void Array_resize(T array, int length);
extern T    Array_copy  (T array, int length);
#undef T
#endif
