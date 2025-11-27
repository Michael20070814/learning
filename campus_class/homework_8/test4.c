#include <stdio.h>
#include "calc.h"
int main(void)
{
    int num, percentage;
    
    scanf("%d%d", &num, &percentage);
    double temp[percentage], distribution[percentage];
    double origin[num];
    double result[num - percentage + 1];
    for (int n = 0; n < num; n++)
        scanf("%lf", &origin[n]);
    for (int n = 0; n < percentage; n++)
        distribution[n] = n + 1;
    for (int n = 0; n < num - percentage + 1; n++)
    {
        for (int j = 0; j < percentage; j++)
            temp[j] = origin[n + j];
        result[n] = WEIGHTED_SUM(temp, distribution, percentage) / percentage;
    }
    for (int n = 0; n < num - percentage + 1; n++)
        printf("%.2lf\n", result[n]);

    return 0;

}