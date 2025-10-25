#include <stdio.h>
#include <ctype.h>
int main(void)
{
    char ch;
    int space_num, line_num, other_num;
    space_num = line_num = other_num = 0;

    printf("Please enter whatever you like, "
        "and enter # to quit");
    while ((ch = getchar()) != '#')
    {
        if (ch == ' ')
            space_num++;
        else if (ch == '\n')
            line_num++;
        else
            other_num++;
    }
    printf("%d space, %d line break, %d other characters", space_num, line_num, other_num);
    return 0;
}