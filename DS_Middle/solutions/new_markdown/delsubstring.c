#include <stdio.h>
#include <string.h>

#define MAX_LEN 10000

static void strip_newline(char *s)
{
    size_t len = strlen(s);

    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
}

int main(void)
{
    char src[MAX_LEN + 1];
    char sub[MAX_LEN + 1];
    char out[MAX_LEN + 1];
    int top = 0;
    int sub_len;

    if (fgets(src, sizeof(src), stdin) == NULL) {
        return 0;
    }
    if (fgets(sub, sizeof(sub), stdin) == NULL) {
        return 0;
    }

    strip_newline(src);
    strip_newline(sub);
    sub_len = (int)strlen(sub);

    if (sub_len == 0) {
        printf("%s\n", src);
        return 0;
    }

    /*
     * Use the output buffer as a stack. Whenever its suffix equals the
     * substring, remove that suffix so newly formed matches are handled too.
     */
    for (int i = 0; src[i] != '\0'; ++i) {
        out[top++] = src[i];
        out[top] = '\0';
        if (top >= sub_len && strncmp(out + top - sub_len, sub, sub_len) == 0) {
            top -= sub_len;
            out[top] = '\0';
        }
    }

    printf("%s\n", out);
    return 0;
}
