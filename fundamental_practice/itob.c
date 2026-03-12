#include <stdio.h>
#include <stdlib.h>
// 实现进制转换

void input(int *n, int *b); // 输入
char *itob(int n, int b); // 进制转化

int main(void)
{
    int n;int b;
    char *p;

    input(&n, &b);


    if (n > 0)
    {
        p = itob(n, b);
        printf("%s", p);
    }
    else
    {    
        p = itob(-n, b);
        printf("-%s", p);
    }
    

    return 0;
}
void input(int *n, int *b)
{
    scanf("%d%d", n, b);
}
char *itob(int n, int b)
{
    int index = 0;
    char *result = (char *) malloc (sizeof(int) * 100);
    while (n > 0) // 录入字符
    {
        int temp = n % b;
        if (temp > 9)
            result[index++] = temp - 10 + 'a';
        else
            result[index++] = temp + '0';
        n = n / b;
    }

    for (int m = 0; m < index / 2; m++) // 前后颠倒
    {
        char temp = result[m];
        result[m] = result[index - 1 - m];
        result[index - 1 - m] = temp;
    }
    result[index] = '\0';

    return result;
}