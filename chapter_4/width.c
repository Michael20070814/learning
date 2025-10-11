#include <stdio.h>
#define PAGES 959
int main(void)
{
    printf("*%d*\n", PAGES);
    printf("*%2d*\n", PAGES);/* 数字表示输出字符宽度，不够时自动扩充  */
    printf("*%10d*\n", PAGES);/* 默认在字符串右端 */
    printf("*%-10d*\n", PAGES);/* -号可以把字符打印在左端*/

    return 0;
}