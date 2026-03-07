#include <stdio.h>
#include <string.h>

void input(char *s, int size)
{
    if (fgets(s, size, stdin) != NULL) 
    {
        int len = strlen(s);
        s[len - 1] = '\0';
    }
}
int countOperators(char arr[], int size) 
{
    int count = 0;
    for (int i = 0; i < size; i++) 
    {
        if (arr[i] == '+' || arr[i] == '-' || arr[i] == '*' || arr[i] == '/') 
        {
            count++;
        }
    }
    return count;
}
void delete_space(char *s);
int calculate(char *s, int size)
{
    for (int m = 0; m < size; m++)
    {
        if (s[m] == '+')
        {
            s[m] = '\0';
            return calculate(s, m) + calculate(&s[m + 1], size - m); 
        }
        else if (s[m] == '-')
        {
            s[m] = '\0';
            return calculate(s, m) - calculate(&s[m + 1], size - m);
        }
        
    }
}
int main(void)
{
    char s[10000];

    input(s, 10000);

    delete_space(s);

    while (strstr(s, '*') || strstr(s, '/'))
    {
        char temp;
    }
}