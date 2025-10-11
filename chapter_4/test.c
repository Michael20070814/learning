#include <stdio.h>
int main(void)
{
    char name[40] = "Huang";
    float cash = 961.58;

    printf("The %s family just may be $%.2f richer!.\n", name, cash);

    return 0;
}