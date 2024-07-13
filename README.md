# Big Num extension

This repository is an extension routine implementation for [tiny-bignum library](https://github.com/kokke/tiny-bignum-c).

The library provides good core structure to practice the custom 
arbitrary precision integer routine with C.
However, some utils would be more useful in practical application.
The 

## Additional routines

1. Even, odd determination routine. Done.
2. Bit count. Done. Maybe more flexible algorithm is possible.
3. Binary Print. Done. Simple.
4. Binary string to big_num. Done.

See `bn_ext.h`, `bn_ext.c` file for the detials.

```.c
bool bignum_is_even(struct bn* n);
bool bignum_is_odd(struct bn* n);

unsigned int bignum_bit_count(struct bn* n);

void print_bits(uint32_t num, bool print_newline);
void bignum_print_bits(struct bn * num, bool print_newline);

void bignum_from_bitstring(struct bn * n, char* str, int nbytes); 

```

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
## License

Same with tiny-bignum, **Public domain**.

## Additional Reading

The tiny-bignum simply extended the bitarray in compile time,
however, in real arbitrary precision system requires dynamics memory
treatment.

See GMP library, and 

In Abstract Algebra by Tomas W Judson, 
there is a practice using Chinese remainder theorem 
to implement arbitrary precision integer arithmetic.