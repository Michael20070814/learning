#include <stdio.h>//检测输入的字符数
int main(void)
{
    char ch;
    int num = 0;

    while ((ch = getchar()) != EOF)
    {
        if (ch != '\n')
        num++;
    }
    printf("%d\n", num);

    return 0;
}