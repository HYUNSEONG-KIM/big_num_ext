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
#include <errno.h>

#include "bn.h"

#define ERROR_NOT_IMPLEMENTED perror("Not implemented.");
#define ERROR_NOT_IMPLEMENTED_STR(s) perror(s);

//=======================================================================

/* (*) Additional Utils*/


// Utils
bool bignum_is_even(struct bn* n);
bool bignum_is_odd(struct bn* n);
int bignum_str_cal_nbytes(char *str, int base); // Not implemented


// Bit routines
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

// Conversion
#define BIT_WORD_SIZE 8*WORD_SIZE
#define BIT_SIZE_DTYPE 8*sizeof(DTYPE)

void bignum_from_bit_string(struct bn * n, char* str,  int nbytes); 
void bignum_from_oct_string(struct bn * n, char* str,  int nbytes); // Not implemented yet.
void bignum_from_dec_string(struct bn * n, char* str, int nbytes); // Not implemented yet.

// In_Output
void print_bits(uint32_t num, bool print_newline);
void bignum_print_bits(struct bn * num, bool print_newline);


// Comparsions

bool bignum_eq(struct bn * a, struct bn *b); // return 1 if both are same.
bool bignum_gt(struct bn * a, struct bn *b); // a>b
bool bignum_lt(struct bn * a, struct bn *b); // a<b
bool bignum_ge(struct bn * a, struct bn *b); // a>=b
bool bignum_le(struct bn * a, struct bn *b); // a<=b


#endif 