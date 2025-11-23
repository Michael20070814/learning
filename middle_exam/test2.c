#include <stdio.h>
int main(void)
{
    int num, R, result;
    int num1[7] = {};
    int i = 0;
    result = 0;
    scanf("%d%d", &num, &R);
    while (num >= R)
    {
        num1[i] = num % R;
        num = num / R;
        i++;
    }
    num1[i] = num;
    for (int n = 0; n <= i; n++)
    {
        result += num1[n];
    }
    printf("%d", result);

    return 0;
}