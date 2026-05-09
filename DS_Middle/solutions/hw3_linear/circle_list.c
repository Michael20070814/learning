#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static Node *new_node(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));

    if (node != NULL) {
        node->value = value;
        node->next = NULL;
    }
    return node;
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    Node *current;
    Node *prev;
    int count = 0;
    int x;
    int first = 1;

    while (scanf("%d", &x) == 1 && x != -1) {
        Node *node = new_node(x);

        if (node == NULL) {
            return 0;
        }
        if (head == NULL) {
            head = tail = node;
            node->next = node;
        } else {
            node->next = head;
            tail->next = node;
            tail = node;
        }
        ++count;
    }

    current = head;
    prev = tail;
    while (count > 0) {
        Node *del = current;
        Node *next = current->next;

        if (!first) {
            putchar(' ');
        }
        printf("%d", del->value);
        first = 0;

        prev->next = next;
        free(del);
        --count;

        if (count == 0) {
            break;
        }
        if (count == 1) {
            current = next;
        } else {
            /* Skip exactly one live node, then visit the following node. */
            prev = next;
            current = next->next;
        }
    }
    putchar('\n');

    return 0;
}
