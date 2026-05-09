#include <stdio.h>
#include <string.h>

#define FIRST_VISIBLE 32
#define LAST_VISIBLE 126
#define VISIBLE_COUNT 95

int main(void)
{
    char key[128];
    char ring[VISIBLE_COUNT];
    char cipher[128] = {0};
    int used[128] = {0};
    int len = 0;
    char first_plain;
    FILE *in;
    FILE *out;
    int ch;

    if (fgets(key, sizeof(key), stdin) == NULL) {
        return 0;
    }
    key[strcspn(key, "\r\n")] = '\0';

    /* Build the initial ring: deduplicated key first, then other visibles. */
    for (int i = 0; key[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)key[i];

        if (c >= FIRST_VISIBLE && c <= LAST_VISIBLE && !used[c]) {
            used[c] = 1;
            ring[len++] = (char)c;
        }
    }
    for (int c = FIRST_VISIBLE; c <= LAST_VISIBLE; ++c) {
        if (!used[c]) {
            ring[len++] = (char)c;
        }
    }

    first_plain = ring[0];

    /*
     * Josephus-like deletion. The deleted character is plaintext, and the
     * character landed on after moving is its ciphertext.
     */
    for (int idx = 0; len > 1;) {
        unsigned char plain = (unsigned char)ring[idx];
        int step;
        int target;

        for (int j = idx; j < len - 1; ++j) {
            ring[j] = ring[j + 1];
        }
        --len;
        if (idx == len) {
            idx = 0;
        }

        step = (int)plain;
        target = (idx + step - 1) % len;
        cipher[plain] = ring[target];
        idx = target;
    }
    cipher[(unsigned char)ring[0]] = first_plain;

    in = fopen("in.txt", "rb");
    out = fopen("in_crpyt.txt", "wb");
    if (in == NULL || out == NULL) {
        if (in != NULL) {
            fclose(in);
        }
        if (out != NULL) {
            fclose(out);
        }
        return 0;
    }

    while ((ch = fgetc(in)) != EOF) {
        if (ch >= FIRST_VISIBLE && ch <= LAST_VISIBLE) {
            fputc(cipher[ch], out);
        } else {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
