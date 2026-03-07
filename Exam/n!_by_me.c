#include <stdio.h>
#include <stdlib.h>

void print(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int permutation(int arr[], int size)
{
    int i = size - 2;
    while (arr[i] > arr[i + 1])
        i--;

    if (i < 0)
        return 0;
    
    int j = size - 1;
    while (arr[j] < arr[i])
        j--;

    swap(arr, i, j);

    int left = i + 1;
    int right = size - 1;
    while (left < right)
    {
        swap(arr, left, right);
        left++;
        right--;
    }
    return 1;
}

int* init(int num)
{
    int *arr = (int *)malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++)
        arr[i] = i + 1;

    return arr;
}

int main(void)
{

    int num;

    scanf("%d", &num);

    int *arr = init(num);

    do
    {
        print(arr, num);
    } while (permutation(arr, num));
    
}