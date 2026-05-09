#include <stdio.h>
#include <string.h>

#define MAX_LEN 128

static void trim_tail_zero(char *s)
{
    int len = (int)strlen(s);

    while (len > 1 && s[len - 1] == '0') {
        s[--len] = '\0';
    }
}

int main(void)
{
    char input[MAX_LEN];
    char integer[MAX_LEN];
    char fraction[MAX_LEN];
    char digits[MAX_LEN * 2];
    char *dot;
    int exponent;
    int dlen = 0;

    if (scanf("%127s", input) != 1) {
        return 0;
    }

    dot = strchr(input, '.');
    strncpy(integer, input, (size_t)(dot - input));
    integer[dot - input] = '\0';
    strcpy(fraction, dot + 1);

    if (strcmp(integer, "0") != 0) {
        exponent = (int)strlen(integer) - 1;
        for (int i = 0; integer[i] != '\0'; ++i) {
            digits[dlen++] = integer[i];
        }
        for (int i = 0; fraction[i] != '\0'; ++i) {
            digits[dlen++] = fraction[i];
        }
    } else {
        int first = 0;

        while (fraction[first] == '0') {
            ++first;
        }
        if (fraction[first] == '\0') {
            printf("0e0\n");
            return 0;
        }
        exponent = -first - 1;
        for (int i = first; fraction[i] != '\0'; ++i) {
            digits[dlen++] = fraction[i];
        }
    }
    digits[dlen] = '\0';
    trim_tail_zero(digits);
    dlen = (int)strlen(digits);

    putchar(digits[0]);
    if (dlen > 1) {
        putchar('.');
        fputs(digits + 1, stdout);
    }
    printf("e%d\n", exponent);

    return 0;
}
