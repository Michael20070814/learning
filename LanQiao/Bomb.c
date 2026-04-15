#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAXN 200005


typedef struct {
    double l, r;
} Interval;

Interval seg[MAXN];

int cmp(const void *a, const void *b) {
    Interval *x = (Interval *)a;
    Interval *y = (Interval *)b;
    if (x->l < y->l) return -1;
    if (x->l > y->l) return 1;
    return 0;
}

int main() {
    int n;
    const double M_PI = acos(-1.0);
    scanf("%d", &n);

    int cnt = 0;

    for (int i = 0; i < n; i++) {
        double x, y, r;
        scanf("%lf %lf %lf", &x, &y, &r);

        double d = sqrt(x * x + y * y);
        if (d <= r) {
            printf("0.000\n");
            return 0;
        }

        double theta = atan2(y, x);
        double delta = asin(r / d);

        double l = theta - delta;
        double rr = theta + delta;

        if (rr < 0 || l > M_PI / 2) continue;

        if (l < 0) l = 0;
        if (rr > M_PI / 2) rr = M_PI / 2;

        seg[cnt].l = l;
        seg[cnt].r = rr;
        cnt++;
    }

    if (cnt == 0) {
        printf("1.000\n");
        return 0;
    }

    qsort(seg, cnt, sizeof(Interval), cmp);

    double total = 0;
    double L = seg[0].l, R = seg[0].r;

    for (int i = 1; i < cnt; i++) {
        if (seg[i].l <= R) {
            if (seg[i].r > R) R = seg[i].r;
        } else {
            total += (R - L);
            L = seg[i].l;
            R = seg[i].r;
        }
    }
    total += (R - L);

    double prob = 1.0 - total / (M_PI / 2.0);

    if (prob < 0) prob = 0;
    if (prob > 1) prob = 1;

    printf("%.3f\n", prob);
    return 0;
}