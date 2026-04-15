#include <stdio.h>
#include <string.h>

#define MAXN 100005

char s[MAXN];

int is_good_edge(char a, char b) {
    int x = a - '0';
    int y = b - '0';
    return (y == x || y == x + 1);
}

int main() {
    scanf("%s", s);
    int n = strlen(s);

    long long ans = 0;
    int left = 0;
    int bad_cnt = 0;

    for (int right = 0; right < n; right++) {
        if (right > 0 && !is_good_edge(s[right - 1], s[right])) {
            bad_cnt++;
        }

        while (bad_cnt > 1) {
            if (left + 1 <= right && !is_good_edge(s[left], s[left + 1])) {
                bad_cnt--;
            }
            left++;
        }

        ans += (long long)(right - left + 1);
    }

    printf("%lld\n", ans);
    return 0;
}