#include <stdio.h>
#define CM_PER_INCH 2.54
#define INCH_PER_FOOT 12
int main(void)
{
    float height; 
    float inch_height;
    int foot_height;
    printf("Please enter your height in cm:\n");
    scanf("%f", &height);
    while (height > 0)
    {
        inch_height = height / CM_PER_INCH % INCH_PER_FOOT;
        foot_height = height / CM_PER_INCH / INCH_PER_FOOT;
        printf("%f cm = %d feet, %f inches", height, foot_height, inch_height);
        printf("Please enter your height in cm:\n");
        scanf("%f", &height);
    }
    return 0;
}