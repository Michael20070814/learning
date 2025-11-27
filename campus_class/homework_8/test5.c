#include <stdio.h>
#include "calc.h"
int main(void)
{
    int num, object;
    object = 0;
    double aver_num, perc_75_num;
    scanf("%d", &num);
    double list[num];
    for (int n = 0; n < num; n++)
        scanf("%lf", &list[n]);
    aver_num = AVERAGE(list, num);
    perc_75_num = PERCENTILE_INC(list, num, 0.75);
    for (int n = 0; n < num; n++)
        if (list[n] > aver_num && list[n] < perc_75_num)
            object += 1;
    printf("%d", object);

    return 0;
}