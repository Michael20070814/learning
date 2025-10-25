#include <stdio.h>/*  在命令行中打开其他文件  */
int main(void)
{
    int ch;

    while ((ch = getchar()) != EOF)
        putchar(ch);
    
    return 0;
}