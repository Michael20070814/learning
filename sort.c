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
    int sequence = 0;
    int flag;
    int index[num];
    int actual_num = 0;
    memset(index, 0, sizeof(index)); // 手动清零
    for (int n = 0; n < num; n++) // 统计真实拥有的电话 去除重复
    {
        for (int i = 0; i < n; i++)
        {   
            if ((!strncmp(arr[n].name, arr[i].name, SIZE)) && (!strncmp(arr[n].name, arr[i].name, SIZE)))
                break;
            else
                actual_num++;
        }
    }
    People *new_arr = (People *) malloc(sizeof(People) * actual_num);
    for (int n = 0; n < num; n++)
    {
        flag = 0;
        int i;
        for (i = n - 1; i >= 0; i--)
        {    
            if ((!strncmp(arr[n].name, arr[i].name, SIZE)) && (!strncmp(arr[n].phone, arr[i].phone, SIZE)))
            {
                flag = 1;
                break;
            }
            else if (!strncmp(arr[n].name, arr[i].name, SIZE))
            {
                flag = 2;
                break;
            }
        }
        if (flag == 1)
            continue;
        else if (flag == 2)
        {
            if (index[i] == 0)
            {
                int length = strlen(arr[n].name);
                new_arr[sequence].name = (char *) malloc(sizeof(char) * SIZE);
                strncpy(new_arr[sequence].name, arr[n].name, length);
                new_arr[n].name[length] = '_';
                new_arr[n].name[length + 1] = '1';
                new_arr[n].name[length + 2] = '\0';
                new_arr[sequence].phone = (char *) malloc(sizeof(char) * SIZE);
                strncpy(new_arr[sequence].phone, arr[n].phone, strlen(arr[n].phone));
            }
            else if (index[i] > 0)
            {
                int length = strlen(arr[n].name);
                new_arr[sequence].name = (char *) malloc(sizeof(char) * SIZE);
                strncpy(new_arr[sequence].name, arr[n].name, length);
                new_arr[sequence].name[length - 1] = index[i] + '0'; 
                index[n] = index[i] + 1;
                new_arr[sequence].phone = (char *) malloc(sizeof(char) * SIZE);
                strncpy(new_arr[sequence].phone, arr[n].phone, strlen(arr[n].phone));
            }
        }
        else
        {
            new_arr[sequence].name = (char *) malloc(sizeof(char) * SIZE);
            strncpy(new_arr[sequence].name, arr[n].name, strlen(arr[n].name) + 1);
            new_arr[sequence].phone = (char *) malloc(sizeof(char) * SIZE);
            strncpy(new_arr[sequence].phone, arr[n].phone, strlen(arr[n].phone) + 1);
            index[n] += 1;
        }
        sequence++;
    }
    return new_arr;
}