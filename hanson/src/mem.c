/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: mem.c
*
*   Description: David R. Hanson's implementation of a memory
*   allocation module in C. All rights reserved to David R. Hanson. 
*
*   For more information, see Hanson's source code on Github at:
*
*       https://github.com/drh/cii/blob/master/src/mem.c
*
****************************************************************/

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "../include/except.h"
#include "../include/mem.h"

const Except_T Mem_Failed = {"Allocation failed"};
void *Mem_alloc(long nbytes, const char *file, int line)
{
    void *ptr;
    assert(nbytes > 0);
    ptr = malloc(nbytes);
    if (ptr == NULL)
    {
        if (file == NULL)
            RAISE(Mem_Failed);
        else
            Except_raise(&Mem_Failed, file, line);
    }
    return ptr;
}
void *Mem_calloc(long count, long nbytes,
                 const char *file, int line)
{
    void *ptr;
    assert(count > 0);
    assert(nbytes > 0);
    ptr = calloc(count, nbytes);
    if (ptr == NULL)
    {
        if (file == NULL)
            RAISE(Mem_Failed);
        else
            Except_raise(&Mem_Failed, file, line);
    }
    return ptr;
}
void Mem_free(void *ptr, const char *file, int line)
{
    (void)file;
    (void)line;
    if (ptr)
        free(ptr);
}
void *Mem_resize(void *ptr, long nbytes,
                 const char *file, int line)
{
    assert(ptr);
    assert(nbytes > 0);
    ptr = realloc(ptr, nbytes);
    if (ptr == NULL)
    {
        if (file == NULL)
            RAISE(Mem_Failed);
        else
            Except_raise(&Mem_Failed, file, line);
    }
    return ptr;
}
