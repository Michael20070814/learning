#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REFS 100
#define MAX_LINE 600
#define MAX_AUTHORS 30
#define MAX_AUTHOR 80

typedef struct Reference {
    char authors[MAX_LINE];
    char first_author[MAX_AUTHOR];
    char title[MAX_LINE];
    char proceedings[MAX_LINE];
    int year;
    int order;
} Reference;

static void trim_in_place(char *s)
{
    int start = 0;
    int end;

    while (isspace((unsigned char)s[start])) {
        ++start;
    }
    if (start > 0) {
        memmove(s, s + start, strlen(s + start) + 1);
    }

    end = (int)strlen(s) - 1;
    while (end >= 0 && isspace((unsigned char)s[end])) {
        s[end--] = '\0';
    }
}

static void strip_final_period(char *s)
{
    int len;

    trim_in_place(s);
    len = (int)strlen(s);
    if (len > 0 && s[len - 1] == '.') {
        s[len - 1] = '\0';
        trim_in_place(s);
    }
}

static void normalize_person_name(const char *src, char *dst)
{
    int out = 0;
    int new_word = 1;
    int last_space = 1;

    for (int i = 0; src[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)src[i];

        if (isspace(c)) {
            if (!last_space && out > 0) {
                dst[out++] = ' ';
                last_space = 1;
            }
            new_word = 1;
        } else {
            if (isalpha(c)) {
                dst[out++] = (char)(new_word ? toupper(c) : tolower(c));
                new_word = 0;
            } else {
                dst[out++] = (char)c;
                new_word = 1;   /* Hyphen starts a new alphabetic part. */
            }
            last_space = 0;
        }
    }

    if (out > 0 && dst[out - 1] == ' ') {
        --out;
    }
    dst[out] = '\0';
}

static int is_standalone_and(const char *s, int i)
{
    int before_ok = (i == 0) || !isalpha((unsigned char)s[i - 1]);
    int after_ok;

    if (s[i + 1] == '\0' || s[i + 2] == '\0') {
        return 0;
    }
    after_ok = !isalpha((unsigned char)s[i + 3]);

    return before_ok && after_ok &&
           tolower((unsigned char)s[i]) == 'a' &&
           tolower((unsigned char)s[i + 1]) == 'n' &&
           tolower((unsigned char)s[i + 2]) == 'd';
}

static void normalize_authors(const char *src, char *authors, char *first_author)
{
    char separated[MAX_LINE];
    char people[MAX_AUTHORS][MAX_AUTHOR];
    int sep_len = 0;
    int people_count = 0;
    char *tok;

    /*
     * Treat a standalone "and" like a comma first, then split uniformly.
     * This handles both "A, B and C" and "A,B,C" input forms.
     */
    for (int i = 0; src[i] != '\0'; ++i) {
        if (is_standalone_and(src, i)) {
            separated[sep_len++] = ',';
            i += 2;
        } else {
            separated[sep_len++] = src[i];
        }
    }
    separated[sep_len] = '\0';

    tok = strtok(separated, ",");
    while (tok != NULL && people_count < MAX_AUTHORS) {
        char name[MAX_AUTHOR];

        strncpy(name, tok, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        trim_in_place(name);
        if (name[0] != '\0') {
            normalize_person_name(name, people[people_count]);
            ++people_count;
        }
        tok = strtok(NULL, ",");
    }

    authors[0] = '\0';
    for (int i = 0; i < people_count; ++i) {
        if (i > 0) {
            if (i == people_count - 1) {
                strcat(authors, " and ");
            } else {
                strcat(authors, ", ");
            }
        }
        strcat(authors, people[i]);
    }

    if (people_count > 0) {
        strcpy(first_author, people[0]);
    } else {
        first_author[0] = '\0';
    }
}

static void copy_part(char *dst, const char *begin, const char *end)
{
    int len = (int)(end - begin);

    strncpy(dst, begin, len);
    dst[len] = '\0';
    trim_in_place(dst);
}

static int parse_reference(const char *line, Reference *ref, int order)
{
    const char *p1 = strchr(line, '.');
    const char *p2;
    const char *p3;
    char author_part[MAX_LINE];
    char year_part[32];

    if (p1 == NULL) {
        return 0;
    }
    p2 = strchr(p1 + 1, '.');
    if (p2 == NULL) {
        return 0;
    }
    p3 = strchr(p2 + 1, '.');
    if (p3 == NULL) {
        return 0;
    }

    copy_part(author_part, line, p1);
    copy_part(year_part, p1 + 1, p2);
    copy_part(ref->title, p2 + 1, p3);
    strcpy(ref->proceedings, p3 + 1);
    strip_final_period(ref->proceedings);

    if (ref->title[0] != '\0') {
        ref->title[0] = (char)toupper((unsigned char)ref->title[0]);
    }
    normalize_authors(author_part, ref->authors, ref->first_author);
    ref->year = atoi(year_part);
    ref->order = order;
    return 1;
}

static int cmp_ref(const void *a, const void *b)
{
    const Reference *ra = (const Reference *)a;
    const Reference *rb = (const Reference *)b;
    int c;

    if (ra->year != rb->year) {
        return rb->year - ra->year;
    }
    c = strcmp(ra->first_author, rb->first_author);
    if (c != 0) {
        return c;
    }
    return ra->order - rb->order;
}

int main(void)
{
    Reference refs[MAX_REFS];
    char line[MAX_LINE];
    int count = 0;

    while (count < MAX_REFS && fgets(line, sizeof(line), stdin) != NULL) {
        char tmp[MAX_LINE];

        strcpy(tmp, line);
        trim_in_place(tmp);
        if (tmp[0] == '\0') {
            continue;
        }
        if (parse_reference(tmp, &refs[count], count)) {
            ++count;
        }
    }

    qsort(refs, count, sizeof(refs[0]), cmp_ref);

    for (int i = 0; i < count; ++i) {
        printf("[%d] %s. %d. %s. %s.\n", i + 1, refs[i].authors,
               refs[i].year, refs[i].title, refs[i].proceedings);
    }

    return 0;
}
