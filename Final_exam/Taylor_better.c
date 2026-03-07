#include <stdio.h>
#include <math.h>
double multichoice(double a, int n);
double jiecheng(int n);
double taylor_series(double x, double a, int n) {
    double sum = 0;
    for (int k = 0; k <= n; ++k) {
        sum += pow((x - a) , k) / multichoice(a, k);
    }
    return sum;
}

double multichoice(double a, int n) {
    if (n == 0 || n == 1)
        return 1.0;
    double result = 1.0;
    for (int num = 0; num < n; ++num) {
        result *= (a - num);
    }
    return result;
}

double jiecheng(int n) {
    double result = 1.0;
    for (int num = 2; num <= n; ++num) {
        result *= num;
    }
    return result;
}

int main(void) {
    double x, a;
    int n;
    
    printf("Enter x: ");
    scanf("%lf", &x);
    
    printf("Enter a: ");
    scanf("%lf", &a);
    
    printf("Enter n: ");
    scanf("%d", &n);
    
    double previous = taylor_series(x, a, 0);
    double current = taylor_series(x, a, n);
    double gap = fabs(current - previous);
    
    printf("Sum after %d terms: %.9lf\nGap between last two terms: %.9lf\n", 
           n, current, gap);
    
    return 0;
}