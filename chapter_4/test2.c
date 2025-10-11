#include <stdio.h>
#include <string.h>
int main(void)
{
    char full_name[20];
    printf("Please enter your name: \n");
    scanf("%19s", full_name);
    printf("\"%20s\"\n", full_name);//适用于名字无空格
    printf("\"%-20s\"\n", full_name);
    printf("\"%*s\"\n", strlen(full_name)+3, full_name);
    return 0;
}