#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Sequential search: check every element from left to right. */
int sequential_search(int arr[], int n, int target)
{
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }

    return -1;
}

/* Binary search: halve the search range each step. Array must be sorted. */
int binary_search(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

/* Recursive binary search helper. */
static int binary_search_r(int arr[], int low, int high, int target)
{
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binary_search_r(arr, mid + 1, high, target);
    } else {
        return binary_search_r(arr, low, mid - 1, target);
    }
}

/* Binary search (recursive version). Array must be sorted. */
int binary_search_recursive(int arr[], int n, int target)
{
    return binary_search_r(arr, 0, n - 1, target);
}

/* Interpolation search: estimate position by value ratio. Array must be sorted. */
int interpolation_search(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (arr[high] == arr[low]) {
            if (arr[low] == target) {
                return low;
            }
            break;
        }

        int pos = low + (int)((long long)(target - arr[low]) * (high - low)
                              / (arr[high] - arr[low]));

        if (arr[pos] == target) {
            return pos;
        } else if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    return -1;
}

/* Jump search: skip ahead by fixed blocks, then do a linear scan. Array must be sorted. */
int jump_search(int arr[], int n, int target)
{
    int step = (int)sqrt((double)n);
    int prev = 0;

    while (arr[(step < n ? step : n) - 1] < target) {
        prev = step;
        step += (int)sqrt((double)n);

        if (prev >= n) {
            return -1;
        }
    }

    for (int i = prev; i < (step < n ? step : n); i++) {
        if (arr[i] == target) {
            return i;
        }
    }

    return -1;
}

/* Fibonacci search: narrow the range using Fibonacci numbers. Array must be sorted. */
int fibonacci_search(int arr[], int n, int target)
{
    int fib_prev2 = 0;
    int fib_prev1 = 1;
    int fib = fib_prev2 + fib_prev1;

    while (fib < n) {
        fib_prev2 = fib_prev1;
        fib_prev1 = fib;
        fib = fib_prev2 + fib_prev1;
    }

    int offset = -1;

    while (fib > 1) {
        int i = (offset + fib_prev2) < (n - 1) ? (offset + fib_prev2) : (n - 1);

        if (arr[i] < target) {
            fib = fib_prev1;
            fib_prev1 = fib_prev2;
            fib_prev2 = fib - fib_prev1;
            offset = i;
        } else if (arr[i] > target) {
            fib = fib_prev2;
            fib_prev1 = fib_prev1 - fib_prev2;
            fib_prev2 = fib - fib_prev1;
        } else {
            return i;
        }
    }

    if (fib_prev1 && (offset + 1) < n && arr[offset + 1] == target) {
        return offset + 1;
    }

    return -1;
}

/* Exponential search: find the range by doubling, then binary search within it. Array must be sorted. */
int exponential_search(int arr[], int n, int target)
{
    if (n == 0) {
        return -1;
    }

    if (arr[0] == target) {
        return 0;
    }

    int bound = 1;

    while (bound < n && arr[bound] <= target) {
        bound *= 2;
    }

    int low = bound / 2;
    int high = (bound < n) ? bound : (n - 1);

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

/* ---- Hash table search ---- */

#define HASH_SIZE 1009

typedef struct hash_node {
    int key;
    struct hash_node *next;
} hash_node_t;

typedef struct {
    hash_node_t *buckets[HASH_SIZE];
} hash_table_t;

static int hash_func(int key)
{
    return ((key % HASH_SIZE) + HASH_SIZE) % HASH_SIZE;
}

/* Create an empty hash table. */
hash_table_t *hash_table_create(void)
{
    hash_table_t *ht = (hash_table_t *)calloc(1, sizeof(hash_table_t));
    return ht;
}

/* Insert a key into the hash table. */
void hash_table_insert(hash_table_t *ht, int key)
{
    int index = hash_func(key);
    hash_node_t *node = (hash_node_t *)malloc(sizeof(hash_node_t));
    node->key = key;
    node->next = ht->buckets[index];
    ht->buckets[index] = node;
}

/* Search for a key in the hash table. Returns 1 if found, 0 otherwise. */
int hash_table_search(hash_table_t *ht, int key)
{
    int index = hash_func(key);
    hash_node_t *cur = ht->buckets[index];

    while (cur != NULL) {
        if (cur->key == key) {
            return 1;
        }
        cur = cur->next;
    }

    return 0;
}

/* Free all memory used by the hash table. */
void hash_table_destroy(hash_table_t *ht)
{
    for (int i = 0; i < HASH_SIZE; i++) {
        hash_node_t *cur = ht->buckets[i];

        while (cur != NULL) {
            hash_node_t *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }

    free(ht);
}

/* ---- Binary search tree ---- */

typedef struct bst_node {
    int key;
    struct bst_node *left;
    struct bst_node *right;
} bst_node_t;

/* Insert a key into the BST and return the new root. */
bst_node_t *bst_insert(bst_node_t *root, int key)
{
    if (root == NULL) {
        bst_node_t *node = (bst_node_t *)malloc(sizeof(bst_node_t));
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    if (key < root->key) {
        root->left = bst_insert(root->left, key);
    } else if (key > root->key) {
        root->right = bst_insert(root->right, key);
    }

    return root;
}

/* Search for a key in the BST. Returns the node if found, NULL otherwise. */
bst_node_t *bst_search(bst_node_t *root, int key)
{
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return bst_search(root->left, key);
    }

    return bst_search(root->right, key);
}

/* Free all nodes in the BST. */
void bst_destroy(bst_node_t *root)
{
    if (root == NULL) {
        return;
    }

    bst_destroy(root->left);
    bst_destroy(root->right);
    free(root);
}

/* Print an array. Used only by the optional demo below. */
static void print_array(const int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 * Optional demo:
 * Compile with -DSEARCH_DEMO to run this main function.
 * Example: gcc search_algorithms.c -DSEARCH_DEMO -lm -o search_demo
 */
#ifdef SEARCH_DEMO
int main(void)
{
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int target = 23;

    printf("Array: ");
    print_array(arr, n);
    printf("Target: %d\n\n", target);

    printf("Sequential search:    index %d\n", sequential_search(arr, n, target));
    printf("Binary search:        index %d\n", binary_search(arr, n, target));
    printf("Binary search (rec):  index %d\n", binary_search_recursive(arr, n, target));
    printf("Interpolation search: index %d\n", interpolation_search(arr, n, target));
    printf("Jump search:          index %d\n", jump_search(arr, n, target));
    printf("Fibonacci search:     index %d\n", fibonacci_search(arr, n, target));
    printf("Exponential search:   index %d\n", exponential_search(arr, n, target));

    /* Hash table demo */
    hash_table_t *ht = hash_table_create();
    for (int i = 0; i < n; i++) {
        hash_table_insert(ht, arr[i]);
    }
    printf("Hash table search:    %s\n", hash_table_search(ht, target) ? "found" : "not found");
    hash_table_destroy(ht);

    /* BST demo */
    bst_node_t *root = NULL;
    for (int i = 0; i < n; i++) {
        root = bst_insert(root, arr[i]);
    }
    printf("BST search:           %s\n", bst_search(root, target) ? "found" : "not found");
    bst_destroy(root);

    return 0;
}
#endif
