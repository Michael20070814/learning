#include <stdio.h>
int main()
{
    int num;
    scanf("%d", &num);
    if (num % 3 == 0)
        printf("%d", num / 3);
    else
        printf("%d", num / 3 + 1);

    return 0;
}