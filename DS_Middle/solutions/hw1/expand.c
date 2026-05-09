#include <stdio.h>
#include <string.h>

#define MAX_LEN 1024

static int same_expand_class(char a, char b)
{
    return ((a >= 'a' && a <= 'z' && b >= 'a' && b <= 'z') ||
            (a >= 'A' && a <= 'Z' && b >= 'A' && b <= 'Z') ||
            (a >= '0' && a <= '9' && b >= '0' && b <= '9'));
}

int main(void)
{
    char s[MAX_LEN];
    int len;

    if (fgets(s, sizeof(s), stdin) == NULL) {
        return 0;
    }
    s[strcspn(s, "\r\n")] = '\0';
    len = (int)strlen(s);

    for (int i = 0; i < len; ++i) {
        if (s[i] == '-' && i > 0 && i + 1 < len &&
            same_expand_class(s[i - 1], s[i + 1]) && s[i + 1] > s[i - 1]) {
            /*
             * The left endpoint has already been printed, so print only
             * the missing middle characters plus the right endpoint.
             */
            for (char ch = (char)(s[i - 1] + 1); ch <= s[i + 1]; ++ch) {
                putchar(ch);
            }
            ++i;        /* Skip the right endpoint from the original string. */
        } else {
            putchar(s[i]);
        }
    }
    putchar('\n');

    return 0;
}
