#include <stdio.h>
struct Student
{
    char name[20];
    int score;
};
struct Student * findTopStudent(struct Student *arr, int size);
int main(void)
{
    struct Student class[5];
    struct Student *ptr;

    printf("Please enter 5 students' name and score: \n");
    for (int num = 0; num < 5; num++)
        scanf("%s%d", class[num].name, &class[num].score);
    ptr = findTopStudent(class, 5);
    printf("Name: %s\nScore: %d\n", ptr->name, ptr->score);

    return 0;
}
struct Student * findTopStudent(struct Student *arr, int size)
{
    int tag = 0;
    int highest = arr[0].score;
    for (int num = 0; num < size; num++)//寻找最高分可以从1开始，因为第一个已经被当作最高分了
    {
        if (arr[num].score > highest)
        {
            highest = arr[num].score;
            tag = num;
        }
    }
    return arr + tag;
}