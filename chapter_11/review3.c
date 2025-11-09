#include <stdio.h>
#include <string.h>
int main(void)
{
    char food [] = "Yummy";
    char *ptr;

    ptr = food + strlen(food);
    while (--ptr >= food)//food自动退化为指向food[0]的指针，比较他们指的位置
        puts(ptr);
    return 0;
}