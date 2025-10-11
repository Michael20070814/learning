#include <stdio.h>
#define BLURB "Authentic imitation!"
int main(void)
{
    printf("[%s]\n", BLURB);//s指代字符串
    printf("[%25s]\n", BLURB);//右对齐
    printf("[%-25s]\n", BLURB);//左对齐
    printf("[%.5s]\n", BLURB);//只显示前5个字符
    printf("[%.15s]\n", BLURB);//只显示前15个字符
    printf("[%25.15s]\n", BLURB);//右对齐，显示前15个字符
    printf("[%-25.15s]\n", BLURB);//左对齐，显示前15个字符

    return 0;
}