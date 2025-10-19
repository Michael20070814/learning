#include <stdio.h>
int main(void)
{
    float num_1, num_2, result;
    printf("Please enter two floats:(q to quit)");
    while (scanf("%f %f", &num_1, &num_2) == 2)
    {
        result = (num_1 - num_2)/(num_1 * num_2);
        printf("The result is %f\n", result);
        printf("Please enter two floats:(q to quit)");
    }
    return 0;
}