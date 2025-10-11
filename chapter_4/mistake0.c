#include <stdio.h>
#define B "booboo"
#define X 10
int main(void)
{
    int age;
    char name[40];//须带上中括号，否则只有一个字节空间，会导致程序崩溃
    int xp;
    printf("Please enter your first name:\n");
    scanf("%s", name);
    printf("All right, %s, what's your age?\n", name);
    scanf("%d", &age);
    xp = age + X;
    printf("That's a %s! You must be at least %d.\n", B, xp);
    return 0;
}