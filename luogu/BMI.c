#include <stdio.h>
int main(void)
{
    double weight, height, bmi;

    scanf("%lf%lf", &weight, &height);
    bmi = weight / height / height;
    if (bmi < 18.5)
        printf("Underweight");
    else if (bmi < 24)
        printf("Normal");
    else
        printf("%.4lf\nOverweight", bmi);
    
    return 0;
}