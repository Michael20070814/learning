#include <stdio.h>
#define RATE1 0.13230
#define RATE2 0.15040
#define RATE3 0.30025
#define RATE4 0.34025
#define BREAK1 360.0
#define BREAK2 468.0
#define BREAK3 720.0
#define BASE1 (RATE1 * BREAK1)
#define BASE2 (BASE1 + RATE2 * (BREAK2 - BREAK1))
#define BASE3 (BASE1 + BASE2 + RATE3 * (BREAK3 - BREAK2))
int main(void)
{
    double price;
    float consumption;

    printf("Please enter your electric consumption: ");
    scanf("%f", &consumption);

    if (consumption < BREAK1)
        price = consumption * RATE1;
    else if (consumption < BREAK2)
        price = (consumption - BREAK1) * RATE2 + BASE1;
    else if (consumption < BREAK3)
        price = (consumption - BREAK2) * RATE3 + BASE2;
    else
        price = (consumption - BREAK3) * RATE4 + BASE3;
    printf("Your bill is $%.2lf", price);
    
    return 0;
}