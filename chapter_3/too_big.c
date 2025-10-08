#include <stdio.h>
int main()
{
    int a = 20000000000000;
    float toobig = 3.0e38;
    float toosmall = 0.1234567e-16;
    printf("%d \n", a);
    printf("%f \n", toobig * 1000.0f);
    printf("%e \n", toosmall / 10);
    return 0;
}