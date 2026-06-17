#include <stdio.h>
#include <stdlib.h>

#define LENGTH 21
#define SIZE 100

typedef struct student
{
    int StudentIndex;
    char name[LENGTH];
    int SeatIndex;
} student;

student table[100];
int tail = 0;

void input(); // 从文件中读取学号信息
int cmp(const void *a, const void *b); // 用作qsort的比较函数 按座位号从小到大进行排序
int cmp2(const void *a, const void *b); // 用作qsort的比较函数 按学号从小到大进行排序
void ProcessDrop(); // 对漏排作为进行处理与修复
void ProcessDuplicate(); // 对重复的行为进行处理与修复
void output(); // 向文件中输出学生信息
int JudgeDuplicate(int i); // 判断座位号i是否会导致重复的情况

int main(void)
{
    input();

    qsort(table, tail, sizeof(student), cmp);

    ProcessDrop();
    qsort(table, tail, sizeof(student), cmp);
    ProcessDuplicate();

    qsort(table, tail, sizeof(student), cmp2);
    output();

    return 0;
}

void input()
{
    scanf("%d", &tail);

    FILE *fp = fopen("in.txt", "r");

    for (int i = 0; i < tail; i++)
    {
        char buffer[SIZE];

        fgets(buffer, SIZE - 1, fp);
        
        sscanf(buffer, "%d %s %d", &table[i].StudentIndex, table[i].name, &table[i].SeatIndex);
    }

    fclose(fp);
}

int cmp(const void *a, const void *b)
{
    student *first = (student *) a;
    student *second = (student *) b;

    if (first -> SeatIndex < second -> SeatIndex)
        return -1;
    else if (first -> SeatIndex > second -> SeatIndex)
        return 1;
    else if (first -> StudentIndex < second -> StudentIndex)
        return -1;
    else if (first -> StudentIndex > second -> StudentIndex)
        return 1;
    else    
        return 0;
}

int cmp2(const void *a, const void *b)
{
    student *first = (student *) a;
    student *second = (student *) b;

    if (first -> StudentIndex < second -> StudentIndex)
        return -1;
    else if (first -> StudentIndex > second -> StudentIndex)
        return 1;
    else    
        return 0;
}

void ProcessDrop()
{
    int flag = 0;
    int max = -1;
    for (int i = 0; i < tail; i++)
        if (table[i].SeatIndex > max)
            max = table[i].SeatIndex;

    max = (max < tail) ? max : tail;

    int has[SIZE + 1] = {0};

    for (int i = 0; i < tail; i++)
    {
        if (table[i].SeatIndex <= max)
            has[table[i].SeatIndex] = 1;
    }

    for (int i = 1; i <= max; i++)
    {
        if (has[i] == 0)
        {
            table[tail - 1 - flag].SeatIndex = i;
            flag++;
        }
    }
}

void ProcessDuplicate()
{
    int flag = 1;
    int max = -1;

    for (int i = 0; i < tail; i++) 
        if (table[i].SeatIndex > max)
            max = table[i].SeatIndex;

    for (int i = 0; i < tail; i++)
    {
        if (i > 1 && table[i].SeatIndex == table[i - 1].SeatIndex)
        {
            table[i].SeatIndex = max + flag;
            flag++;
        }
    }
}

void output()
{
    FILE *fp = fopen("out.txt", "w");
    for (int i = 0; i < tail; i++)
    {
        fprintf(fp, "%d %s %d\n", table[i].StudentIndex, table[i].name, table[i].SeatIndex);
    }

    fclose(fp);
}

int JudgeIn(int i)
{
    for (int m = 0; m < tail; m++)
    {
        if (i == table[m].SeatIndex)
            return 1;
    }

    return 0;
}

int JudgeDuplicate(int i)
{
    for (int m = 0; m < tail; m++)
    {
        if (i != m && table[i].SeatIndex == table[m].SeatIndex)
            return m;
    }

    return 0;
}