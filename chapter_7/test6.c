#include <stdio.h>
int main(void)
{
    char ch;
    int test, num;
    test = num = 0;
    while ((ch = getchar()) != '#')
    {
        if (test == 0 && ch == 'e')
            test++;
        else if (test == 1 && ch == 'i')
            num++;
        else
            test = 0;
    }
    printf("ei appears for %d times", num);
    return 0;
}