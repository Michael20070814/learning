#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 100
int main(void)
{
    int max, start;
    max = start = 0;
    int alpha[26] = {0};
    memset(alpha, -1, 26 * sizeof(int));
    char input[MAX_LENGTH];
    scanf("%s", input);
    for (int num = 0; input[num] != '\0'; num++)
    {
        if (alpha[input[num] - 'a'] != -1 &&
            alpha[input[num] - 'a'] >= start)
            start = alpha[input[num] - 'a'] + 1; // 这里面记录的是第一次出现的元素的下标，并非后面出现的下标
        alpha[input[num] - 'a'] = num;
        int current_len = num - start + 1;
        if (current_len > max)
            max = current_len;
    }
    printf("%d", max);

    return 0;
}