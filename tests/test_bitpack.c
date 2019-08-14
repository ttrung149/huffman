/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: test_bitpack.c
*
*   Description: Test driver for bitpack module
*
****************************************************************/
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/bitpack.h"

int main() {
    uint64_t test_1 = 0xFFFFFFFFFFFFFFFF;
    printf("Bitpack_get_u: %"PRIu64" \n", Bitpack_getu(test_1, 10, 5));
    test_1 = Bitpack_newu(test_1, 60, 4, 0);
    printf("Bitpack_new_u: %"PRIu64" \n", test_1);

    printf("Bitpack_get_u: %"PRIu64" \n", Bitpack_getu(test_1, 10, 5));

    return 0;
}
