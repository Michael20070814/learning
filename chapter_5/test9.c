#include <stdio.h>
void Temperatures(double n);
int main(void)
{
    double tempera;
    int num;
    printf("Please enter the temperature in Fahrenheit:(enter q or non-number to quit)");
    num = scanf("%lf", &tempera);
    while (num == 1)
    {
        Temperatures(tempera);
        printf("Please enter next number for temperature in Fahrenheit:(enter q or non-number to quit)");
        num = scanf("%lf", &tempera);
    }
    printf("Done!\n");
    return 0;
}
void Temperatures(double n)
{
    const double CEL_TO_KEL = 273.16;
    double CEL;
    double KEL;
    CEL = 5.0 / 9.0 * (n - 32.0);
    KEL = CEL + CEL_TO_KEL;
    printf("%.2lf℉ %.2lf℃ %.2lfK\n", n, CEL, KEL);
}