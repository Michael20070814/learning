#include <stdio.h>
#include <string.h>
int add(char *input);
char input[10000000];
int main(void)
{
    
    int num;

    scanf("%s", input);
    num = add(input);
    printf("%d", num);

    return 0;
}
int add(char *input)
{
    int length, temp;
    while (1)
    {
        temp = 0;
        for (int num = 0; input[num] != '\0' ; num++)
        {
            temp += input[num] - '0';
        }
        if (temp > 9)
        {
            sprintf(input, "%d", temp);
        }
        else
            return temp;
    }   
}