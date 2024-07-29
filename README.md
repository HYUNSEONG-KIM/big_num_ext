# Big Num extension

This repository is an extension routine implementation for [tiny-bignum library](https://github.com/kokke/tiny-bignum-c).

tiny-bignum-c library provides good core structure to practice the custom 
arbitrary precision integer routine with C, however, some util would be more useful to use the library in practical application.

In addition, it would be a good toy project to practice bit manipulation.


## Additional routines

1. Even, odd determination routine. Done.
2. Bit count. Done. Maybe, more flexible algorithm is possible.
3. Binary Print. Done. Simplest one.
4. Binary string to big_num. Done.
5. Comparison routines, `eq, gt, lt, ge, le`. Done.

See `bn_ext.h`, `bn_ext.c` file for the details.

Public API

```.c
// Utils
bool bignum_is_even(struct bn* n); // Return 1 if n is even else 0.
bool bignum_is_odd(struct bn* n); // Return 1 if n is odd else 1.

// Bit routines
unsigned int bignum_bit_count(struct bn* n); // Return the number of 1 bits in the n.

// In_Ouput
void print_bits(uint32_t num, bool print_newline); // Print te bit string to terminal, if print_newline=true, it sperate the bits as hex unit.
void bignum_print_bits(struct bn * num, bool print_newline); // print the bignum as binary string.

void bignum_from_bit_string(struct bn * n, char* str,  int nbytes); 
// Comparsions

bool bignum_eq(struct bn * a, struct bn *b); // return 1 if both are same.
bool bignum_gt(struct bn * a, struct bn *b); // a>b
bool bignum_lt(struct bn * a, struct bn *b); // a<b
bool bignum_ge(struct bn * a, struct bn *b); // a>=b
bool bignum_le(struct bn * a, struct bn *b); // a<=b
```

### Python api

In `bn_to_python.c/.h`, there are two functions converting the `bignum` object to python `long` and vice verse.
Since, Python already provides arbitrary integer routine, but the `bignum` would be great for 
static integer calculation for speed acceleration.

## Example

```
#include "bn_ext.h"

int main(void){
    char * bin_st_s = "01111110111000110001111111111111111111111111000000000000001111111111111111111111111000000111111111011111110001111111111111111111";
    struct bn num_bin;
    bignum_from_bit_string(&num_bin, bin_st, (strlen(bin_st)>>3));
    bignum_print_binary(&num_bin, 1);

    int bits = bignum_bit_count(&num_bin);

    print("Total 1s: %d\n", bits);
}
```

Result:
```
00000000 00000000 00000000 00000000
00000000 00000000 00000000 00000000
.
.
.
01111110 11100011 00011111 11111111 
11111111 11110000 00000000 00111111 
11111111 11111111 11100000 01111111 
11011111 11000111 11111111 11111111
Total 1s: 96
```

## Not implemented yet(Further plan)

### In/output

Print routine to file or buffers.

```.{C}
void bignum_from_file(struct bn *n, FIFLE * fp, int byte_len, int base, bool sep); \\ read file and initiate bignum struct.
void bignum_to_file(struct bn *n, FIFLE * fp, int byte_len, int base, bool sep); \\ write the bignum struct to the file as string.
```

### Conversion

```.{C}
void bignum_from_oct_string(struct bn * n, char * str, int byte_len);
void bignum_from_dec_string(struct bn * n, char * str, int byte_len);

void bignum_to_oct_string(struct bn * n, char * str, int byte_len);
void bignum_to_dec_string(struct bn * n, char * str, int byte_len);
// 
void bignum_ext_from_string(struct bn * n, char * str, int base, int byte_len);
```
### Bit routines

### Comparsions

1. Print routine directly print the string to the terminal -> We can change the routine to choose a buffer to print it.
2. Octa string to big_num routine
3. bit manipulation function: Replace specific index, read specific parts of the bit string.
4. String matching routine. It is already implemented in python api.

### Misc utils

```.{C}
int bignum_str_cal_nbytes(char *str, int base);
```

## License

Same with tiny-bignum, **Public domain**.

## Additional Reading

The tiny-bignum simply extended the bitarray in compile time,
however, in real arbitrary precision system requires dynamics memory
treatment.

1. Determine the maximum bytes in compile time: tiny-big-num, simple and soild structure, less flexible.
2. Dynamically allocate and free the data: GMP, flexible and powerful, requiring high huddle to develop.

If you only requires to handle large integer it would be useful but, 
in commercial or research purpose case, it would be wise to see [List of Arbitarary Precision Arithmetic Softwares](https://en.wikipedia.org/wiki/List_of_arbitrary-precision_arithmetic_software).

As a side using a number theory you can treat the larger integer with fixed precision integer datatypes.
In Abstract Algebra by Tomas W Judson, there is a practice using Chinese remainder theorem 
to implement larger precision integer arithmetic.
