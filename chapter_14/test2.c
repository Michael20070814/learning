#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
struct MON
{
    char name[20];
    char simple[4];
    int days;
    int index;
};
struct MON month[12]= 
{
    {"January", "Jan", 31, 1},
    {"February", "Feb", 28, 2},
    {"March", "Mar", 31, 3},
    {"April", "Apr", 30, 4},
    {"May", "May", 31, 5},
    {"June", "Jun", 30, 6},
    {"July", "Jul", 31, 7},
    {"August", "Aug", 31, 8},
    {"September", "Sep", 30, 9},
    {"October", "Oct", 31, 10},
    {"November", "Nov", 30, 11},
    {"December", "Dec", 31, 12},
    };
int main(void)
{
    int day, year, num;
    char mon[20];
    int result = 0;
    printf("Please enter day, month and year");
    scanf("%d%s%d", &day, mon, &year);
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        month[1].days = 29;
    if (isdigit(mon[0]))
        num = atoi(mon);
    else
        for (int n = 0; n < 12; n++)
            if (!(strncmp(mon, month[n].name, 3)))
                num = n;
    for (int n = 0; n < num - 1; n++)
        result += month[n].days;
    result += day;
    printf("%d", result);

    return 0;
}