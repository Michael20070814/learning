#include <stdio.h>
#include <stdlib.h>

void print(int *v, int n)
{
    for (int i = 0; i < n; i++)
        printf("%4d", v[i]);
    printf("\n");
}

void heapPermute(int *v, int n, int size)
{
    if (size == 1)
    {
        print(v, n);
        return;
    }
    for (int i = 0; i < size; i++)
    {
        heapPermute(v, n, size - 1);
        int j = (size % 2 == 1) ? 0 : i;

        int tmp = v[j];
        v[j] = v[size-1];
        v[size-1] = tmp;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    
    int *v = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        v[i] = i + 1;

    heapPermute(v, n, n);

    free(v);
    return 0;
}