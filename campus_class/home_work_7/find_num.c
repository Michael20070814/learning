#include <stdio.h>
int main(void)
{
    int times = 0;
    int temp, maximum, minimum;
    scanf("%d", &times);
    scanf("%d", &temp);
    maximum = minimum = temp;
    for (int num = 0; num < times - 1; num++)
    {
        scanf("%d", &temp);
        maximum = (maximum > temp) ? maximum : temp;
        minimum = (minimum < temp) ? minimum : temp;
    }
    printf("%d %d", maximum, minimum);

    return 0;
}