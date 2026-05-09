#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATTERN 32
#define MAX_REPLACE 32

typedef struct Token {
    int is_set;
    char chars[MAX_PATTERN];
} Token;

static int parse_pattern(const char *pattern, Token tokens[])
{
    int count = 0;

    for (int i = 0; pattern[i] != '\0'; ++i) {
        if (pattern[i] == '[') {
            int len = 0;

            tokens[count].is_set = 1;
            ++i;
            while (pattern[i] != '\0' && pattern[i] != ']') {
                tokens[count].chars[len++] = pattern[i++];
            }
            tokens[count].chars[len] = '\0';
            ++count;
        } else {
            tokens[count].is_set = 0;
            tokens[count].chars[0] = pattern[i];
            tokens[count].chars[1] = '\0';
            ++count;
        }
    }

    return count;
}

static int char_equal_ignore_case(char a, char b)
{
    return tolower((unsigned char)a) == tolower((unsigned char)b);
}

static int token_match(Token *token, char c)
{
    if (!token->is_set) {
        return char_equal_ignore_case(token->chars[0], c);
    }

    for (int i = 0; token->chars[i] != '\0'; ++i) {
        if (char_equal_ignore_case(token->chars[i], c)) {
            return 1;
        }
    }
    return 0;
}

static int match_at(const char *text, int pos, Token tokens[], int token_count)
{
    for (int i = 0; i < token_count; ++i) {
        if (text[pos + i] == '\0' || !token_match(&tokens[i], text[pos + i])) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    char pattern[MAX_PATTERN];
    char replacement[MAX_REPLACE];
    Token tokens[MAX_PATTERN];
    int token_count;
    char *text = NULL;
    int cap = 1024;
    int len = 0;
    int c;

    if (fgets(pattern, sizeof(pattern), stdin) == NULL) {
        return 0;
    }
    if (fgets(replacement, sizeof(replacement), stdin) == NULL) {
        return 0;
    }
    pattern[strcspn(pattern, "\r\n")] = '\0';
    replacement[strcspn(replacement, "\r\n")] = '\0';
    token_count = parse_pattern(pattern, tokens);

    text = (char *)malloc((size_t)cap);
    if (text == NULL) {
        return 0;
    }

    while ((c = getchar()) != EOF) {
        if (len + 2 >= cap) {
            char *bigger;

            cap *= 2;
            bigger = (char *)realloc(text, (size_t)cap);
            if (bigger == NULL) {
                free(text);
                return 0;
            }
            text = bigger;
        }
        text[len++] = (char)c;
    }
    text[len] = '\0';

    for (int i = 0; i < len;) {
        if (match_at(text, i, tokens, token_count)) {
            fputs(replacement, stdout);
            i += token_count;
        } else {
            putchar(text[i]);
            ++i;
        }
    }

    free(text);
    return 0;
}
