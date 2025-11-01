#include <stdio.h>
int main(void)
{
    const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31};//不表明数组元素个数，初始化时让程序自动匹配

    for (int index = 0; index < sizeof days / sizeof days[0]; index++)//用sizeof给出运算对象的大小，再除以一个的，得出元素个数
        printf("Month %2d has %d days.\n", index + 1, days[index]);
    
    return 0;
}