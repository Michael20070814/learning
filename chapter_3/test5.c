#include <stdio.h>
int main()
{
    int age;
    printf("Enter your age:");
    scanf("%d", &age);
    printf("The seconds for your age is %e.\n", age*3.156e7);
    return 0;
}