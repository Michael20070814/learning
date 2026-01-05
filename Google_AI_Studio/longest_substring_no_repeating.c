#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 100
int main(void)
{
    int length, max;
    max = length = 0;
    int alpha[26] = {0};
    memset(alpha, -1, 26 * sizeof(int));
    char input[MAX_LENGTH];
    scanf("%s", input);
    for (int num = 0; input[num] != '\0'; num++)
    {
        if (alpha[input[num] - 'a'] != -1)
        {
            length = num - alpha[input[num] - 'a'];
            if (length > max)
                max = length;
            alpha[input[num] - 'a'] = num;
        }
        else
        {    
            alpha[input[num] - 'a'] = num;
        }
    }
    printf("%d", max);

    return 0;
} // 写错了，只能维护滑动窗口 