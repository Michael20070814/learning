#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LEN 81

char *input(void);
char *multi(char *num1, char *num2);
void reverse(char *num);
void print(char *result, int len);

int main(void)
{
    char *num1 = input();
    char *num2 = input();

    char *result = multi(num1, num2);
    char *p = result;

    while (*p == '\0')
        p++;

    print(p, (2 * LEN - 1 + result - p));

    free(result);

    return 0;
}

char *input(void)
{
    char *result = (char *) malloc(sizeof(char) * LEN);
    int num = 0; char ch;
    
    while ((ch = getchar()) != '\n')
        result[num++] = ch;
    
    result[num] = '\0';

    return result;
}

char *multi(char *num1, char *num2)
{
    reverse(num2); reverse(num1);
    char *result = (char *)calloc(2 * LEN, sizeof(char));

    for (int m = 0; num2[m] != '\0'; m++)
    {    
        for (int n = 0; num1[n] != '\0'; n++)
                result[2 * LEN - 2 - m - n] += (num1[n] - '0') * (num2[m] - '0');

        int index = 2 * LEN - 2;
        while (index != -1)
        {
            if (result[index] > 9)
            {    
                int temp = result[index];
                result[index] = temp % 10;
                if (temp / 10 != 0)
                        result[index - 1] += temp / 10;
            }
            index--;
        }
    }
    
    free(num1);
    free(num2);

    return result;
}

void reverse(char *num)
{
    char *p = num;
    char *q = &num[strlen(num) - 1];

    while (p < q)
    {
        char temp = *p;
        *p = *q;
        *q = temp;
        p++;
        q--;
    }
}

void print(char *result, int len)
{
    int num = 0;
    for (;num < len; num++)
        printf("%d", result[num]);
}