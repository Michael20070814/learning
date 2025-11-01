#include <stdio.h>
void copy_arr(double ar[], const double ar1[], int n);
void copy_ptr(double ar[], const double ar1[], int n);
void copy_ptrs(double ar[], const double ar1[], const double *ptr);
int main(void)
{
    double source[5] = {1.1, 2.2, 3.3, 4.4 ,5.5};
    double target1[5];
    double target2[5];
    double target3[5];
    copy_arr(target1, source, 5);
    copy_ptr(target2, source, 5);
    copy_ptrs(target3, source, source + 5);
}
void copy_arr(double ar[], const double ar1[], int n)
{
    for (int count = 0; count < n; count++)
    {
        ar[count] = ar1[count];
    }
    for (int count = 0; count < n; count++)
        printf("%.2lf ", ar[count]);
    printf("\n");
}
void copy_ptr(double *ptr, const double *ptr1, int n)
{
    for (int count = 0; count < n; count++)
        *(ptr + count) = *(ptr1 + count);
    for (int count = 0; count < n; count++)
        printf("%.2lf " , *(ptr + count));
    printf("\n");
}
void copy_ptrs(double ar[], const double ar1[], const double *ptr)
{   
    const double *ptr1 = ar1;
    double *ptr2 = ar;
    for (; ptr1 < ptr; ptr1++, ptr2++)
    {
        *ptr2 = *ptr1;
    }
    ptr1 = ar1;
    ptr2 = ar;
    for (; ptr1 < ptr; ptr1++, ptr2++)
        printf("%.2lf ", *ptr2);
    printf("\n");
}
