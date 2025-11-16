#include <stdio.h>
int main()
{
    printf("- Size of int*: %zu\n", sizeof(int *));
    printf("- Size of char*: %zu\n", sizeof(char *));
    printf("- Size of double*: %zu\n", sizeof(double *));//32位则生成4

    char a = 'A';
    printf("%X: %c", &a, a);
}