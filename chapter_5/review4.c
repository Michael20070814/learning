#include <stdio.h>
int main(void)
{
    int i = 1;
    float n;
    printf("Watch out! Here come a bunch of fractions!\n");
    while (i++ < 30)
    {
        n = (float) 1 / i;
        printf(" %f", n);

    }
    printf("That's all, folks.\n");
    return 0;
}