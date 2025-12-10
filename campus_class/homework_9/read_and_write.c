#include <stdio.h>
#include <string.h>
int main(void)
{
    FILE *fp1 = fopen("fcopy.in", "r+");
    FILE *fp2 = fopen("fcopy.out", "w");

    char ch;
    while ((ch = getc(fp1)) != EOF)
    {    
        if (isspace(ch))
        {    
            while (isspace(ch = getc(fp1)))
                continue;
            putc(' ', fp2);
        }
        putc(ch, fp2);
    }
}