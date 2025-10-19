#include <stdio.h>
float two_float_minus(float m, float n);
int main(void)
{
    float num_1, num_2, result;
    printf("Please enter two floats:(q to quit)");
    while (scanf("%f %f", &num_1, &num_2) == 2)
    {
        printf("The result is %f\n", two_float_minus(num_1, num_2));
        printf("Please enter two floats:(q to quit)");
    }
    return 0;
}
float two_float_minus(float m, float n)
{
    float result;
    result = (m - n)/(m * n);
    return result;
}