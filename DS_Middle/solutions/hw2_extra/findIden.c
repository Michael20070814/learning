#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_VAR 10
#define MAX_NAME 32
#define MAX_LINE 512

static int find_var(char vars[][MAX_NAME], int count, const char *name)
{
    for (int i = 0; i < count; ++i) {
        if (strcmp(vars[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

int main(void)
{
    FILE *fp = fopen("int.c", "r");
    char vars[MAX_VAR][MAX_NAME];
    int used[MAX_VAR] = {0};
    int var_count = 0;
    char line[MAX_LINE];

    if (fp == NULL) {
        return 0;
    }

    /*
     * The declaration is guaranteed to be on one line and to use int only.
     * Collect alphabetic words after the int keyword until the semicolon.
     */
    while (fgets(line, sizeof(line), fp) != NULL) {
        char *p = strstr(line, "int");

        if (p != NULL) {
            p += 3;
            while (*p != '\0' && *p != ';') {
                if (isalpha((unsigned char)*p)) {
                    int len = 0;

                    while (isalpha((unsigned char)*p)) {
                        if (len < MAX_NAME - 1) {
                            vars[var_count][len++] = *p;
                        }
                        ++p;
                    }
                    vars[var_count][len] = '\0';
                    ++var_count;
                } else {
                    ++p;
                }
            }
            break;
        }
    }

    {
        int c;
        char word[MAX_NAME];
        int len = 0;

        while ((c = fgetc(fp)) != EOF) {
            if (isalpha((unsigned char)c)) {
                if (len < MAX_NAME - 1) {
                    word[len++] = (char)c;
                }
            } else if (len > 0) {
                int idx;

                word[len] = '\0';
                idx = find_var(vars, var_count, word);
                if (idx >= 0) {
                    used[idx] = 1;
                }
                len = 0;
            }
        }
        if (len > 0) {
            int idx;

            word[len] = '\0';
            idx = find_var(vars, var_count, word);
            if (idx >= 0) {
                used[idx] = 1;
            }
        }
    }

    fclose(fp);

    for (int i = 0; i < var_count; ++i) {
        if (!used[i]) {
            printf("%s\n", vars[i]);
        }
    }

    return 0;
}
