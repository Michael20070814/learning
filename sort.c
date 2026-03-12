#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 50

typedef struct People
{
    char *name;
    char *phone;
} People;

People *input(int *num);
int Process_list(People *arr, int num);
int cmp(const void *a, const void *b);
void print(People *arr, int length);

int main(void)
{
    int num;
    People *arr = input(&num);
    int length = Process_list(arr, num);

    qsort(arr, length, sizeof(People), cmp);

    print(arr, length);

    return 0;
}

People *input(int *num)
{
    // 从stdin读取数量
    scanf("%d", num);

    // 分配 num 个 People 的数组
    People *arr = (People *)malloc(*num * sizeof(People));
    if (arr == NULL)
    {
        return NULL;
    }

    // 逐个读取每个 People 的数据
    for (int i = 0; i < *num; i++)
    {
        arr[i].name = (char *)malloc(SIZE * sizeof(char));
        arr[i].phone = (char *)malloc(SIZE * sizeof(char));

        if (arr[i].name == NULL || arr[i].phone == NULL)
        {
            return NULL;
        }

        scanf("%50s %50s", arr[i].name, arr[i].phone);
    }

    return arr;
}

int Process_list(People *arr, int num)
{
    int flag;
    for (int n = 0; n < num; n++)
    {
        flag = 0;
        for (int i = 0; i < n; i++)
            if ((!strncmp(arr[n].name, arr[i].name, SIZE)) && (!strncmp(arr[n].name, arr[i].name, SIZE)))
            {
                flag = 1;
                break;
            }
            else if (!strncmp(arr[n].name, arr[i].name, SIZE))
            {
                flag = 2;
                break;
            }
        if (flag == 1)
            continue;
        else
    }
}