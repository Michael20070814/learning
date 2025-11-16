#include <stdio.h>
int revert(int n);
int main(void)
{
    int num;
    int result;
    scanf("%d", &num);
    if (num > 99 && num < 1000)
        result = revert(num);
    else
        result = -1;
    printf("%d", result);

    return 0;
}
int revert(int n)
{
    int n1, n2, n3;
    n1 = n % 10;
    n2 = n / 10 % 10;
    n3 = n / 100 %10;
    return n1 *100 + n2 * 10 + n3 * 1;
}