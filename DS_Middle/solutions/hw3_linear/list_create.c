#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int main(void)
{
    Node *head = NULL;
    int x;
    int first = 1;

    while (scanf("%d", &x) == 1 && x != -1) {
        Node *node = (Node *)malloc(sizeof(Node));

        if (node == NULL) {
            return 0;
        }
        /*
         * Head insertion reverses the input order naturally.
         * The newest number always becomes the first list node.
         */
        node->value = x;
        node->next = head;
        head = node;
    }

    while (head != NULL) {
        Node *next = head->next;

        if (!first) {
            putchar(' ');
        }
        printf("%d", head->value);
        first = 0;
        free(head);
        head = next;
    }
    putchar('\n');

    return 0;
}
