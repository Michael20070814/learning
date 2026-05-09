#include <stdio.h>

/*
 * Prime factorization of a composite integer.
 * Trial division is enough here because the input fits in int.
 */
int main(void)
{
    int n;
    int first = 1;

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    for (int d = 2; (long long)d * d <= n; ++d) {
        while (n % d == 0) {
            if (!first) {
                putchar(' ');
            }
            printf("%d", d);
            first = 0;
            n /= d;
        }
    }

    /* If n is still greater than 1, it is the last prime factor. */
    if (n > 1) {
        if (!first) {
            putchar(' ');
        }
        printf("%d", n);
    }

    putchar('\n');
    return 0;
}
