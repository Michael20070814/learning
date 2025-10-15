#include <stdio.h>
int main(void)
{
    int n = 39;

    while (n)
        printf("%2d is true\n", n--);
    printf("%2d is false\n", n);

    n = -36;
    while (n)
        printf("%2d is true\n", n++);
    printf("%2d is false\n", n);

    return 0;
}