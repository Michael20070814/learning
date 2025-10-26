#include <stdio.h>
#include <ctype.h>
int main(void)
{
    int ch;
    int lower_num, upper_num;
    lower_num = upper_num = 0;

    while ((ch = getchar()) != EOF)
    {
        if (islower(ch))
            lower_num++;
        else if (isupper(ch))
            upper_num++;
    }
    printf("Upper: %d\nLower: %d", upper_num, lower_num);

    return 0;
}