#ifndef __BIGNUM_EXT_H__
#define __BIGNUM_EXT_H__

//#include <Python.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#include "bn.h"

#define ERROR_NOT_IMPLEMENTED revert("Not implemented.")
#define ERROR_NOT_IMPLEMENTED_STR(s) revert(s)

//=======================================================================

/* (*) Additional Utils*/
bool bignum_is_even(struct bn* n);
bool bignum_is_odd(struct bn* n);

// Bit count routine===================
unsigned int bignum_bit_count(struct bn* n);
static const int BITS_TABLE_uint32 [256] = {
    0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};
int _fast_bit_count32 (unsigned int n);
/*
If you modified `WORD_SIZE`,
you have to recalculate the `BITS_TABLE_uint32` data.
In addition, you also modify the inner code of _fast_bit_count() function.
This is a look-up table.

void initialize_lookup_table() {
    for (int i = 0; i < 256; i++) {
        BITS_TABLE_uint[i] = (i & 1) + BITS_TABLE_uinti / 2];
    }
}
int _fast_bit_count(BIN_ARRAY_SIZE) (unsigned int n);
*/


#define BIT_WORD_SIZE 8*WORD_SIZE
#define BIT_SIZE_DTYPE 8*sizeof(DTYPE)

void bignum_from_bitstring(struct bn * n, char* str, int nbytes); 
void bignum_from_octstring(struct bn * n, char* str, int nbytes); // Not implemented yet.
void bignum_from_decistring(struct bn * n, char* str, int nbytes); // Not implemented yet.

/*Utils*/
void print_bits(uint32_t num, bool print_newline);
void bignum_print_bits(struct bn * num, bool print_newline);

#endif 