#include "bn_ext.h"

// Minor utilities 
bool bignum_is_even(struct bn* n){return (n->array[0] & 1) == 0;}
bool bignum_is_odd(struct  bn* n){return !(bignum_is_even(n));}

// See the next references
// https://gurmeet.net/puzzles/fast-bit-counting-routines/
unsigned int bignum_bit_count(struct bn* n){
    unsigned int count = 0;
    for(int i = 0; i < BN_ARRAY_SIZE; ++i){
        // block count - > sum
        count += _fast_bit_count32((unsigned int)n->array[i]); 
    }
    return count;
}
int _fast_bit_count32 (unsigned int n) {
    // This algorithm only works for 32bit integer,
    // so that, it is well fits with tiny-big-num library.

    /* 
    // Algorithm description:
    // 0xffu(16) = 255(10)  = 11111111(2)
    // n&0xffu part;
    //       n : ...11101110|01101010
    //    0xffu: ...00000000|11111111
    // =n&0xffu: ...00000000|01101010
    // -> After the count, shift the bit to right and iteratively sum.
    */

    return BITS_TABLE_uint32[n & 0xffu]
          +BITS_TABLE_uint32[(n >>  8) & 0xffu]
          +BITS_TABLE_uint32[(n >> 16) & 0xffu]
          +BITS_TABLE_uint32[(n >> 24) & 0xffu];
}
/* Additional note on bit counting with lookup table.
If the integer data type becomes 64bit, then
(8bit mask) : 8 byte -> 8 terms
with n >> 32, >> 40, >>48, >> 56 

16bit mask: 0xffffu, >>16, >>32, >>48, ...
32bit mask: 0xffffffffu, >>32, >>64, ...
*/

/*
String to big_num strcuture:
Hexadecimal : implemented.
Octadecimal : not implemented but same structure with hex.
Decimal: <- not a 2 power base, the units does not match with permitted bits.
Binary: diff structure.
*/

int bignum_str_cal_nbytes(char *str, int base){
    int str_len = strlen(str);
    int nbytes = 0;
    switch(base)
    {
        case 2: 
            nbytes = str_len >>3;
            break;
        case 8: 
            nbytes = str_len >>2;
            break;
        case 16:
        case 10:
    }
    ERROR_NOT_IMPLEMENTED
    return -1;
}

//int bignum_util_cal_nbytes(char *str, char * tmp_str){
//    // Calculate original string length
//    int nbytes = 0;
//    int str_len = 0;
//    
//    //
//    if (tmp_str != NULL & sizeof(tmp_str)/sizeof(char) >= nbytes){
//        memset(tmp_str, '\0', sizeof(tmp_str));
//    } 
//    
//
//    return nbytes;
//}

void bignum_from_bit_string(struct bn * n, char* str, int nbytes){
    // nbytes represent the binary string data size, 
    // (strlen(bit_str)>>3)
    
    require(n, "n is null");
    require(str, "str is null");
    require(nbytes > 0, "nbytes must be positive");
    //require((nbytes & 1) == 0, "string format must be in hex -> equal number of bytes"); // why is it? (Kim)
    
    int str_len = 8*nbytes; //Must be same with strlen(str);

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
            strncpy(tmp_str, &str[i], BIT_WORD_SIZE);
            tmp_str[BIT_WORD_SIZE] = '\0';
            tmp = 0;
            tmp = (DTYPE)strtoul(&tmp_str[0] , NULL, 2); 
            
            //printf("%s \t %u \n", tmp_str, tmp); 

            n->array[j] = tmp;
            i -= BIT_WORD_SIZE;
            j += 1;
        }
    }
    
    // initial memo
    // Memo: 1byte = 8bit
    // 32bit, int = 4bytes = 32bit
    // Get word length = WORD_SIZE(hex) - > BINARY calculation
    // READ BINARY of length = WORD SIZE
    // convert them to uint8(32bit)
    // using strtol, 2 convert the string to unint8
    // assign n->array[] = integer
}
void bignum_from_oct_string(struct bn * n, char* str, int nbytes){
    ERROR_NOT_IMPLEMENTED_STR("Oct string routine is in developing.");
}
void bignum_from_dec_string(struct bn * n, char* str, int nbytes){
    ERROR_NOT_IMPLEMENTED_STR("Deci string routine is in developing.");
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

// Comparsions==========================================

int _bignum_get_comp_index(struct bn * a, struct bn *b){
    int i;
    for (i=BN_ARRAY_SIZE-1; i>0; --i)
    {
        if((bool)(a->array[i]) || (bool)(b->array[i]))
        {
            return i;
        }
    }
    return 0;
}

bool bignum_eq(struct bn * a, struct bn *b)
{
    int i;
    for (i=0; i< BN_ARRAY_SIZE; ++i)
    {
        if(a->array[i] != b->array[i])
        {
            return false;
        }
    }
    return true;
} 
bool bignum_gt(struct bn * a, struct bn *b)
{
    int i = _bignum_get_comp_index(a, b);
    return a->array[i] > b->array[i];

}
bool bignum_lt(struct bn * a, struct bn *b)
{
    int i = _bignum_get_comp_index(a, b);
    return a->array[i] < b->array[i];

}
bool bignum_ge(struct bn * a, struct bn *b)
{
    if(bignum_gt(a, b)){return true;}
    if(bignum_eq(a, b)){return true;}
    return false;

}
bool bignum_le(struct bn * a, struct bn *b)
{
    if(bignum_lt(a, b)){return true;}
    if(bignum_eq(a, b)){return true;}
    return false;
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