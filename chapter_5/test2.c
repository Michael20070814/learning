#include <stdio.h>
int main(void)
{
    int enter;
    int criterion;
    printf("Please enter your int:\n");
    scanf("%d", &enter);
    criterion = enter + 10;
    while (enter <= criterion)
    {
        printf("%d\t", enter);
        enter++;
    }
    return 0;
}