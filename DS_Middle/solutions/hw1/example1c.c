#include <ctype.h>
#include <stdio.h>

int main(void)
{
    long long result = 0;
    long long term = 0;
    char op = '+';
    int c;

    while (1) {
        long long num = 0;

        do {
            c = getchar();
        } while (isspace((unsigned char)c));

        while (isdigit((unsigned char)c)) {
            num = num * 10 + (c - '0');
            c = getchar();
        }

        /*
         * result stores finished additive terms. term stores the current
         * multiplication/division chain so operator precedence is preserved.
         */
        if (op == '+') {
            result += term;
            term = num;
        } else if (op == '-') {
            result += term;
            term = -num;
        } else if (op == '*') {
            term *= num;
        } else if (op == '/') {
            term /= num;
        }

        while (isspace((unsigned char)c)) {
            c = getchar();
        }
        if (c == '=') {
            break;
        }
        op = (char)c;
    }

    result += term;
    printf("%lld\n", result);
    return 0;
}
