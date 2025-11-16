#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int add(char *input);
int main(void)
{
    char input[10000];
    int num;

    scanf("%s", &input);
    num = add(input);
    printf("%d", num);

    return 0;
}
int add(char *input)
{
    int length = strlen(input);
    int temp = 0;
    int n = 0;
    char result[20];
    for (int num = 0; num < length; num++)
    {
        temp += input[num] - '0';
    }
    if (temp > 9)
    {
        sprintf(result, "%d", temp);
        temp = add(result);
    }
    return temp;
}