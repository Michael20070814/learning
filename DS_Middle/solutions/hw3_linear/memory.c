#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int start;
    int length;
    struct Block *next;
} Block;

static Block *new_block(int start, int length)
{
    Block *block = (Block *)malloc(sizeof(Block));

    if (block != NULL) {
        block->start = start;
        block->length = length;
        block->next = NULL;
    }
    return block;
}

static Block *previous_of(Block *current)
{
    Block *p = current;

    while (p->next != current) {
        p = p->next;
    }
    return p;
}

int main(void)
{
    Block *current = NULL;
    Block *tail = NULL;
    int count;
    int req;

    if (scanf("%d", &count) != 1) {
        return 0;
    }

    for (int i = 0; i < count; ++i) {
        int start;
        int length;
        Block *block;

        scanf("%d%d", &start, &length);
        block = new_block(start, length);
        if (block == NULL) {
            return 0;
        }
        if (current == NULL) {
            current = tail = block;
            block->next = block;
        } else {
            block->next = current;
            tail->next = block;
            tail = block;
        }
    }

    while (scanf("%d", &req) == 1 && req != -1) {
        Block *best = NULL;
        Block *best_prev = NULL;
        Block *prev;
        Block *p;
        int best_len = 0;

        if (current == NULL) {
            continue;
        }

        prev = previous_of(current);
        p = current;
        for (int i = 0; i < count; ++i) {
            if (p->length >= req && (best == NULL || p->length < best_len)) {
                best = p;
                best_prev = prev;
                best_len = p->length;
            }
            prev = p;
            p = p->next;
        }

        if (best == NULL) {
            continue;
        }

        if (best->length == req) {
            if (count == 1) {
                free(best);
                current = NULL;
                count = 0;
            } else {
                best_prev->next = best->next;
                current = best->next;
                free(best);
                --count;
            }
        } else {
            best->length -= req;
            current = best;
        }
    }

    if (current != NULL) {
        Block *p = current;

        for (int i = 0; i < count; ++i) {
            printf("%d %d\n", p->start, p->length);
            p = p->next;
        }

        while (count-- > 0) {
            Block *next = current->next;
            free(current);
            current = next;
        }
    }

    return 0;
}
