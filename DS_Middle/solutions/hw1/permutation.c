#include <stdio.h>

#define MAX_N 10

static int n;
static int used[MAX_N + 1];
static int perm[MAX_N];

static void dfs(int depth)
{
    if (depth == n) {
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                putchar(' ');
            }
            printf("%d", perm[i]);
        }
        putchar('\n');
        return;
    }

    /*
     * Trying candidates from small to large gives lexicographic order,
     * exactly matching the "smaller numbers first" requirement.
     */
    for (int value = 1; value <= n; ++value) {
        if (!used[value]) {
            used[value] = 1;
            perm[depth] = value;
            dfs(depth + 1);
            used[value] = 0;
        }
    }
}

int main(void)
{
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    dfs(0);
    return 0;
}
