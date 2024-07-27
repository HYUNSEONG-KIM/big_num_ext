#include "../../bn.h"
#include <stdio.h>

int main(void){
    struct bn num;
    bignum_init(&num);
    bignum_from_int(&num, 0);
    char buff[8192];

    bignum_to_string(&num, buff, sizeof(buff));
    printf("%s\n", buff);
}