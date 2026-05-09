#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 128

static int equal_ignore_case(const char *text, const char *pattern, int len)
{
    for (int i = 0; i < len; ++i) {
        if (tolower((unsigned char)text[i]) !=
            tolower((unsigned char)pattern[i])) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    char old_word[MAX_WORD];
    char new_word[MAX_WORD];
    FILE *in;
    FILE *out;
    char *text = NULL;
    int cap = 1024;
    int len = 0;
    int c;
    int old_len;

    if (fgets(old_word, sizeof(old_word), stdin) == NULL) {
        return 0;
    }
    if (fgets(new_word, sizeof(new_word), stdin) == NULL) {
        return 0;
    }
    old_word[strcspn(old_word, "\r\n")] = '\0';
    new_word[strcspn(new_word, "\r\n")] = '\0';
    old_len = (int)strlen(old_word);

    in = fopen("filein.txt", "rb");
    out = fopen("fileout.txt", "wb");
    if (in == NULL || out == NULL || old_len == 0) {
        if (in != NULL) {
            fclose(in);
        }
        if (out != NULL) {
            fclose(out);
        }
        return 0;
    }

    text = (char *)malloc((size_t)cap);
    if (text == NULL) {
        fclose(in);
        fclose(out);
        return 0;
    }
    while ((c = fgetc(in)) != EOF) {
        if (len + 2 >= cap) {
            char *bigger;

            cap *= 2;
            bigger = (char *)realloc(text, (size_t)cap);
            if (bigger == NULL) {
                free(text);
                fclose(in);
                fclose(out);
                return 0;
            }
            text = bigger;
        }
        text[len++] = (char)c;
    }
    text[len] = '\0';

    for (int i = 0; i < len;) {
        if (i + old_len <= len && equal_ignore_case(text + i, old_word, old_len)) {
            fputs(new_word, out);
            i += old_len;
        } else {
            fputc(text[i], out);
            ++i;
        }
    }

    free(text);
    fclose(in);
    fclose(out);
    return 0;
}
