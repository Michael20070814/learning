#include <stdio.h>
#include <stdlib.h>

int selection_sort(int arr[], int n); // 选择排序 返回比较次数
static void swap(int *a, int *b); // 标准交换函数
void output(int arr[], int n, int times); // 标准输出
int bubble_sort(int arr[], int n); // 冒泡排序
int adjust(int k[ ],int i,int n); // 调整顶堆
int heapSort(int k[ ],int n); // 堆排序调用
static void merge(int arr[], int temp[], int left, int middle, int right, int *times); // 二路归并合并
static void merge_sort_recursive(int arr[], int temp[], int left, int right, int *times); // 二路归并递归
void merge_sort(int arr[], int n, int *times); // 二路归并调取
static int partition(int arr[], int low, int high, int *times); // 快速排序分块
static void quick_sort_recursive(int arr[], int low, int high, int *times); // 快速排序递归调用
void quick_sort(int arr[], int n, int *times); // 快速排序调用

int main(void)
{
    int input_times;
    scanf("%d", &input_times);

    int method;
    scanf("%d", &method);

    int input[input_times];

    for (int i = 0; i < input_times; i++)
        scanf("%d", &input[i]);

    int times;

    switch (method)
    {
        case 1:
        times = selection_sort(input, input_times);
        break;
        case 2:
        times = bubble_sort(input, input_times);
        break;
        case 3:
        times = heapSort(input, input_times);
        break;
        case 4:
        merge_sort(input, input_times, &times);
        break;
        case 5:
        quick_sort(input, input_times, &times);
        break;
    }

    output(input, input_times, times);

    return 0;
}

int selection_sort(int arr[], int n)
{
    int result = 0;
    for (int i = 0; i < n - 1; i++) 
    {
        int min_index = i;

        for (int j = i + 1; j < n; j++)
        {
            result++;
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }

        if (min_index != i)
        {
            swap(&arr[i], &arr[min_index]);
        }
    }

    return result;
}

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void output(int arr[], int n, int times)
{
    for (int m = 0; m < n; m++)
        printf("%d ", arr[m]);
    
    printf("\n%d", times);
}

int bubble_sort(int arr[], int n)
{
    int result = 0;
    for (int i = 0; i < n - 1; i++) 
    {
        int swapped = 0;

        for (int j = 0; j < n - 1 - i; j++) 
        {
            result++;
            if (arr[j] > arr[j + 1]) 
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }
    }

    return result;
}


int adjust(int k[ ],int i,int n)
{
    int j;
    int temp;
    int result = 0;
    temp=k[i];
    j=2*i+1;  //由于数组下标从0开始，所以2*i +1 是指向结点左孩子的下标，
    while(j<n)
    {
        if(j+1<n && k[j]<k[j+1])
            j++; // j指向i结点左右孩子中值大的那个结点
        result++;
        if(temp<k[j])
        {
            k[(j - 1) / 2]= k[j];  // j结点的值赋到其父结点中
            j=2*j+1;   //  j指向自己的左孩子
        } 
        else
            break;
    }
    k[(j - 1) / 2]=temp;

    return result;
}

int heapSort(int k[ ],int n)
{
    int i, temp;

    int result = 0;
    for(i=n/2-1;i>=0;i--)
        result += adjust(k,i,n);
    for(i=n-1;i>=1;i--)
    {
        temp=k[i];
        k[i]=k[0];
        k[0]=temp;
        result += adjust(k,0,i);  //每次都排好一个位置
    }

    return result;
}

static void merge(int arr[], int temp[], int left, int middle, int right, int *times)
{
    int i = left;
    int j = middle + 1;
    int k = left;

    while (i <= middle && j <= right) 
    {
        (*times)++;

        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= middle) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

static void merge_sort_recursive(int arr[], int temp[], int left, int right, int *times)
{
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;
    merge_sort_recursive(arr, temp, left, middle, times);
    merge_sort_recursive(arr, temp, middle + 1, right, times);
    merge(arr, temp, left, middle, right, times);
}

void merge_sort(int arr[], int n, int *times)
{
    if (n <= 1) {
        return;
    }

    int *temp = (int *)malloc((size_t)n * sizeof(int));
    if (temp == NULL) {
        return;
    }

    *times = 0;

    merge_sort_recursive(arr, temp, 0, n - 1, times);
    free(temp);
}

static int partition(int arr[], int low, int high, int *times)
{
    int last = low;

    for (int i = low + 1; i <= high; i++) {
        (*times)++;  // 统计 if (arr[i] < arr[left]) 这次比较

        if (arr[i] < arr[low]) {
            last++;
            swap(&arr[last], &arr[i]);
        }
    }

    swap(&arr[low], &arr[last]);

    return last;
}

static void quick_sort_recursive(int arr[], int low, int high, int *times)
{
    if (low < high) {
        int pivot_index = partition(arr, low, high, times);
        quick_sort_recursive(arr, low, pivot_index - 1, times);
        quick_sort_recursive(arr, pivot_index + 1, high, times);
    }
}

void quick_sort(int arr[], int n, int *times)
{
    *times = 0;
    if (n <= 1) {
        return;
    }

    quick_sort_recursive(arr, 0, n - 1, times);
}
