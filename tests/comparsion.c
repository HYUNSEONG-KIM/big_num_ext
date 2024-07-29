#include "../bn.h"
#include "../bn_ext.h"

#include <stdio.h>
#include <stdbool.h>


bool bignum_eq(struct bn * a, struct bn *b); // return 1 if both are same.
bool bignum_gt(struct bn * a, struct bn *b); // a>b
bool bignum_lt(struct bn * a, struct bn *b); // a<b
bool bignum_ge(struct bn * a, struct bn *b); // a>=b
bool bignum_le(struct bn * a, struct bn *b); // a<=b


void test_func(int a, int b, struct bn * bn_a, struct bn * bn_b){
    printf("-----------------------\n");
    printf("a=%d, b=%d\n", a, b);
    bignum_from_int(bn_a, a);
    bignum_from_int(bn_b, b);
    printf("a=b:%s\n", (bignum_eq(bn_a, bn_b))?"True":"False");
    printf("a>b:%s\n", (bignum_gt(bn_a, bn_b))?"True":"False");
    printf("a<b:%s\n", (bignum_lt(bn_a, bn_b))?"True":"False");
    printf("a>=b:%s\n", (bignum_ge(bn_a, bn_b))?"True":"False");
    printf("a<=b:%s\n", (bignum_le(bn_a, bn_b))?"True":"False");
}

void test_func_bignum(struct bn * bn_a, struct bn * bn_b){
    printf("-----------------------\n");
    printf("a=b:%s\n", (bignum_eq(bn_a, bn_b))?"True":"False");
    printf("a>b:%s\n", (bignum_gt(bn_a, bn_b))?"True":"False");
    printf("a<b:%s\n", (bignum_lt(bn_a, bn_b))?"True":"False");
    printf("a>=b:%s\n", (bignum_ge(bn_a, bn_b))?"True":"False");
    printf("a<=b:%s\n", (bignum_le(bn_a, bn_b))?"True":"False");
}

int main(void){
    struct bn bn_a, bn_b, bn_c;
    int a=0, b=0, c=0;
    bignum_init(&bn_a);
    bignum_init(&bn_b);
    bignum_init(&bn_c);

    // integer cases
    a = 0;
    b = 1;
    test_func(0, 0, &bn_a, &bn_b);
    test_func(0, 1, &bn_a, &bn_b);
    test_func(1, 0, &bn_a, &bn_b);
    test_func(1, 1, &bn_a, &bn_b);
    test_func(100, 100, &bn_a, &bn_b);
    
    test_func(134, 172, &bn_a, &bn_b);
    test_func(123, 63444, &bn_a, &bn_b);
    test_func(12308,12164, &bn_a, &bn_b);
    test_func(3725, 6254, &bn_a, &bn_b);
    test_func(112541, 6124, &bn_a, &bn_b);

    // big_num routines bigger than C integer.
    char * a_num = "ABC4FFFFFFFF";
    char * b_num = "ABC3FFFFFFFF";
    bignum_from_string(&bn_a, a_num, 16);
    bignum_from_string(&bn_b, b_num, 16);
    printf("-----------------------\n");
    printf("a=%s, b=%s\n", a_num, b_num);
    test_func_bignum(&bn_a, &bn_b);

    char * c_num = "FFFFF";
    char * d_num = "ABC3FFFFFFFF";
    bignum_from_string(&bn_a, c_num, 8);
    bignum_from_string(&bn_b, d_num, 16);
    printf("-----------------------\n");
    printf("a=%s, b=%s\n", c_num, d_num);
    test_func_bignum(&bn_a, &bn_b);
}


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