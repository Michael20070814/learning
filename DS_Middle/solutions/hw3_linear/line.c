#include <stdio.h>

#define MAX_SEG 100

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Segment {
    Point start;
    Point end;
} Segment;

static Segment segs[MAX_SEG];
static int memo[MAX_SEG];
static int n;

static int same_point(Point a, Point b)
{
    return a.x == b.x && a.y == b.y;
}

static int chain_len(int idx)
{
    int best = 1;

    if (memo[idx] != 0) {
        return memo[idx];
    }

    /*
     * A following segment must start exactly at the current end point.
     * Recursion is safe because every segment goes from smaller x to larger x.
     */
    for (int j = 0; j < n; ++j) {
        if (same_point(segs[idx].end, segs[j].start)) {
            int len = 1 + chain_len(j);

            if (len > best) {
                best = len;
            }
        }
    }

    memo[idx] = best;
    return best;
}

int main(void)
{
    int best_idx = 0;
    int best_len = 0;

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d%d", &segs[i].start.x, &segs[i].start.y,
              &segs[i].end.x, &segs[i].end.y);
    }

    for (int i = 0; i < n; ++i) {
        int len = chain_len(i);

        if (len > best_len) {
            best_len = len;
            best_idx = i;
        }
    }

    printf("%d %d %d\n", best_len, segs[best_idx].start.x,
           segs[best_idx].start.y);
    return 0;
}
