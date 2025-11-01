#include <stdio.h>
void reverse_list(double ar[], double *end);
void swap(double *ptr, double *ptr1);
int main(void)
{
    double list[10] = { 1.1, 2.6, 1.9, 12.3, 15.9, 21.4, 99.7, 0.9, 45.7, 16.8};
    reverse_list(list, list + 9);
    for (int item = 0; item < 10; item++)
        printf("%lf\n", list[item]);
    return 0;
}
void reverse_list(double *ar, double *end)
{
    double reverse_list[end - ar + 1];
    for (int count = 0; count < (end - ar + 1)/2; count++, ar++, end--)
        swap(ar, end);
}
void swap(double *ptr, double *ptr1)
{
    double temp;
    temp = *ptr;
    *ptr = *ptr1;
    *ptr1 = temp;
    return;
}