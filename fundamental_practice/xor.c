#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

void input(int *arr1, int *arr2, int *size1, int *size2);
int *process_arr(int *arr1, int *arr2, int *size, int size1, int size2);
void print(int *result, int size);
int cmp(const void *a, const void *b);

int main(void)
{
    int input1[SIZE];
    int input2[SIZE];
    int size1, size2;
    int size = 0;

    input(input1, input2, &size1, &size2);

    int *p = process_arr(input1, input2, &size, size1, size2);

    print(p, size);

    return 0;
}

void input(int *arr1, int *arr2, int *size1, int *size2)
{
    int temp;int index = 0;
    char ch;
    while (scanf("%d", &temp) == 1)
    {
        arr1[index++] = temp;
        if ((ch = getchar()) == '\n')
            break;
    }
    *size1 = index;
    index = 0;
    while (scanf("%d", &temp) == 1)
    {
        arr2[index++] = temp;
        if ((ch = getchar()) == '\n')
            break;
    }
    *size2 = index;
}

int *process_arr(int *arr1, int *arr2, int *size, int size1, int size2)
{
    *size = 0;
    int *result = (int *) malloc(sizeof(int) * 2 * SIZE);
    int index = 0;

    for (int m = 0; m < size1; m++)
    {
        int flag = 1;
        for (int n = 0; n < size2; n++)
        {
            if (arr1[m] == arr2[n])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 0)
            continue;
        else
        {
            result[index++] = arr1[m];
        }
    }
    
    for (int m = 0; m < size2; m++)
    {
        int flag = 1;
        for (int n = 0; n < size1; n++)
        {
            if (arr2[m] == arr1[n])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 0)
            continue;
        else
        {
            result[index++] = arr2[m];
        }
    }

    qsort(result, index, sizeof(int), cmp);
    *size = index;
    return result;
}

void print(int *result, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", result[i]);
}

int cmp(const void *a, const void *b)
{
    const int *first = (const void *)a;
    const int *second = (const void *)b;

    if (*first < *second)
        return 1;
    else if (*first > *second)
        return -1;
    else
        return 0;
}