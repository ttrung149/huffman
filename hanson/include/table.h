/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: table.h
*
*   Description: Header file for David R. Hanson's implementation 
*   of a dictionary in C. All rights reserved to David R. Hanson. 
*
*   For more information, see Hanson's source code on Github at:
*
*       https://github.com/drh/cii/blob/master/include/table.h
*
****************************************************************/

/* $Id$ */
#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED
#define T Table_T
typedef struct T *T;
extern T Table_new(int hint,
                   int cmp(const void *x, const void *y),
                   unsigned hash(const void *key));
extern void Table_free(T *table);
extern int Table_length(T table);
extern void *Table_put(T table, const void *key,
                       void *value);
extern void *Table_get(T table, const void *key);
extern void *Table_remove(T table, const void *key);
extern void Table_map(T table,
                      void apply(const void *key, void **value, void *cl),
                      void *cl);
extern void **Table_toArray(T table, void *end);
#undef T
#endif
