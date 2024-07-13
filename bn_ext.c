#include "bn_ext.h"

#include<string.h>

// Minor utilities 
bool bignum_is_even(struct bn* n){return (n->array[0] & 1) == 0;}
bool bignum_is_odd(struct  bn* n){return !(bignum_is_even(n));}

// See the next references
// https://gurmeet.net/puzzles/fast-bit-counting-routines/
unsigned int bignum_bit_count(struct bn* n){
    unsigned int count = 0;
    int i;
    for(int i = 0; i < BN_ARRAY_SIZE; ++i){
        // block count - > sum
        count += _fast_bit_count32((unsigned int)n->array[i]); 
    }
    return count;
}
int _fast_bit_count32 (unsigned int n) {
    // Only work for 32 bit length
    return bits_in_char[n & 0xffu]
      +  bits_in_char[(n >>  8 ) & 0xffu]
      +  bits_in_char[(n >> 16) & 0xffu]
      +  bits_in_char[(n >> 24) & 0xffu];
}

/*
String to big_num strcuture:
hexadecimal : implemented.
octadecimal : not implemented but same with hex.
binary: diff structure.
*/

#define BIT_WORD_SIZE 8*WORD_SIZE
#define BIT_SIZE_DTYPE 8*sizeof(DTYPE)

void bignum_from_bitstring(struct bn * n, char* str, int nbytes){
    // nbytes represent the binary string data size, 
    // (strlen(bit_str)>>3)
    
    require(n, "n is null");
    require(str, "str is null");
    require(nbytes > 0, "nbytes must be positive");
    require((nbytes & 1) == 0, "string format must be in hex -> equal number of bytes");
    
    int str_len = 8*nbytes ;//Must be same with strlen(str);

    if (str_len > BIT_SIZE_DTYPE){
        require((nbytes % (sizeof(DTYPE))) == 0, "Bit string length must be a multiple of (sizeof(DTYPE)) characters");
    }

    bignum_init(n);

    DTYPE tmp; // uint64 = 2 * WORD_SIZE
    // The binary length is less than reference dtype:
    if (str_len <=BIT_SIZE_DTYPE){
        //printf("Single uint_32\n");
        tmp  = 0 ;
        tmp = (DTYPE)strtoul(&str[0], NULL, 2); 
        n->array[0] = tmp;
    }
    else{
        int i = str_len  - (BIT_WORD_SIZE); 
        int j = 0;
        char tmp_str[BIT_WORD_SIZE+1];

        while (i >=0){
            strncpy(tmp_str, &str[i], 32);
            tmp_str[32] = '\0';
            tmp = 0;
            tmp = (DTYPE)strtoul(&tmp_str[0] , NULL, 2); 
            
            //printf("%s \t %u \n", tmp_str, tmp); 

            n->array[j] = tmp;
            i -= BIT_WORD_SIZE;
            j += 1;
        }
    }

    // Memo: 1byte = 8bit
    // 32bit, int = 4bytes = 32bit
    // Get word length = WORD_SIZE(hex) - > BINARY calculation
    // READ BINARY of length = WORD SIZE
    // convert them to uint8(32bit)
    // using strtol, 2 convert the string to unint8
    // assign n->array[] = integer
}

/*Utils--------------------------------------------------------------------------------*/

void print_bits(uint32_t num, bool print_newline) {
    int bitCount = sizeof(num) * 8; // Number of bits in an integer
    unsigned int mask = 1 << (bitCount - 1); // Create a mask with the leftmost bit set

    // Loop through each bit
    for(int i = 0; i < bitCount; i++) {
        // Print '1' if the current bit is set, otherwise print '0'
        if (num & mask) {
            printf("1");
        } else {
            printf("0");
        }

        // Shift the mask to the right by one bit
        mask >>= 1;

        // Print a space after every 8 bits for readability
        if ((i + 1) % 8 == 0) {
            printf(" ");
        }
    }
    if(print_newline){
        printf("\n");
    }
}
void bignum_print_bits(struct bn * num, bool print_newline){
    int j = 0;
    for(int i=1; i < BN_ARRAY_SIZE+1; i++){
        j = BN_ARRAY_SIZE - i;
        print_bits(num->array[j],0);
        if(print_newline){
        printf("\n");
        }
    }
}

#ifdef __TESTING__
#include <stdio.h>
#include<stdlib.h> // strtol()


int main(void){
    /*
    printf("Main program is running. \n");
    int even_num = 34;
    int odd_num = 1252;

    struct bn even_bn;
    struct bn odd_bn;
    struct bn num;

    bignum_from_int(&num, 100);
    bignum_from_int(&even_bn, even_num);
    bignum_from_int(&odd_bn, odd_num);
    */

    /*
    char buf[8192]; 
    printf("Bignum int, string routine test");
    for(int i =0; i<100 ; i++){
        bignum_from_int(&num, i);
        bignum_to_string(&num, buf, sizeof(buf));
        printf("%d is %s\n", i, buf);
    }
    

    bignum_to_string(&even_bn, buf, sizeof(buf));
    printf("%d is %s\n", even_num, buf);
    bignum_to_string(&odd_bn, buf, sizeof(buf));
    printf("%d is %s\n", odd_num, buf);
    */
   /*
    bool b_e = bignum_is_even(&even_bn);
    bool b_o = bignum_is_even(&odd_bn);
    printf("\n\n");
    printf("Big num even-routine test\n");
    printf("-Even number %d is %s\n", even_num, b_e?"True":"False");
    printf("-Odd number %d is %s\n", odd_num, b_o?"True":"False");
    
    printf("Big num 33\n");
    printBits(odd_bn.array[0], 0);
    printf("\n");
    printf("Big Num binary print\n===========\n");
    bignum_print_binary(&even_bn, 1);
    printf("===============\n");

    printf("Big num 33\n");
    printBits(odd_bn.array[0], 0);
    printf("\n");
    printf("Big Num binary print\n===========\n");
    bignum_print_binary(&even_bn, 1);
    printf("===============\n");

    printf("Bin_count routine\n");
    int count1 = bignum_bit_count(&even_bn);
    int count2 = bignum_bit_count(&odd_bn);

    printf("%d ,%d\n", count1, count2);

    */

    printf("Bit string example: \n");
    printf("1100101011110000\n");
    char * str = "1100101011110000";
    int value = strtol(str, NULL, 2);
    printf("%d \n", value);
    //int nbytes = strlen(str); // nbytes = 16
    //struct bn my_bignum;

    //int tmp =0;
    //sscanf(&str, "%1d")
    //bignum_from_bistring(&my_bignum, str, nbytes);

    //bignum_print_binary(&my_bignum, 1);

}
#endif 