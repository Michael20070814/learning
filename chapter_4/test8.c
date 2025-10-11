#include <stdio.h>
#define gasoline_conversion 3.785
#define mileage_conversion 1.609
int main(void)
{
    float mileage;
    float gasoline;
    printf("Please enter mileage and gasoline: \n");
    scanf("%f %f", &mileage, &gasoline);
    printf("%.1f \n", mileage / gasoline);
    printf("%.1f \n", gasoline * gasoline_conversion / mileage / gasoline_conversion);
    return 0;
}