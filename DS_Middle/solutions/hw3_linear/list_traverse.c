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

static void print_with_commas(int value)
{
    char raw[32];
    int len;
    int first_group;

    sprintf(raw, "%d", value);
    len = 0;
    while (raw[len] != '\0') {
        ++len;
    }

    first_group = len % 3;
    if (first_group == 0) {
        first_group = 3;
    }

    for (int i = 0; i < len; ++i) {
        if (i > 0 && (i - first_group) % 3 == 0) {
            putchar(',');
        }
        putchar(raw[i]);
    }
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    int x;
    int first = 1;

    while (scanf("%d", &x) == 1 && x != -1) {
        Node *node = new_node(x);

        if (node == NULL) {
            return 0;
        }
        if (head == NULL) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    /*
     * Visit from head to tail, print each value, and free the node
     * immediately after it is no longer needed.
     */
    while (head != NULL) {
        Node *next = head->next;

        if (!first) {
            putchar(' ');
        }
        print_with_commas(head->value);
        first = 0;
        free(head);
        head = next;
    }
    putchar('\n');

    return 0;
}
