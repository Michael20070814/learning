#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 100

static char *skip_zero(char *s)
{
    while (*s == '0' && s[1] != '\0') {
        ++s;
    }
    return s;
}

static int compare_number(const char *a, const char *b)
{
    int la = (int)strlen(a);
    int lb = (int)strlen(b);

    if (la != lb) {
        return la > lb ? 1 : -1;
    }
    return strcmp(a, b);
}

static void subtract_abs(const char *big, const char *small, char *out)
{
    int i = (int)strlen(big) - 1;
    int j = (int)strlen(small) - 1;
    int borrow = 0;
    int top = 0;
    char rev[MAX_DIGITS];

    while (i >= 0 || j >= 0) {
        int x = (i >= 0 ? big[i] - '0' : 0) - borrow;
        int y = (j >= 0 ? small[j] - '0' : 0);

        if (x < y) {
            x += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        rev[top++] = (char)('0' + x - y);
        --i;
        --j;
    }

    while (top > 1 && rev[top - 1] == '0') {
        --top;
    }

    for (int k = 0; k < top; ++k) {
        out[k] = rev[top - 1 - k];
    }
    out[top] = '\0';
}

int main(void)
{
    char a_buf[MAX_DIGITS];
    char b_buf[MAX_DIGITS];
    char *a;
    char *b;
    char ans[MAX_DIGITS];
    int cmp;

    if (scanf("%99s%99s", a_buf, b_buf) != 2) {
        return 0;
    }

    a = skip_zero(a_buf);
    b = skip_zero(b_buf);
    cmp = compare_number(a, b);

    if (cmp == 0) {
        printf("0\n");
    } else if (cmp > 0) {
        subtract_abs(a, b, ans);
        printf("%s\n", ans);
    } else {
        subtract_abs(b, a, ans);
        printf("-%s\n", ans);
    }

    return 0;
}
