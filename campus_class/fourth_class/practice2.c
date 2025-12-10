#include <stdio.h>
struct date
{
    int year;
    int month;
    int day;
};
int main(void)
{
    struct date person1, person2;
    scanf("%d%d%d", &person1.year, &person1.month, &person1.day);
    scanf("%d%d%d", &person2.year, &person2.month, &person2.day);
    if (person1.year < person2.year)
        printf("%d", 1);
    else if (person1.year > person2.year)
        printf("%d", 0);
    else
    {
        if (person1.month < person2.month)
            printf("%d", 1);
        else if (person1.month > person2.month)
            printf("%d", 0);
        else
        {
            if (person1.day < person2.day)
                printf("%d", 1);
            else if (person1.day > person2.day)
                printf("%d", 0);
            else
                printf("%d", 0);
        }
    }
}