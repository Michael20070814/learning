#include <stdio.h>
#include <stdlib.h>

/* Swap two integer values. */
static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Insertion sort: insert each element into the sorted part before it. */
void insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

/* Selection sort: repeatedly choose the smallest item from the unsorted part. */
void selection_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            swap(&arr[i], &arr[min_index]);
        }
    }
}

/* Bubble sort: move the largest unsorted value to the end in each pass. */
void bubble_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;

        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

/* Shell sort: sort elements with decreasing gaps, then finish with gap 1. */
void shell_sort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
    }
}

/* Keep the subtree rooted at root_index as a max heap. */
// recursion
static void heapify(int arr[], int n, int root_index)
{
    int largest = root_index;
    int left = 2 * root_index + 1;
    int right = 2 * root_index + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != root_index) {
        swap(&arr[root_index], &arr[largest]);
        heapify(arr, n, largest);
    }
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



/* Heap sort: build a max heap, then move the largest value to the end. */
void heap_sort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

/* Merge two sorted ranges: arr[left..middle] and arr[middle + 1..right]. */
static void merge(int arr[], int temp[], int left, int middle, int right)
{
    int i = left;
    int j = middle + 1;
    int k = left;

    while (i <= middle && j <= right) {
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

/* Recursively split the array and merge sorted halves. */
static void merge_sort_recursive(int arr[], int temp[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;
    merge_sort_recursive(arr, temp, left, middle);
    merge_sort_recursive(arr, temp, middle + 1, right);
    merge(arr, temp, left, middle, right);
}

/* Two-way merge sort: split the array into two halves and merge them back. */
void merge_sort(int arr[], int n)
{
    if (n <= 1) {
        return;
    }

    int *temp = (int *)malloc((size_t)n * sizeof(int));
    if (temp == NULL) {
        return;
    }

    merge_sort_recursive(arr, temp, 0, n - 1);
    free(temp);
}

/* Put values smaller than the pivot before it and larger values after it. */
static int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

/* Recursively sort the parts before and after the pivot. */
static void quick_sort_recursive(int arr[], int low, int high)
{
    if (low < high) {
        int pivot_index = partition(arr, low, high);
        quick_sort_recursive(arr, low, pivot_index - 1);
        quick_sort_recursive(arr, pivot_index + 1, high);
    }
}

/* Quick sort: choose a pivot, partition the array, and sort both sides. */
void quick_sort(int arr[], int n)
{
    if (n <= 1) {
        return;
    }

    quick_sort_recursive(arr, 0, n - 1);
}

/* Print an array. This helper is used only by the optional demo below. */
static void print_array(const int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 * Optional demo:
 * Compile with -DSORT_DEMO to run this main function.
 * Example: gcc sort_algorithms.c -DSORT_DEMO -o sort_demo
 */
#ifdef SORT_DEMO
int main(void)
{
    int arr[] = {64, 25, 12, 22, 11};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    quick_sort(arr, n);
    print_array(arr, n);

    return 0;
}
#endif
