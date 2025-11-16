#include <stdio.h>
struct Student
{
    char name[20];
    int score;
};
int main(void)
{
    int average, tag;
    int highest;
    struct Student class[3];

    printf("Please enter three students' name and score: \n");
    for (int num = 0; num < 3; num++)
    {
        scanf("%s%d", &class[num].name, &class[num].score);//数组名本身就是地址不能再加&
    }
    average = (class[0].score + class[1].score + class[2].score) / 3;
    highest = class[0].score;
    tag = 0;
    for (int num = 0; num < 3; num++)
    {
        if (highest > class[num].score)
        {    
            highest = highest;
        }
        else
        {
            highest = class[num].score;
            tag = num;
        }
    }
    printf("Average points: %d\n", average);
    printf("Highest student: %s %d\n", class[tag].name, class[tag].score);

    return 0;
}
