#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 128

typedef struct WordNode {
    char word[MAX_WORD];
    int count;
    struct WordNode *next;
} WordNode;

static void add_word(WordNode **head, const char *word)
{
    WordNode **pos = head;
    WordNode *node;

    while (*pos != NULL && strcmp((*pos)->word, word) < 0) {
        pos = &(*pos)->next;
    }

    if (*pos != NULL && strcmp((*pos)->word, word) == 0) {
        ++(*pos)->count;
        return;
    }

    node = (WordNode *)malloc(sizeof(WordNode));
    if (node == NULL) {
        return;
    }
    strcpy(node->word, word);
    node->count = 1;
    node->next = *pos;
    *pos = node;
}

int main(void)
{
    FILE *fp = fopen("article.txt", "r");
    WordNode *head = NULL;
    char word[MAX_WORD];
    int len = 0;
    int c;

    if (fp == NULL) {
        return 0;
    }

    while ((c = fgetc(fp)) != EOF) {
        if (isalpha((unsigned char)c)) {
            if (len < MAX_WORD - 1) {
                word[len++] = (char)tolower((unsigned char)c);
            }
        } else if (len > 0) {
            word[len] = '\0';
            add_word(&head, word);
            len = 0;
        }
    }
    if (len > 0) {
        word[len] = '\0';
        add_word(&head, word);
    }

    fclose(fp);

    while (head != NULL) {
        WordNode *next = head->next;

        printf("%s %d\n", head->word, head->count);
        free(head);
        head = next;
    }

    return 0;
}
