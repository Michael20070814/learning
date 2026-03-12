#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_longest_sequence(char *p, int size);

int main(void)
{
    char s[10000];
    
    scanf("%s", s);

    int length = get_longest_sequence(s, strlen(s));

    printf("%d", length);

    return 0;
}

int get_longest_sequence(char *p, int size)
{
    int maxLength = 1;
    int *DP = (int *) malloc (sizeof(int) * size); // 存储到这里字符串的最大子串

    DP[0] = 1;
    for (int i = 1; i < size; i++)
    {
        DP[i] = 1;
        for (int j = i - 1; j >= 0; j--)
            if (DP[j] + 1 > DP[i] && p[j] <= p[i])
                DP[i] = DP[j] + 1;
        
        if (DP[i] > maxLength)
            maxLength = DP[i];
    }
    
    free(DP);

    return maxLength;
}