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
        float total_inch = height / CM_PER_INCH;
        foot_height = total_inch / INCH_PER_FOOT;
        inch_height = total_inch - foot_height * INCH_PER_FOOT;
        printf("%.1f cm = %d feet, %.1f inches\n", height, foot_height, inch_height);
        printf("Please enter your height in cm:\n");
        scanf("%f", &height);
    }
    printf("Bye!\n");
    return 0;
}

//inch_height = height / CM_PER_INCH % INCH_PER_FOOT;    只有int类型可以进行求模运算
//foot_height = height / CM_PER_INCH / INCH_PER_FOOT;