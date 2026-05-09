#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMS 1000
#define MAX_LINE 20000

typedef struct InputTerm {
    long long coef;
    long long exp;
} InputTerm;

typedef struct Term {
    long long coef;
    long long exp;
    struct Term *next;
} Term;

static int read_poly(InputTerm poly[])
{
    char line[MAX_LINE];
    char *tok;
    int count = 0;

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }

    tok = strtok(line, " \t\r\n");
    while (tok != NULL) {
        long long coef = atoll(tok);

        tok = strtok(NULL, " \t\r\n");
        if (tok == NULL) {
            break;
        }
        poly[count].coef = coef;
        poly[count].exp = atoll(tok);
        ++count;
        tok = strtok(NULL, " \t\r\n");
    }

    return count;
}

static void add_term(Term **head, long long coef, long long exp)
{
    Term **pos = head;
    Term *node;

    if (coef == 0) {
        return;
    }

    while (*pos != NULL && (*pos)->exp > exp) {
        pos = &(*pos)->next;
    }

    if (*pos != NULL && (*pos)->exp == exp) {
        (*pos)->coef += coef;
        if ((*pos)->coef == 0) {
            Term *del = *pos;
            *pos = del->next;
            free(del);
        }
        return;
    }

    node = (Term *)malloc(sizeof(Term));
    if (node == NULL) {
        return;
    }
    node->coef = coef;
    node->exp = exp;
    node->next = *pos;
    *pos = node;
}

static void free_poly(Term *head)
{
    while (head != NULL) {
        Term *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    InputTerm a[MAX_TERMS];
    InputTerm b[MAX_TERMS];
    Term *result = NULL;
    int na;
    int nb;
    int first = 1;

    na = read_poly(a);
    nb = read_poly(b);

    /*
     * Multiply every pair of terms and insert the product into a descending
     * exponent list, merging equal exponents on the fly.
     */
    for (int i = 0; i < na; ++i) {
        for (int j = 0; j < nb; ++j) {
            add_term(&result, a[i].coef * b[j].coef, a[i].exp + b[j].exp);
        }
    }

    for (Term *p = result; p != NULL; p = p->next) {
        if (!first) {
            putchar(' ');
        }
        printf("%lld %lld", p->coef, p->exp);
        first = 0;
    }
    putchar('\n');

    free_poly(result);
    return 0;
}
