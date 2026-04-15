#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll p;
    ll c;
} Soldier;

int cmp(const void *a, const void *b) {
    ll ca = ((Soldier *)a)->c;
    ll cb = ((Soldier *)b)->c;
    if (ca < cb) return -1;
    if (ca > cb) return 1;
    return 0;
}

int main() {
    int n;
    ll S;
    scanf("%d %lld", &n, &S);

    Soldier *a = (Soldier *)malloc(sizeof(Soldier) * n);

    ll total_individual = 0;   // 全部单独训练的总花费
    ll active_sum = 0;         // 当前还能从一次团训中受益的士兵 p_i 之和

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &a[i].p, &a[i].c);
        total_individual += a[i].p * a[i].c;
        active_sum += a[i].p;
    }

    qsort(a, n, sizeof(Soldier), cmp);

    ll cur = total_individual; // 当前花费 f(k)
    ll ans = cur;
    ll prev = 0;
    int i = 0;

    while (i < n) {
        ll c = a[i].c;
        ll len = c - prev; // 在 [prev, c-1] 这段内，active_sum 不变

        // 一次团训带来的净变化：+S - active_sum
        cur += len * (S - active_sum);
        if (cur < ans) ans = cur;

        // 到达 k = c 后，所有 c_i == c 的士兵不再需要后续团训
        while (i < n && a[i].c == c) {
            active_sum -= a[i].p;
            i++;
        }

        prev = c;
    }

    printf("%lld\n", ans);

    free(a);
    return 0;
}