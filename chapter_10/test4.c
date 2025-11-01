#include <stdio.h>
int return_max_index(double ar[], int n);
int main(void)
{
    double list[10] = { 1.1, 2.6, 1.9, 12.3, 15.9, 21.4, 99.7, 56.1, 45.7, 16.8};
    printf("%d", return_max_index(list, 10));
    return 0;
}
int return_max_index(double ar[], int n)
{
    int max = ar[0];
    int index;
    for (int count = 0; count < n; count++)
    {
        if (ar[count] > max)
        {
            max = ar[count];
            index = count;
        }
    }
    return index;
}