#include <stdio.h>
void cube(double n);
int main(void)
{
    double enter;
    double cubic_number;

    printf("Please enter a double:\n");
    scanf("%lf", &enter);

    cube(enter);
    
    return 0;
}
void cube(double n)
{
    double cubic_number;
    cubic_number = n * n * n;
    printf("The cube for your number is %f\n", cubic_number);
}