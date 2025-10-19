#include <stdio.h>
#include <string.h>
int main(void)
{
    int size, i;
    char letter[size];
    printf("Please enter a letter: ");
    scanf("%s", letter);
    size = strlen(letter);
    for (i=size-1; i >= 0; i--)
        printf("%c", letter[i]);
    return 0;
}