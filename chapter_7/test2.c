#include <stdio.h>//读取8个字符即换行
int main(void)
{
    char ch;
    int i = 0;
    while ((ch = getchar()) != '#')
    {
        printf("%c %d ", ch, ch);
        i++;
        if (!(i % 8))
            printf("\n");
    }
    printf("Done!\n");
    return 0;
}