#include "bn.h"
#include "bn_ext.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>


/*
String to big_num strcuture:
hexadecimal : implemented.
octadecimal : not implemented but same with hex.
binary: diff structure.
*/

//#define BIT_WORD_SIZE 8*WORD_SIZE
//#define BIT_SIZE_DTYPE 8*sizeof(DTYPE)
//
//void bignum_from_bitstring(struct bn * n, char* str, int nbytes){
//    // nbytes represent the binary string data size, but 
//    // we need to check the  original routine.
//    
//    require(n, "n is null");
//    require(str, "str is null");
//    require(nbytes > 0, "nbytes must be positive");
//    require((nbytes & 1) == 0, "string format must be in hex -> equal number of bytes");
//    
//    int str_len = 8*nbytes ;//Must be same with strlen(str);
//
//    if (str_len > BIT_SIZE_DTYPE){
//        require((nbytes % (sizeof(DTYPE))) == 0, "Bit string length must be a multiple of (sizeof(DTYPE)) characters");
//    }
//
//    bignum_init(n);
//
//    DTYPE tmp; // uint64 = 2 * WORD_SIZE
//    // The binary length is less than reference dtype:
//    if (str_len <=BIT_SIZE_DTYPE){
//        //printf("Single uint_32\n");
//        tmp  = 0 ;
//        tmp = (DTYPE)strtoul(&str[0], NULL, 2); 
//        n->array[0] = tmp;
//    }
//    else{
//        int i = str_len  - (BIT_WORD_SIZE); 
//        int j = 0;
//        char tmp_str[BIT_WORD_SIZE+1];
//
//        while (i >=0){
//            strncpy(tmp_str, &str[i], 32);
//            tmp_str[32] = '\0';
//            tmp = 0;
//            tmp = (DTYPE)strtoul(&tmp_str[0] , NULL, 2); 
//            
//            //printf("%s \t %u \n", tmp_str, tmp); 
//
//            n->array[j] = tmp;
//            i -= BIT_WORD_SIZE;
//            j += 1;
//        }
//    }
//
//    // Memo: 1byte = 8bit
//    // 32bit, int = 4bytes = 32bit
//    // Get word length = WORD_SIZE(hex) - > BINARY calculation
//    // READ BINARY of length = WORD SIZE
//    // convert them to uint8(32bit)
//    // using strtol, 2 convert the string to unint8
//    // assign n->array[] = integer
//
//
//}

int main(void){
    printf("Bit string example: \n");
    printf("1100101011110000\n");
    char * str = "1100101011110000";
    int value = strtol(str, NULL, 2);
    printf("%d \n", value);

    printf("Bignum test MACRO----------\n");

    char * hex_st= "1a3f13";
    printf("Example number: %s:, %ld\n", hex_st, strtol(&hex_st[0], NULL, 16));
    DTYPE tmp = 0;
    sscanf(&hex_st[0], SSCANF_FORMAT_STR, &tmp);
    printf("%d \n", tmp); // 1a3f13 -> 1720083
    sscanf(&hex_st[1], SSCANF_FORMAT_STR, &tmp);
    printf("%d \n", tmp); // a3f13 -> 671507
    sscanf(&hex_st[2], SSCANF_FORMAT_STR, &tmp);
    printf("%d \n", tmp); // 3f13 -> 16147


    printf("------------------------------\n");
    char * hex_st2= "FFFFF"; //"ffffffffffffffffff";
    uint32_t max = UINT32_MAX;
    printf("%u\n", max);
    printf("Example number: %s:, Length: %lu, %ld\n", hex_st2, strlen(hex_st2), strtol(&hex_st[0], NULL, 16));
    tmp = 0;

    sscanf(&hex_st2[0], SSCANF_FORMAT_STR, &tmp);
    printf("%u \n", tmp); // 3f13 -> 16147

    sscanf(&hex_st2[1], SSCANF_FORMAT_STR, &tmp);
    printf("%u \n", tmp); // 3f13 -> 16147

    printf("Binary Test-------------------------\n");
    char * bin_st= "0000000000000000000000010101011111111111111111111111111111111111"; // 9
    
    char * bin_st2 = "101010111";
    printf("Example number: 101010111, 11111111111111111111111111111111\n");
    tmp =0;
    tmp = strtoul(&bin_st[32], NULL, 2);
    printf("%u \n", tmp); 
    tmp = strtoul(&bin_st[0], NULL, 2);
    printf("%u \n", tmp); 
    //sscanf(&bin_st[10], SSCANF_FORMAT_STR_BIN, &tmp);
    //printf("%u \n", tmp); 
    //sscanf(&bin_st[0], SSCANF_FORMAT_STR_BIN, &tmp);
    //printf("%u \n", tmp); 

    printf("Byte word size: %d\n", WORD_SIZE);
    printf("Bit word size: %d\n", 8*WORD_SIZE);

    //struct bn num_bin;
    //struct bn num_bin2;
    //bignum_from_bitstring(&num_bin, bin_st, (strlen(bin_st)>>3));
    //bignum_print_bits(&num_bin, 1);

    char * bin_st_s = "0111111011100011000111111111111111111111111100000000000000111111111111111111111111100000011111111101111111000111111111111111111";
    struct bn num_bin;
    bignum_from_bitstring(&num_bin, bin_st, (strlen(bin_st)>>3));
    bignum_print_binary(&num_bin, 1);

    int bits = bignum_bit_count(&num_bin);

    print("Total 1s: %d\n", bits);
}

//ffffffffffffffffffc= 17
//fffffff : 7


