#include <stdio.h>
int main(void)
{
    char ch;

    scanf("%c", &ch);
    while (ch != 'g')
    {
        printf("%c", ch);
        scanf("%c", &ch);//区分大小写，之后的中断输入
    }
    return 0;
}