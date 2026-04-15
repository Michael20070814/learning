#include <stdio.h>

const char* judge_color(long long k) {
    long long x = k - 1;
    int right_count = 0;

    while (x > 0) {
        right_count += (x & 1);
        x >>= 1;
    }

    if (right_count % 2 == 0) {
        return "RED";
    } else {
        return "BLACK";
    }
}

void solve_queries(int m) {
    int n;
    long long k;

    for (int i = 0; i < m; i++) {
        scanf("%d %lld", &n, &k);
        printf("%s\n", judge_color(k));
    }
}

int main() {
    int m;
    scanf("%d", &m);

    solve_queries(m);

    return 0;
}