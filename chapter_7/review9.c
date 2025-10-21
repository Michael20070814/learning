#include <stdio.h>
int main(void)
{
    char ch;

    while ((ch = getchar()) != '#')
    {
        if (ch != '\n')
        {
            printf("Step1\n");
            if (ch == 'q')
            {
                printf("Step2\n");
                printf("Step3\n");
            }
            if (ch == 'c')
                printf("");
            if (ch == 'h')
                printf("Step3\n");
            if (ch == 'b')
                break;
        }
    }
    printf("Done\n");
    return 0;
}