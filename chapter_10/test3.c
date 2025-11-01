#include <stdio.h>
int return_max(int ar[], int n);
int main(void)
{
    int list[10] = { 10, 100, -10, 90, 20, 40, 25, 19, 64, 86 };
    printf("%d", return_max(list, 10));
    return 0;
}
int return_max(int ar[], int n)
{
    int max = ar[0];
    for (int count = 0; count < n; count++)
    {
        if (ar[count] > max)
            max = ar[count];
    }
    return max;
}