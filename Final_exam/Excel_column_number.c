#include <stdio.h>
int main(void)
{
    char alpha_list[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int num;
    scanf("%d", &num);
    while (num > 26)
    {
        printf("%c", alpha_list[num / 26 - 1]);
        num = num % 26;
    }
    printf("%c", alpha_list[num - 1]);
}