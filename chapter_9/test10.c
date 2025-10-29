#include <stdio.h>
void to_base_n(int base, int n);
int main()
{
    long base; 
    int n;
    printf("Please enter the base and the n: ");
    scanf("%d%d", &base, &n);
    to_base_n(base, n);
}
void to_base_n(int base, int n)
{
    int r = 0;
    r = base % n;
    if (base >= n)
        to_base_n(base/n, n);
    printf("%d", r);
    return;
}