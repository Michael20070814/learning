#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 90
#define MAX_RESULT 200

static char *skip_leading_zero(char *s)
{
    while (*s == '0' && s[1] != '\0') {
        ++s;
    }
    return s;
}

int main(void)
{
    char a_buf[MAX_DIGITS];
    char b_buf[MAX_DIGITS];
    char *a;
    char *b;
    int ans[MAX_RESULT] = {0};
    int len_a;
    int len_b;
    int start = 0;

    if (scanf("%89s%89s", a_buf, b_buf) != 2) {
        return 0;
    }

    a = skip_leading_zero(a_buf);
    b = skip_leading_zero(b_buf);
    if (strcmp(a, "0") == 0 || strcmp(b, "0") == 0) {
        printf("0\n");
        return 0;
    }

    len_a = (int)strlen(a);
    len_b = (int)strlen(b);

    /*
     * ans[i + j + 1] stores the low digit of a[i] * b[j], matching the
     * usual hand-written multiplication positions.
     */
    for (int i = len_a - 1; i >= 0; --i) {
        for (int j = len_b - 1; j >= 0; --j) {
            int pos = i + j + 1;
            int sum = ans[pos] + (a[i] - '0') * (b[j] - '0');

            ans[pos] = sum % 10;
            ans[pos - 1] += sum / 10;
        }
    }

    while (start < len_a + len_b && ans[start] == 0) {
        ++start;
    }
    for (int i = start; i < len_a + len_b; ++i) {
        putchar((char)('0' + ans[i]));
    }
    putchar('\n');

    return 0;
}
