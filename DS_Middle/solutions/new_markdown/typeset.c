#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 256

/*
 * Copy words from src to dst, removing extra spaces and tabs.
 * A word is any consecutive sequence except spaces and horizontal tabs.
 */
static void normalize_words(const char *src, char *dst)
{
    int out = 0;
    int need_space = 0;
    int i = 0;

    while (src[i] != '\0') {
        while (src[i] == ' ' || src[i] == '\t') {
            ++i;
        }
        if (src[i] == '\0' || src[i] == '\n' || src[i] == '\r') {
            break;
        }

        if (need_space) {
            dst[out++] = ' ';
        }
        while (src[i] != '\0' && src[i] != '\n' && src[i] != '\r' &&
               src[i] != ' ' && src[i] != '\t') {
            dst[out++] = src[i++];
        }
        need_space = 1;
    }

    dst[out] = '\0';
}

int main(void)
{
    int colon_pos;
    char line[MAX_LINE];

    if (scanf("%d", &colon_pos) != 1) {
        return 0;
    }

    /* Remove the rest of the first line before reading records. */
    fgets(line, sizeof(line), stdin);

    while (fgets(line, sizeof(line), stdin) != NULL) {
        char *colon = strchr(line, ':');
        char left_raw[MAX_LINE];
        char right_raw[MAX_LINE];
        char left[MAX_LINE];
        char right[MAX_LINE];
        int left_len;
        int blanks;

        if (colon == NULL) {
            printf("%s", line);
            if (strchr(line, '\n') == NULL) {
                putchar('\n');
            }
            continue;
        }

        *colon = '\0';
        strcpy(left_raw, line);
        strcpy(right_raw, colon + 1);

        normalize_words(left_raw, left);
        normalize_words(right_raw, right);

        /*
         * The colon is fixed at column colon_pos (1-based).
         * There must be one blank immediately before the colon.
         */
        left_len = (int)strlen(left);
        blanks = colon_pos - left_len - 2;
        while (blanks-- > 0) {
            putchar(' ');
        }
        printf("%s : %s\n", left, right);
    }

    return 0;
}
