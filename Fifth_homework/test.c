#include <stdio.h>
#include <string.h>


int main(void)
{
    char src[] = "myfile.txt";

    char *p = strstr(src, ".txt");

    strcpy(p, ".hzip");

    printf("%s", src);

    return 0;
}