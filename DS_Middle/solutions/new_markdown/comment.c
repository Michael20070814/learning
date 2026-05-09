#include <stdio.h>

/* Count only block comments.
 * The two delimiter pairs themselves are not counted as comment text,
 * but all characters in the file are counted in the denominator.
 */
int main(void)
{
    FILE *fp = fopen("filein.c", "r");
    long total = 0;
    long comment = 0;
    int state = 0;
    int c;

    if (fp == NULL) {
        return 0;
    }

    while ((c = fgetc(fp)) != EOF) {
        ++total;

        // 处理多行与单行注释
        if (state == 0) {
            if (c == '/') {
                state = 1;
            }
        } else if (state == 1) {
            if (c == '*') {
                state = 2;
            } else if (c != '/') {
                state = 0;
            }
        } else if (state == 2) {
            if (c == '*') {
                state = 3;      /* The star might be the end delimiter. */
            } else {
                ++comment;
            }
        } else {
            if (c == '/') {
                state = 0;      /* End delimiter; do not count '*' or '/'. */
            } else {
                ++comment;      /* The previous '*' was just comment text. */
                if (c == '*') {
                    state = 3;
                } else {
                    ++comment;
                    state = 2;
                }
            }
        }
    }

    fclose(fp);
    printf("%ld%%\n", total == 0 ? 0 : comment * 100 / total);
    return 0;
}
