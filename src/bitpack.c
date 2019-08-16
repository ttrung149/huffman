
#include <assert.h>
#include <stdio.h>
#include "../include/bitpack.h"
#include "../hanson/include/except.h"

Except_T Bitpack_Overflow = { "Overflow packing bits" };

// Checks if n fits in width-number of bits
bool Bitpack_fitsu(uint64_t n, unsigned width)
{
        assert(width <= 64);

        if (width == 0) return false;
        return (n >> width) == 0;
}

// Extracts bits given width and starting lsb from provided word
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb)
{
        if (width == 0) return 0;
        assert((width <= 64) && (width + lsb <= 64));
        uint64_t temp = word;

        temp = temp << (64 - (lsb + width));
        temp = temp >> (64 - width);
        return temp;
}

// Packs bits given value, width, and starting lsb to original word
uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, 
                      uint64_t value)
{
        assert(lsb < 64 && lsb + width <= 64);
        if (!Bitpack_fitsu(value, width)) 
            RAISE(Bitpack_Overflow);

        uint64_t old_val = Bitpack_getu(word, width, lsb);
        word = word ^ (old_val << lsb);
        return word | (value << lsb);
}
