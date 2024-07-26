# Big Num extension

This repository is an extension routine implementation for [tiny-bignum library](https://github.com/kokke/tiny-bignum-c).

tiny-bignum-c library provides good core structure to practice the custom 
arbitrary precision integer routine with C, however, some utils would be more useful to use the library in practical application.


## Additional routines

1. Even, odd determination routine. Done.
2. Bit count. Done. Maybe more flexible algorithm is possible.
3. Binary Print. Done. Simple.
4. Binary string to big_num. Done.

See `bn_ext.h`, `bn_ext.c` file for the details.

```.c
bool bignum_is_even(struct bn* n);
bool bignum_is_odd(struct bn* n);

unsigned int bignum_bit_count(struct bn* n);

void print_bits(uint32_t num, bool print_newline);
void bignum_print_bits(struct bn * num, bool print_newline);

void bignum_from_bitstring(struct bn * n, char* str, int nbytes); 

```

### Python api

In `bn_to_python.c/.h`, there are two macro convert the bignum object to python and vice verse.
Since, Python already provides arbitrary integer routine, but the bighum would be great for 
static integer calculation for speed accelration.

## Example


```
#include "bn_ext.h"

int main(void){
    char * bin_st_s = "01111110111000110001111111111111111111111111000000000000001111111111111111111111111000000111111111011111110001111111111111111111";
    struct bn num_bin;
    bignum_from_bitstring(&num_bin, bin_st, (strlen(bin_st)>>3));
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

## Further Plan

1. Print routine directly print the string to the terminal -> We can change the routine to choose a buffer to print it.
2. Octa string to big_num routine
3. bit manipulation function: replace specific index, read specific parts of the bit string.
4. string matching routine. It is already implemented in python api.


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
to implement arbitrary precision integer arithmetic.
