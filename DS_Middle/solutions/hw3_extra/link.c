#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    int count;
    struct Node *next;
} Node;

static Node *new_node(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));

    if (node != NULL) {
        node->value = value;
        node->count = 1;
        node->next = NULL;
    }
    return node;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    long long comparisons = 0;
    int n;

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        int x;
        Node *prev = NULL;
        Node *cur = head;

        scanf("%d", &x);

        /*
         * Each visited node contributes one integer comparison. If found,
         * move the node to the head to improve later searches.
         */
        while (cur != NULL) {
            ++comparisons;
            if (cur->value == x) {
                break;
            }
            prev = cur;
            cur = cur->next;
        }

        if (cur == NULL) {
            Node *node = new_node(x);

            if (node == NULL) {
                continue;
            }
            if (head == NULL) {
                head = tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        } else {
            ++cur->count;
            if (prev != NULL) {
                prev->next = cur->next;
                if (tail == cur) {
                    tail = prev;
                }
                cur->next = head;
                head = cur;
            }
        }
    }

    printf("%lld\n", comparisons);
    for (Node *p = head, *next; p != NULL && n > 0; p = next) {
        static int printed = 0;

        next = p->next;
        if (printed < 5) {
            printf("%d %d\n", p->value, p->count);
            ++printed;
        }
    }

    free_list(head);
    return 0;
}
