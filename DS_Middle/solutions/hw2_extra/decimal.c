#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 128

static void trim_fraction_tail(char *s)
{
    char *dot = strchr(s, '.');
    int len;

    if (dot == NULL) {
        return;
    }

    len = (int)strlen(s);
    while (len > 0 && s[len - 1] == '0') {
        s[--len] = '\0';
    }
    if (len > 0 && s[len - 1] == '.') {
        s[--len] = '\0';
    }
}

int main(void)
{
    char input[MAX_LEN];
    char digits[MAX_LEN];
    char output[256];
    char *e_pos;
    int exp;
    int digit_len = 0;
    int frac_len = 0;
    int point;
    int out = 0;

    if (scanf("%127s", input) != 1) {
        return 0;
    }

    e_pos = strchr(input, 'e');
    if (e_pos == NULL) {
        e_pos = strchr(input, 'E');
    }
    exp = atoi(e_pos + 1);

    for (char *p = input; p < e_pos; ++p) {
        if (*p == '.') {
            frac_len = (int)(e_pos - p - 1);
        } else {
            digits[digit_len++] = *p;
        }
    }
    digits[digit_len] = '\0';

    point = digit_len - frac_len + exp;
    if (point <= 0) {
        output[out++] = '0';
        output[out++] = '.';
        for (int i = 0; i < -point; ++i) {
            output[out++] = '0';
        }
        for (int i = 0; i < digit_len; ++i) {
            output[out++] = digits[i];
        }
    } else if (point >= digit_len) {
        for (int i = 0; i < digit_len; ++i) {
            output[out++] = digits[i];
        }
        for (int i = 0; i < point - digit_len; ++i) {
            output[out++] = '0';
        }
    } else {
        for (int i = 0; i < point; ++i) {
            output[out++] = digits[i];
        }
        output[out++] = '.';
        for (int i = point; i < digit_len; ++i) {
            output[out++] = digits[i];
        }
    }
    output[out] = '\0';

    trim_fraction_tail(output);
    printf("%s\n", output);
    return 0;
}
