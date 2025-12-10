#include <stdio.h>
int main(void)
{
    int volumes[26];
    char ch;
    int sum = 0;
    int num = 0;
    for (int num = 0; num < 26; num++)
        scanf("%d ", &volumes[num]);
    while ((ch = getchar()) != '\n')
    {
        sum += volumes[ch - 'a'];
        if (sum > 100)
        {    
            sum = volumes[ch - 'a'];
            num++;
        }
    }
    printf("%d %d", num + 1, sum);

    return 0;
}