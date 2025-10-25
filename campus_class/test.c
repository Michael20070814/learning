#include <stdio.h>
int f(int x, int y);
int main(void)
{
    int a, b, c;

    a = 1;
    b = 2;
    c = f(a,b);

    printf("Hello world!\n");
}
int f(int x, int y)
{
    return 2 * (x + y);
}