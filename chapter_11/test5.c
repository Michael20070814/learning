#include <stdio.h>
char * search(char *ct, char goal)
{
    while (*ct != '\0')
    {
        if (*ct == goal)
        {
            return ct;
        }
        ct++;
    }
    return NULL;
}
int main(void)
{
    char *result;
    result = search("I love you", 'e');
    printf("%c", *result);
    return 0;
}