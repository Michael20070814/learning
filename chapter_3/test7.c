#include <stdio.h>
int main(void)
{
    int height;
    printf("Enter your height in centimeters:");
    scanf("%d", &height);
    printf("Your height in inches is %f.\n", height / 2.54);
    return 0;
}