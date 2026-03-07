#include <stdio.h>
#include <string.h>
int main(void)
{
    char c[] = "\t\v\\\0will\n";

    printf("%d", strlen(c));

    return 0;
}