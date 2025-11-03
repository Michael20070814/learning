#include <stdio.h>
void add_arr(const int ar[], const int ar1[], int ar2[], int n);
void show_arr(int ar[], int n);
int main(void)
{
    const int list_1[] = {2, 4, 5, 8};
    const int list_2[] = {1, 0, 4, 6};
    int list_3[4];
    add_arr(list_1, list_2, list_3, 4);
    show_arr(list_3, 4);
}
void add_arr(const int ar[], const int ar1[], int ar2[], int n)
{
    for (int count = 0; count < n; count++)
        ar2[count] = ar1[count] + ar[count];
}
void show_arr(int ar[], int n)
{
    for (int count = 0; count < n; count++)
            printf("%d ", ar[count]);
}