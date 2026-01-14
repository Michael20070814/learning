#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int index;
    char name[10];
    int score;
} Singer;
Singer *input(int *num);
int find_max(int *input, int length);
void swap(Singer *p1, Singer *p2);
int find_min(int *input, int length);
void order(Singer *Singer_list, int number);
void print_Singer(Singer *Singer_list, int number);
int main(void)
{
    int Singer_number;
    Singer *list = input(&Singer_number);
    if (list == NULL)
        return 0;
    order(list, Singer_number);
    print_Singer(list, Singer_number);

    free(list);
    return 0;
}
void swap(Singer *p1, Singer *p2) // 交换两名学生的顺序
{
    Singer temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
Singer *input(int *num) // 读取用户输入
{
    FILE *fp = fopen("output.txt", "a");
    printf("Please enter the number of Singers.\n");
    int Singer_num;
    scanf("%d", &Singer_num);
    if (Singer_num >= 10)
    {
        printf("Please input 1-9.\n");
        return NULL;
    }
    Singer *list = (Singer *) malloc(sizeof(Singer) * Singer_num);
    for (int n = 0; n < Singer_num; n++)
    {
        int temp[5] = {};
        list[n].score = 0;
        scanf("%d%4s%d%d%d%d%d", &list[n].index, list[n].name, &temp[0], &temp[1], &temp[2], &temp[3], &temp[4]); // 可以确保输入的安全性
        for (int m = 0; m < n; m++)
        {
            if (list[m].index == list[n].index)
            {
                fprintf(fp, "Please input the correct number.\n");
                return NULL;
            }
        }
        for (int m = 0; m < 5; m++)
            list[n].score += temp[m];
        list[n].score -= find_max(temp, 5) + find_min(temp, 5);
    }
    *num = Singer_num;
    return list; 
}
void order(Singer *Singer_list, int number) // 学生名单的排列 从高到低
{
    for (int m = 0; m < number; m++)
    {
        for (int n = 0; n < number - 1 - m; n++) // 最后的元素已经排好了
        {
            if (Singer_list[n].score < Singer_list[n + 1].score)
                swap(&Singer_list[n], &Singer_list[n + 1]);
            if (Singer_list[n].score == Singer_list[n + 1].score && Singer_list[n].index > Singer_list[n + 1].index)
                swap(&Singer_list[n], &Singer_list[n + 1]);
        }
    }
}
void print_Singer(Singer *Singer_list, int number) // 打印学生名单
{
    FILE *fp = fopen("output.txt", "a");
    for (int num = 0; num < number; num++)
    {
        if (Singer_list[num - 1].score == Singer_list[num].score)
            fprintf(fp, "   %d%4d%10s%5d\n", num, Singer_list[num].index, Singer_list[num].name, Singer_list[num].score);
        else
            fprintf(fp, "   %d%4d%10s%5d\n", num+1, Singer_list[num].index, Singer_list[num].name, Singer_list[num].score);
        
    }
    fclose(fp);
}
int find_max(int *input, int length)
{
    int temp;
    temp = input[0];
    for (int n = 0; n < length; n++)
    {
        if (input[n] > temp)
            temp = input[n];
    }
    return temp;
}
int find_min(int *input, int length)
{
    int temp;
    temp = input[0];
    for (int n = 0; n < length; n++)
    {
        if (input[n] < temp)
            temp = input[n];
    }
    return temp;
}