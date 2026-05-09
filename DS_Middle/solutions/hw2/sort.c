#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_NAME 32
#define PHONE_LEN 16

typedef struct Entry {
    char original[MAX_NAME];
    char name[MAX_NAME];
    char phone[PHONE_LEN];
} Entry;

static int same_original_pair(const Entry *e, const char *name, const char *phone)
{
    return strcmp(e->original, name) == 0 && strcmp(e->phone, phone) == 0;
}

static int cmp_entry(const void *a, const void *b)
{
    const Entry *ea = (const Entry *)a;
    const Entry *eb = (const Entry *)b;

    return strcmp(ea->name, eb->name);
}

int main(void)
{
    Entry entries[MAX_ITEMS];
    int n;
    int count = 0;

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        char name[MAX_NAME];
        char phone[PHONE_LEN];
        int duplicate = 0;
        int same_name_count = 0;

        scanf("%31s%15s", name, phone);

        /*
         * Exact duplicates are discarded before renaming. Name collisions
         * with different phones receive suffixes in first-appearance order.
         */
        for (int j = 0; j < count; ++j) {
            if (same_original_pair(&entries[j], name, phone)) {
                duplicate = 1;
                break;
            }
            if (strcmp(entries[j].original, name) == 0) {
                ++same_name_count;
            }
        }
        if (duplicate) {
            continue;
        }

        strcpy(entries[count].original, name);
        strcpy(entries[count].phone, phone);
        if (same_name_count == 0) {
            strcpy(entries[count].name, name);
        } else {
            sprintf(entries[count].name, "%s_%d", name, same_name_count);
        }
        ++count;
    }

    qsort(entries, count, sizeof(entries[0]), cmp_entry);

    for (int i = 0; i < count; ++i) {
        printf("%s %s\n", entries[i].name, entries[i].phone);
    }

    return 0;
}
