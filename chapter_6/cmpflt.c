#include <stdio.h>
#include <math.h>
int main(void)
{
    const double ANSWER = 3.14159;
    double response;

    printf("What is the value of pi?");
    scanf("%lf", &response);
    while (fabs(response - ANSWER) > 0.0001)
    {
        printf("try again!");
        scanf("%lf", &response);
    }
    printf("close enough!\n");
    return 0;
}