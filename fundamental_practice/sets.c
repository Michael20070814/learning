#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

int *input();
int *subtract_list(int *a, int *b);
void print(int *result);

int main(void)
{
    int *a = input();

    int *b = input();

    int *result = subtract_list(a, b);

    print(result);

    return 0;
}

int *input()
{
    int initial_capacity = 10;
    int count = 0;
    int num; int current_capacity = initial_capacity;

    int *arr = (int *) malloc(sizeof(int) * initial_capacity);

    while (scanf("%d", &num) == 1)
    {
        if (count == current_capacity - 1)
        {
            current_capacity *= 2;
            int *temp = (int *) realloc(arr, sizeof(int) * current_capacity);
            free(arr);
            arr = temp;
            arr[count] = num;
        }
        else
            arr[count++] = num;
        
        if (num == -1)
        {
            arr[count] = -1;
            break;
        }
    }

    return arr;
}

int *subtract_list(int *a, int *b)
{
    int length = 0;int flag = 0;int count = 0;
    for (int i = 0; a[i] != -1; i++)
    {
        length++;
    }

    int *result = (int *) malloc(sizeof(int) * length);

    
    for (int i = 0; a[i] != -1; i++)
    {
        for (int j = 0; b[j] != -1; j++)
        {
            if (a[i] == b[j])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            flag = 0;
            continue;
        }
        else
        {
            result[count++] = a[i];
        }
    }
    result[count] = -1;

    return result;
}

void print(int *result)
{
    for (int i = 0; result[i] != -1; i++)
    {
        printf("%d ", result[i]);
    }
}