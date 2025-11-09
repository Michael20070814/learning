#include <stdio.h>
void * input(char *ct)
{
    int i = 0;
    while ((ct[i] = getchar()) != EOF)
    {
        i++;
    }
    ct[i - 1] = '\0';
}
int main(void)
{
    char ar[40];
    input(ar);
    puts(ar);
    return 0;
}