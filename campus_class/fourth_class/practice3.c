#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    char temp[100];
    gets(temp);
    char *p = (char * ) malloc(sizeof(char) * strlen(temp));
    strcpy(p, temp);
    puts(p);
    free(p);
    return 0;
}