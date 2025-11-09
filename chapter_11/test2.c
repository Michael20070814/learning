#include <stdio.h>
#include <stdio.h>
void * input(char *ct, int n)
{
    int i = 0;
    while ((ct[i] = getchar()) != '\0' && ct[i] != '\t' && ct[i] != '\n' && i <= n)
    {
        i++;
    }
    ct[i] = '\0';
}
int main(void)
{
    char ar[40];
    input(ar, 10);
    puts(ar);
    return 0;
}