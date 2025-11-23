#include <stdio.h>
struct Student
{
    char name[20];
    int score;
};
void updateScore(struct Student *s, int newScore);
void printStudent(struct Student *s);
int main(void)
{
    struct Student s1;

    printf("Please enter the name of the student: \n");
    scanf("%s", s1.name);
    printf("Please enter the score of the student: \n");
    scanf("%d", s1.score);//结构体时可以使用打点调用
    printStudent(&s1);//参数是指针的时候传入一个地址
    updateScore(&s1, 95);
    printStudent(&s1);
    
    return 0;
}
void updateScore(struct Student *s, int newScore)
{
    s->score = newScore;
}
void printStudent(struct Student *s)//结构体数组变成指针之后只能使用箭头
{
    printf("Name: %s\nScore: %d\n", s->name, s->score);
}