#include "../../bn.h"
#include "../../bn_ext.h"
#include <string.h>



int main(void){
    char * hex_test1 = "80000038";
    char * hex_test2 = "0000008000003e8";
    char * hex_test3 = "8000003e81";
    char * hex_test4 = "8000003e8a4";
    char * hex_test5 = "80000038000003";
    char * hex_test6 = "80000038000003a";
    struct bn num;
    char buff[8192];
    int len = (sizeof(DTYPE) * 2);

    bignum_from_string(&num, hex_test1, len);
    bignum_to_string(&num, buff, sizeof(buff));
    printf("Test 1\n");
    printf("Length: %d\n", strlen(hex_test1));
    printf("%s\n", hex_test1);
    printf("%s\n", buff);
    memset(buff, "\0", sizeof(buff));

    bignum_from_string(&num, hex_test2, 2*len);
    bignum_to_string(&num, buff, sizeof(buff));
    printf("Test 2\n");
    printf("Length: %d\n", strlen(hex_test2));
    printf("%s\n", hex_test2);
    printf("%s\n", buff);
    memset(buff, "\0", sizeof(buff));

    bignum_from_string(&num, hex_test3, 2*len);
    bignum_to_string(&num, buff, sizeof(buff));
    printf("Test 3\n");
    printf("Length: %d\n", strlen(hex_test3));
    printf("%s\n", hex_test3);
    printf("%s\n", buff);
    memset(buff, "\0", sizeof(buff));

    bignum_from_string(&num, hex_test4, 2*len);
    bignum_to_string(&num, buff, sizeof(buff));
    printf("Test 4\n");
    printf("Length: %d\n", strlen(hex_test4));
    printf("%s\n", hex_test4);
    printf("%s\n", buff);
    memset(buff, "\0", sizeof(buff));


    bignum_from_string(&num, hex_test5, 2*len);
    bignum_to_string(&num, buff, sizeof(buff));
    printf("Test 5\n");
    printf("Length: %d\n", strlen(hex_test5));
    printf("%s\n", hex_test5);
    printf("%s\n", buff);
    memset(buff, "\0", sizeof(buff));

    bignum_from_string(&num, hex_test6, len);
    bignum_to_string(&num, buff, sizeof(buff));
    printf("Test 6\n");
    printf("Length: %d\n", strlen(hex_test6));
    printf("%s\n", hex_test6);
    printf("%s\n", buff);
    memset(buff, "\0", sizeof(buff));
    return 0;
}