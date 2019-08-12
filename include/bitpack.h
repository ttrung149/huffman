/****************************************************************
*
*   Huffman-compressor - Trung Truong - 2019
*
*   File name: bitpack.h
*
*   Description: Header file for bit packing module that handles
*   data types on a bit-wise level
*
****************************************************************/

#include <stdbool.h>
#include <stdint.h>

#ifndef BITPACK_INCLUDED
#define BITPACK_INCLUDED

// Checks if n fits in width-number of bits
bool Bitpack_fitsu(uint64_t n, unsigned width);

// Extracts bits given width and starting lsb from provided word
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb);

// Packs bits given value, width, and starting lsb to original word
uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, 
                      uint64_t value);

#endif
