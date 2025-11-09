#include <stdio.h>
#include <stdlib.h>
double power(double ow, int n);
int main(int argc, char * argv [])
{
    double pow = atof(argv[1]);
    printf("%lf", power(pow, atoi(argv[2])));
    return 0;
}
double power(double pow, int n)
{
    double temp = 1.0;
    for (int num = 0; num < n; num++)
    {
        temp *= pow;
    }
    return temp;
}