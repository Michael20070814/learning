#include <stdio.h>
#include <stdlib.h>
struct Student//建立结构体，绑定名字与成绩
{
    char name[20];
    int score;
};
int findHighestStudents(struct Student *arr, int size, struct Student ***resultPtr);
int main(void)
{
    int num, i;
    struct Student **result = NULL;//创建空结构体指针数组

    printf("Please enter the number of students: \n");
    scanf("%d", &num);
    struct Student *class = malloc(num * sizeof(struct Student));//动态分配决定有几个学生
    printf("Please enter %d students' name and score: \n", num);
    for (int n = 0; n < num; n++)
        scanf("%s%d", class[n].name, &class[n].score);//对应存入数据
    i = findHighestStudents(class, num, &result);
    printf("Highest score: %d", result[0]->score);
    for (int n = 0; n < i; n++)
        printf("Name: %s\nScore: %d\n", result[n]->name, result[n]->score);//对返回数组循环取值
    
    return 0;
}
int findHighestStudents(struct Student *arr, int size, struct Student ***resultPtr)//使用星号传入数组的指针
{
    int highest, n, j;
    n = j = 0;
    highest = arr[0].score;
    for (int num = 0; num < size; num++)
    {
        if (arr[num].score > highest)
            highest = arr[num].score;//遍历数组寻找最高分的学生序号
    }
    for (int num = 0; num < size; num++)
    {    
        if (arr[num].score == highest)//统计最高分学生人数
            n += 1;
    }
    *resultPtr = malloc(n * sizeof(struct Student*));
    for (int num = 0; num < size; num++)
    {    
        if (arr[num].score == highest)
        {    
            (*resultPtr)[j] = &arr[num];//先解引用一次，外层是指针，不能使用[]取值
            j++;
        }
    }

    return n;
}