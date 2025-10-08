#include <stdio.h>
int main()
{
    float f;
    printf("Enter a floating-poing value:");
    scanf("%f", &f);
    printf("fixed-poing notation: %f \n",f);
    printf("exponential notation: %e \n",f);
    printf("p notation: %a \n",f);
    return 0;
}
/* 如何解决输入数位过长导致错误的问题？如5612.2698 */