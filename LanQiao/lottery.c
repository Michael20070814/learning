#include <stdio.h>

#define MAXN 100005

int a[MAXN], b[MAXN], c[MAXN];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]);

    int m;
    scanf("%d", &m);

    int pos1 = 1, pos2 = 1, pos3 = 1;
    int total = 0;

    while (m--) {
        int x1, x2, x3;
        scanf("%d %d %d", &x1, &x2, &x3);

        pos1 = (pos1 + x1 - 1) % n + 1;
        pos2 = (pos2 + x2 - 1) % n + 1;
        pos3 = (pos3 + x3 - 1) % n + 1;

        int v1 = a[pos1];
        int v2 = b[pos2];
        int v3 = c[pos3];

        int score = 0;

        // 三个相同
        if (v1 == v2 && v2 == v3) {
            score = 200;
        } else {
            // 两个相同
            if (v1 == v2 || v1 == v3 || v2 == v3) {
                if (score < 100) score = 100;
            }

            // 连续（严格顺序）
            if (v2 == v1 + 1 && v3 == v2 + 1) {
                if (score < 200) score = 200;
            }

            // 排序后连续
            int x = v1, y = v2, z = v3;
            // 排序
            if (x > y) { int t = x; x = y; y = t; }
            if (y > z) { int t = y; y = z; z = t; }
            if (x > y) { int t = x; x = y; y = t; }

            if (y == x + 1 && z == y + 1) {
                if (score < 100) score = 100;
            }
        }

        total += score;
    }

    printf("%d\n", total);
    return 0;
}