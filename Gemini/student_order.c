#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char name[20];
    int score;
} Student;
Student *input(int *num);
void swap(Student *p1, Student *p2);
void order(Student *student_list, int number);
void print_student(Student *student_list, int number);
int main(void)
{
    int student_number;
    Student *list = input(&student_number);
    order(list, student_number);
    print_student(list, student_number);

    free(list);
    return 0;
}
void swap(Student *p1, Student *p2) // 交换两名学生的顺序
{
    Student temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
Student *input(int *num) // 读取用户输入
{
    printf("Please enter the number of students.\n");
    int student_num;
    scanf("%d", &student_num);
    Student *list = (Student *) malloc(sizeof(Student) * student_num);
    for (int n = 0; n < student_num; n++)
    {
        printf("Please enter %dth student's name and score.\n", n + 1);
        scanf("%19s%d", list[n].name, &list[n].score); // 可以确保输入的安全性
    }
    *num = student_num;
    return list; 
}
void order(Student *student_list, int number) // 学生名单的排列 从高到低
{
    for (int m = 0; m < number; m++)
    {
        for (int n = 0; n < number - 1 - m; n++) // 最后的元素已经排好了
        {
            if (student_list[n].score < student_list[n + 1].score)
                swap(&student_list[n], &student_list[n + 1]);
        }
    }
}
void print_student(Student *student_list, int number) // 打印学生名单
{
    for (int num = 0; num < number; num++)
        printf("%s\t%d\n", student_list[num].name, student_list[num].score);
}