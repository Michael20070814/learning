#include <math.h>
#include <stdio.h>

/*
 * pi / 2 = 1 + 1!/3 + 2!/(3*5) + ...
 * term[k] = k! / (3*5*...*(2k+1)), term[0] = 1.
 * Therefore term[k] = term[k - 1] * k / (2k + 1).
 */
int main(void)
{
    double eps;
    double term = 1.0;
    double sum = 1.0;
    double prev_pi = 2.0;
    double pi = prev_pi;
    int n = 1;

    if (scanf("%lf", &eps) != 1) {
        return 0;
    }

    do {
        int k;

        ++n;
        k = n - 1;
        term *= (double)k / (double)(2 * k + 1);
        sum += term;
        pi = 2.0 * sum;

        if (n >= 2 && fabs(pi - prev_pi) < eps) {
            break;
        }
        prev_pi = pi;
    } while (1);

    printf("%d %.7f\n", n, pi);
    return 0;
}
