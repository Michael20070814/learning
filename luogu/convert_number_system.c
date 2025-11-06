#include <stdio.h>
int main(void)
{
    int num, R;
    int num1[1000] = {};
    int n = 0;
    int i = 0;
    char result[1000] = {};
    scanf("%d%d", &num, &R);
    while (num >= R)
    {
        num1[i] = num % R;
        num = num / R;
        i++;
    }
    num1[i] = num;
    for (int count = i, n = 0; count >= 0; count--, n++)
    {
        if (num1[count] > 9)
            result[n] = 'A' + num1[count] - 10;
        else
            result[n] = '0' + num1[count];
    }
    for (int count = 0; count <= i; count++)
        printf("%c", result[count]);
    return 0;
}//可以使用查表法进行优化