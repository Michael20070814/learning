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
    Node *current = NULL;
    Node *tail = NULL;
    int n;
    int count;

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        int x;
        Node *node;

        scanf("%d", &x);
        node = new_node(x);
        if (node == NULL) {
            return 0;
        }
        if (current == NULL) {
            current = tail = node;
            node->next = node;
        } else {
            node->next = current;
            tail->next = node;
            tail = node;
        }
    }

    count = n;
    while (count > 0) {
        Node *min_node = current;
        Node *prev_min = NULL;
        Node *prev = NULL;
        Node *p = current;

        /* Find the minimum while remembering the node before it. */
        for (int i = 0; i < count; ++i) {
            if (p->value < min_node->value) {
                min_node = p;
                prev_min = prev;
            }
            prev = p;
            p = p->next;
        }
        if (prev_min == NULL) {
            prev_min = prev;
        }

        /* Print the clockwise path from current to the selected minimum. */
        p = current;
        while (1) {
            printf("%d ", p->value);
            if (p == min_node) {
                break;
            }
            p = p->next;
        }
        putchar('\n');

        if (count == 1) {
            free(min_node);
            current = NULL;
        } else {
            current = min_node->next;
            prev_min->next = min_node->next;
            free(min_node);
        }
        --count;
    }

    return 0;
}
