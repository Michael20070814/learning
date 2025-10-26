#include <stdio.h>
int main(void)
{
    int ch;
    int num = 0;

    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
        {
            printf("\\n---%d ", ch);
            printf("\n");
            num = 0;
        }
        else if (ch == '\t')
            printf("\\t---%d ", ch);
        else if(ch <= 31)
            printf("^%c---%d ", ch+64, ch);
        else
            printf("%c---%d ", ch, ch);
        num++;
        if (num == 10 )
        {
            printf("\n");
            num = 0;
        }
    }
    printf("Done!\n");
    return 0;
}