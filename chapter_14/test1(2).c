#include <stdio.h>
#include <string.h>
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
    {"Februrary", "Feb", 28, 2},
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
    char mon[20];
    int num;
    int result = 0;
    scanf("%s", mon);
    for (int n = 0; n < 12; n++)
        if (!(strcmp(mon, month[n].name)))
            num = n;
    for (int n = 0; n <= num; n++)
        result += month[n].days;
    printf("%d", result);

    return 0;
}