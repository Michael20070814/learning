#include <stdio.h>
#include <math.h>

int is_prime(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int count = 0;
    int num = 1;

    while (count < 2025) {
        num++;
        if (is_prime(num)) {
            count++;
        }
    }

    printf("%d\n", num);
    return 0;
}