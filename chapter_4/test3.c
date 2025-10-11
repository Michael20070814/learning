#include <stdio.h>
int main(void)
{
    float num, num2;
    printf("Please enter a float: \n");
    scanf("%f", &num);
    printf("The input is %.1f or %.1e. \n", num, num);
    printf("Please enter a float: \n");
    scanf("%f", &num2);
    printf("The input is %.3f or %.3e. \n", num2, num2);
    return 0;
}