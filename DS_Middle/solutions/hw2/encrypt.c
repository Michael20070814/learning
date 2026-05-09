#include <stdio.h>
#include <string.h>

#define ALPHA 26

int main(void)
{
    char key[64];
    char table[ALPHA + 1];
    int used[ALPHA] = {0};
    int len = 0;
    FILE *in;
    FILE *out;
    int c;

    if (scanf("%63s", key) != 1) {
        return 0;
    }

    /* Deduplicated key first. */
    for (int i = 0; key[i] != '\0'; ++i) {
        int idx = key[i] - 'a';

        if (idx >= 0 && idx < ALPHA && !used[idx]) {
            used[idx] = 1;
            table[len++] = key[i];
        }
    }

    /* Then append unused letters from z to a. */
    for (char ch = 'z'; ch >= 'a'; --ch) {
        int idx = ch - 'a';

        if (!used[idx]) {
            table[len++] = ch;
        }
    }
    table[len] = '\0';

    in = fopen("encrypt.txt", "rb");
    out = fopen("output.txt", "wb");
    if (in == NULL || out == NULL) {
        if (in != NULL) {
            fclose(in);
        }
        if (out != NULL) {
            fclose(out);
        }
        return 0;
    }

    while ((c = fgetc(in)) != EOF) {
        if (c >= 'a' && c <= 'z') {
            fputc(table[c - 'a'], out);
        } else {
            fputc(c, out);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
