#include <stdio.h>

void input(char s[]) 
{
    int index = 0;
    int c;
    
    while ((c = getchar()) != EOF) 
    {
        s[index++] = (char)c;
    }
    
    s[index] = '\0';
}
void compute_alpha(char s[], int arr[26]) 
{
    while (*s != '\0') 
    {
        if (*s >= 'a' && *s <= 'z')
            arr[*s - 'a']++;
        s++;
    }
}

int find_max(int arr[26])
{
    int max = arr[0];
    for (int num = 1; num < 26; num++)
    {
        max = (max > arr[num]) ? max : arr[num];
    }
    return max;
}

void output(int arr[26])
{
    int max = find_max(arr);

    for (int m = 0; m < max; m++)
    {
        for (int n = 0; n < 26; n++)
        {
            if (m + arr[n] >= max)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("abcdefghijklmnopqrstuvwxyz\n");
}

int main(void)
{
    char s[10000];
    int alpha[26] = {};

    input(s);
    compute_alpha(s, alpha);

    output(alpha);
}



