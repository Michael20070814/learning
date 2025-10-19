#include <stdio.h>
int power(int m, int n);
int main(void)
{
    int number[8], index;
    for (index = 0; index <= 7; index++)
    {
        number[index] = power(2, index+1);
    }
    index = 0;
    do 
    {
        printf("%d\n", number[index]);
        index++;
    }while (index <= 7);
    return 0;
}
int power(int m, int n)
{
    int result, i;
    result = 1;
    for (i = 1; i <= n; i++)
        result *= m;
    return result;
}