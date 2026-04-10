/**
 * list.c — 通用双向链表实现
 */

#include "list.h"

#include <stdlib.h>
#include <string.h>

/* ─────────────────── 内部辅助 ─────────────────── */

static ListNode *node_alloc(void *data)
{
    ListNode *n = malloc(sizeof(ListNode));
    if (!n) return NULL;
    n->data = data;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

/* 在 after 之后插入节点 n（after == NULL 表示插在 head 之前） */
static void link_after(List *list, ListNode *after, ListNode *n)
{
    if (after == NULL) {
        /* 插到链表最前 */
        n->next = list->head;
        n->prev = NULL;
        if (list->head) list->head->prev = n;
        list->head = n;
        if (list->tail == NULL) list->tail = n;
    } else {
        n->prev = after;
        n->next = after->next;
        if (after->next) after->next->prev = n;
        else             list->tail = n;
        after->next = n;
    }
    list->size++;
}

/* 从链表中摘除节点 n（不释放内存） */
static void unlink(List *list, ListNode *n)
{
    if (n->prev) n->prev->next = n->next;
    else         list->head    = n->next;

    if (n->next) n->next->prev = n->prev;
    else         list->tail    = n->prev;

    n->prev = n->next = NULL;
    list->size--;
}

/* ─────────────────── 生命周期 ─────────────────── */

List *list_create(void)
{
    List *list = malloc(sizeof(List));
    if (!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void list_destroy(List *list, ListFreeFn free_fn)
{
    if (!list) return;
    ListNode *cur = list->head;
    while (cur) {
        ListNode *next = cur->next;
        if (free_fn) free_fn(cur->data);
        free(cur);
        cur = next;
    }
    free(list);
}

/* ─────────────────── 插入 ─────────────────── */

ListNode *list_push_front(List *list, void *data)
{
    if (!list) return NULL;
    ListNode *n = node_alloc(data);
    if (!n) return NULL;
    link_after(list, NULL, n);
    return n;
}

ListNode *list_push_back(List *list, void *data)
{
    if (!list) return NULL;
    ListNode *n = node_alloc(data);
    if (!n) return NULL;
    link_after(list, list->tail, n);
    return n;
}

ListNode *list_insert_before(List *list, ListNode *node, void *data)
{
    if (!list) return NULL;
    /* node == NULL 视为插到尾部 */
    if (!node) return list_push_back(list, data);
    ListNode *n = node_alloc(data);
    if (!n) return NULL;
    link_after(list, node->prev, n);
    return n;
}

ListNode *list_insert_after(List *list, ListNode *node, void *data)
{
    if (!list) return NULL;
    /* node == NULL 视为插到头部 */
    if (!node) return list_push_front(list, data);
    ListNode *n = node_alloc(data);
    if (!n) return NULL;
    link_after(list, node, n);
    return n;
}

ListNode *list_insert_sorted(List *list, void *data, ListCmpFn cmp)
{
    if (!list || !cmp) return NULL;
    ListNode *cur = list->head;
    while (cur && cmp(cur->data, data) <= 0)
        cur = cur->next;
    /* cur == NULL 说明插在尾部，否则插在 cur 之前 */
    return list_insert_before(list, cur, data);
}

/* ─────────────────── 删除 ─────────────────── */

void *list_remove(List *list, ListNode *node, ListFreeFn free_fn)
{
    if (!list || !node) return NULL;
    void *data = node->data;
    unlink(list, node);
    if (free_fn) { free_fn(data); data = NULL; }
    free(node);
    return data;
}

void *list_pop_front(List *list, ListFreeFn free_fn)
{
    if (!list || !list->head) return NULL;
    return list_remove(list, list->head, free_fn);
}

void *list_pop_back(List *list, ListFreeFn free_fn)
{
    if (!list || !list->tail) return NULL;
    return list_remove(list, list->tail, free_fn);
}

size_t list_remove_if(List *list, const void *target,
                      ListCmpFn cmp, ListFreeFn free_fn)
{
    if (!list || !cmp) return 0;
    size_t removed = 0;
    ListNode *cur = list->head;
    while (cur) {
        ListNode *next = cur->next;
        if (cmp(cur->data, target) == 0) {
            list_remove(list, cur, free_fn);
            removed++;
        }
        cur = next;
    }
    return removed;
}

/* ─────────────────── 查找 ─────────────────── */

ListNode *list_find(const List *list, const void *target, ListCmpFn cmp)
{
    if (!list || !cmp) return NULL;
    for (ListNode *cur = list->head; cur; cur = cur->next)
        if (cmp(cur->data, target) == 0) return cur;
    return NULL;
}

ListNode *list_find_last(const List *list, const void *target, ListCmpFn cmp)
{
    if (!list || !cmp) return NULL;
    for (ListNode *cur = list->tail; cur; cur = cur->prev)
        if (cmp(cur->data, target) == 0) return cur;
    return NULL;
}

ListNode *list_at(const List *list, size_t index)
{
    if (!list || index >= list->size) return NULL;
    ListNode *cur;
    if (index < list->size / 2) {
        /* 从头部查 */
        cur = list->head;
        for (size_t i = 0; i < index; i++) cur = cur->next;
    } else {
        /* 从尾部查 */
        cur = list->tail;
        for (size_t i = list->size - 1; i > index; i--) cur = cur->prev;
    }
    return cur;
}

/* ─────────────────── 遍历 ─────────────────── */

void list_foreach(const List *list, ListForEachFn fn, void *user_data)
{
    if (!list || !fn) return;
    for (ListNode *cur = list->head; cur; cur = cur->next)
        fn(cur->data, user_data);
}

void list_foreach_rev(const List *list, ListForEachFn fn, void *user_data)
{
    if (!list || !fn) return;
    for (ListNode *cur = list->tail; cur; cur = cur->prev)
        fn(cur->data, user_data);
}

/* ─────────────────── 工具 ─────────────────── */

size_t list_size(const List *list)
{
    return list ? list->size : 0;
}

int list_is_empty(const List *list)
{
    return !list || list->size == 0;
}

void list_reverse(List *list)
{
    if (!list || list->size <= 1) return;
    ListNode *cur = list->head;
    while (cur) {
        /* 交换 prev / next */
        ListNode *tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
        cur = cur->prev;   /* 原来的 next */
    }
    /* 交换头尾指针 */
    ListNode *tmp = list->head;
    list->head = list->tail;
    list->tail = tmp;
}

/* ───────── 归并排序（仅操作指针，O(n log n)，稳定）───────── */

/* 将链表从 head 节点开始拆成两半，返回后半段的头节点 */
static ListNode *split_half(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode *second = slow->next;
    slow->next = NULL;
    if (second) second->prev = NULL;
    return second;
}

/* 合并两个有序单链表（借用 next 指针），返回合并后的头节点 */
static ListNode *merge_sorted(ListNode *a, ListNode *b, ListCmpFn cmp)
{
    if (!a) return b;
    if (!b) return a;
    if (cmp(a->data, b->data) <= 0) {
        a->next = merge_sorted(a->next, b, cmp);
        if (a->next) a->next->prev = a;
        a->prev = NULL;
        return a;
    } else {
        b->next = merge_sorted(a, b->next, cmp);
        if (b->next) b->next->prev = b;
        b->prev = NULL;
        return b;
    }
}

static ListNode *mergesort(ListNode *head, ListCmpFn cmp)
{
    if (!head || !head->next) return head;
    ListNode *second = split_half(head);
    head   = mergesort(head,   cmp);
    second = mergesort(second, cmp);
    return merge_sorted(head, second, cmp);
}

void list_sort(List *list, ListCmpFn cmp)
{
    if (!list || list->size <= 1 || !cmp) return;
    list->head = mergesort(list->head, cmp);
    /* 修复 tail 和各节点的 prev 指针（mergesort 仅保证 next 正确）*/
    ListNode *cur = list->head;
    list->head->prev = NULL;
    while (cur->next) {
        cur->next->prev = cur;
        cur = cur->next;
    }
    list->tail = cur;
}

void **list_to_array(const List *list, size_t *out_len)
{
    if (!list || list->size == 0) {
        if (out_len) *out_len = 0;
        return NULL;
    }
    void **arr = malloc(list->size * sizeof(void *));
    if (!arr) { if (out_len) *out_len = 0; return NULL; }
    size_t i = 0;
    for (ListNode *cur = list->head; cur; cur = cur->next)
        arr[i++] = cur->data;
    if (out_len) *out_len = list->size;
    return arr;
}

void list_splice(List *dst, List *src)
{
    if (!dst || !src || src->size == 0) return;
    if (dst->tail) {
        dst->tail->next  = src->head;
        src->head->prev  = dst->tail;
    } else {
        dst->head = src->head;
    }
    dst->tail  = src->tail;
    dst->size += src->size;
    src->head = src->tail = NULL;
    src->size = 0;
}
