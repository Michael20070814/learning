#include <stdio.h>
int is_within(char goal, char *ct)
{
    while (*ct != '\0')
    {
        if (*ct == goal)
        return 1;
        ct++;//注意对指针进行迭代，否则陷入死循环
    }
    return 0;
}
int main(void)
{
    char ch;
    int result;
    for (ch = 'a'; ch <= 'z'; ch++)
    {
        result = is_within(ch, "I love you");
        printf("%c in 'I love you' is %d\n", ch, result);
    }
    return 0;
}