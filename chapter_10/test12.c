#include <stdio.h>
#define MONTHS 12
#define YEARS 5
void cal_year_rain(float *ptr, const float ar[][12], float *tot);
void cal_month_rain(float *subtot, const float ar[][12]);
int main(void)
{
    const float rain[YEARS][MONTHS] =
    {
        {4.3, 4.3, 4.3, 3.0, 2.0, 1.2, 0.2, 0.4, 2.4, 3.5, 6.6, 8.4},
        {8.5, 8.2, 1.2, 1.6, 2.4, 0.0, 5.2, 0.9, 0.3, 0.9, 1.4, 7.3},
        {9.1, 8.5, 6.7, 4.3, 2.1, 0.8, 0.2, 0.2, 1.1, 2.3, 6.1, 8.4},
        {7.2, 9.9, 8.4, 3.3, 1.2, 0.8, 0.4, 0.0, 0.6, 1.7, 4.3, 6.2},
        {7.6, 5.6, 3.8, 2.8, 3.8, 0.2, 0.0, 0.0, 1.3, 2.6, 5.2, 6.9}
    };

    float subtot, total;
    const float (*rainfall)[12] = rain;//声明指针之后一定要记得初始化它

    printf(" YEAR    RAINFALL (inches)\n");
    cal_year_rain(&subtot, rain, &total);
    printf("\nThe yearly average is %.1f inches.\n\n", total / YEARS);
    printf(" MONTHLY AVERAGES:\n");
    printf(" Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec\n");
    cal_month_rain(&subtot, rain);
    printf("\n");

    return 0;
}
void cal_year_rain(float *ptr, const float ar[][12], float *tot)
{
    int year, month;
    float subtot1 = 0;
    float tot1 = 0;
    *ptr = 0;
    *tot = 0;
    for (year = 0, tot1 = 0; year < YEARS; year++)
    {
        for (month = 0, subtot1 = 0; month < MONTHS; month++)
            subtot1 += ar[year][month];
        printf("%5d %15.1f\n", 2000 + year, subtot1);
        tot1 += subtot1;
    }
    *ptr = subtot1;
    *tot = tot1;
}
void cal_month_rain(float *subtot, const float ar[][12])
{
    int year, month;
    float subtot1 = 0;
    for (month = 0; month < MONTHS; month++)
    {
        for (year = 0, subtot1 = 0; year < YEARS; year++)
            subtot1 += ar[year][month];
        printf("%4.1f ", subtot1 / YEARS);
    }
}