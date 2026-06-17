#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    int Index;
    char Name[21];
    int time;
} student;

student table[50];
int tail = 0;

int isExisting(int index); // 通过index查询是否已经存在学生
void input(); // 读取用户信息
int cmp(const void *a, const void *b); // qsort排序函数
void output(); // 输出最终结果

int main(void)
{

    input();

    qsort(table, tail, sizeof(student), cmp);

    output();

    return 0;
}

int isExisting(int index)
{
    for (int i = 0; i < tail; i++)
    {
        if (index == table[i].Index)
            return i;
    }

    return -1;
}

void input()
{
    int num;

    scanf("%d", &num);

    for (int m = 0; m < num; m++)
    {
        int index;
        char buffer[21];
        int time;
        scanf("%d %s %d", &index, buffer, &time);

        int flag = isExisting(index);
        if (flag != -1)
            table[flag].time += time;
        else
        {
            table[tail].Index = index;
            strcpy(table[tail].Name, buffer);
            table[tail].time += time;
            tail++;
        }
    }
}

int cmp(const void *a, const void *b)
{
    student *first = (student *) a;
    student *second = (student *) b;

    if (first -> time > second -> time)
        return -1;
    else if (first -> time < second -> time)
        return 1;
    else if (first -> Index < second -> Index)
        return -1;
    else if (first -> Index > second -> Index)
        return 1;
    else
        return 0;
}

void output()
{
    for (int m = 0; m < tail; m++)
    {
        printf("%d %s %d\n", table[m].Index, table[m].Name, table[m].time);
    }

}