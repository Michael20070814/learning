#include <stdio.h>
#define MSG "I am special"
int main(void)
{
    char ar[] = MSG;
    const char *pt = MSG;

    printf("address of \" I am special\": %p \n", "I am special");
    printf("            address ar: %p \n", ar);
    printf("            address pt: %p \n", pt);
    printf("        address of MSG: %p \n", MSG);
    printf("address of \" I am special\": %p \n", "I am special");

    return 0;
}