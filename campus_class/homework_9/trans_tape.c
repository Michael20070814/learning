#include <stdio.h>
#include <string.h>
void transpose(char *ar, int len);
void swap(char *p, char *q);
int main(void)
{
    int i, m;
    m = i = 0;
    char string[100];
    char result[100];

    scanf("%s", string);
    while (string[m] != '\0')
    {
        if (string[m] == 'i')
        {    
            transpose(result, i);
            m++;
        }
        else
        {    
            result[i] = string[m];
            i++;
            m++;
        }
    }
    puts(result);

    return 0;
}
void transpose(char *ar, int len)
{
    for (int i = 0; i < len / 2; i++)
        swap(&ar[i], &ar[len - 1 -i]);
}
void swap(char *p, char *q)
{
    char temp = *p;
    *p = *q;
    *q = temp;
}