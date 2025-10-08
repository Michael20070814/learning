#include <stdio.h>
int main(void)
{
    unsigned int un = 3000000000; // int 为32位
    short end = 200;             // short 为16位
    long big = 65537;            // long 为32位
    long long verybig = 12345678908642; // long long 为64位

    printf("un = %u and not %d\n", un, un); // %u用于正数的转换说明
    printf("end = %hd and %d\n", end, end); // %hd用于short类型的转换说明
    printf("big = %ld and not %hd\n", big, big); // %ld用于long类型的转换说明
    printf("verybig = %lld and not %ld\n", verybig, verybig); // %lld用于long long类型的转换说明
    return 0;
}