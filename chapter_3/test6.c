#include <stdio.h>
int main(void)
{
    int quota;
    printf("Enter your water quota:");
    scanf("%d",&quota);
    printf("Your water particles number is %e. \n",quota*950*3.0e23);
    return 0;
}