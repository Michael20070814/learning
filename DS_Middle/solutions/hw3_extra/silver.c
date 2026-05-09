#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int weight;
    struct Node *next;
} Node;

static Node *new_node(int weight)
{
    Node *node = (Node *)malloc(sizeof(Node));

    if (node != NULL) {
        node->weight = weight;
        node->next = NULL;
    }
    return node;
}

/* Keep the list sorted increasingly after every purchase or cut remainder. */
static void insert_sorted(Node **head, int weight)
{
    Node *node;
    Node **pos = head;

    if (weight <= 0) {
        return;
    }

    node = new_node(weight);
    if (node == NULL) {
        return;
    }

    while (*pos != NULL && (*pos)->weight <= weight) {
        pos = &(*pos)->next;
    }
    node->next = *pos;
    *pos = node;
}

static long long total_weight(Node *head)
{
    long long sum = 0;

    while (head != NULL) {
        sum += head->weight;
        head = head->next;
    }
    return sum;
}

static void sell_silver(Node **head, int amount)
{
    int need = amount;

    if (amount <= 0 || total_weight(*head) < amount) {
        return;
    }

    /*
     * Selling always takes blocks from the head. If the last taken block is
     * too large, put its remaining part back into the sorted list.
     */
    while (need > 0 && *head != NULL) {
        Node *first = *head;
        int left;

        *head = first->next;
        if (first->weight <= need) {
            need -= first->weight;
            free(first);
        } else {
            left = first->weight - need;
            free(first);
            need = 0;
            insert_sorted(head, left);
        }
    }
}

static void melt_small(Node **head)
{
    int sum = 0;

    /* Since the list is sorted, all blocks below 10 grams are at the front. */
    while (*head != NULL && (*head)->weight < 10) {
        Node *del = *head;

        sum += del->weight;
        *head = del->next;
        free(del);
    }

    if (sum > 0) {
        insert_sorted(head, sum);
    }
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
    int x;
    int first = 1;

    while (scanf("%d", &x) == 1 && x != 999999) {
        if (x > 0) {
            insert_sorted(&head, x);
        } else if (x < 0) {
            sell_silver(&head, -x);
        } else {
            melt_small(&head);
        }
    }

    for (Node *p = head; p != NULL; p = p->next) {
        if (!first) {
            putchar(' ');
        }
        printf("%d", p->weight);
        first = 0;
    }
    putchar('\n');

    free_list(head);
    return 0;
}
