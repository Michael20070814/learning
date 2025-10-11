#include <stdio.h>

int main(void)
{
    const double RENT = 3852.99;/* const表示只读 限定 */

    printf("*%f*\n", RENT);//默认打印后6位小数
    printf("*%e*\n", RENT);
    printf("*%4.2f*\n", RENT);
    printf("*%3.1f*\n", RENT);
    printf("*%10.3f*\n", RENT);/* 点后表示小数位数，点前为字符长度  */
    printf("*%10.3E*\n", RENT);
    printf("*%+4.2f*\n", RENT);/* 数字若为正，则显示正号，反之亦然  */
    printf("*%010.2f*\n", RENT);//0用来填补字符长度剩下来的空格

    return 0;
}