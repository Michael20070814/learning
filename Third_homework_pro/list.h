/**
 * list.h — 通用双向链表库
 *
 * 支持：头插、尾插、任意位置插入、按值/位置删除、查找、遍历、排序、反转
 * 节点数据类型为 void*，可存放任意类型数据
 */

#ifndef LIST_H
#define LIST_H

#include <stddef.h>

/* ───────────────────────── 类型定义 ───────────────────────── */

typedef struct ListNode {
    void            *data;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;   /* 指向第一个节点（哨兵头节点之后）*/
    ListNode *tail;   /* 指向最后一个节点                  */
    size_t    size;   /* 当前元素数量                       */
} List;

/* 比较函数：a < b 返回负数，a == b 返回 0，a > b 返回正数 */
typedef int  (*ListCmpFn)(const void *a, const void *b);

/* 遍历回调：对每个节点的 data 执行操作 */
typedef void (*ListForEachFn)(void *data, void *user_data);

/* 释放数据回调（可选，若数据是堆分配的则传入，否则传 NULL）*/
typedef void (*ListFreeFn)(void *data);

/* ────────────────────── 生命周期 ────────────────────── */

/**
 * list_create  — 创建一个空链表
 * 返回值：成功返回链表指针，内存不足返回 NULL
 */
List    *list_create(void);

/**
 * list_destroy — 销毁链表及所有节点
 * @free_fn：若非 NULL，对每个节点的 data 调用 free_fn 后再释放节点
 */
void     list_destroy(List *list, ListFreeFn free_fn);

/* ─────────────────────── 插入 ─────────────────────── */

/**
 * list_push_front — 在链表头部插入数据
 * 返回值：成功返回新节点指针，失败返回 NULL
 */
ListNode *list_push_front(List *list, void *data);

/**
 * list_push_back — 在链表尾部插入数据
 */
ListNode *list_push_back(List *list, void *data);

/**
 * list_insert_before — 在指定节点之前插入数据
 * @node：参考节点，若为 NULL 则插入到尾部
 */
ListNode *list_insert_before(List *list, ListNode *node, void *data);

/**
 * list_insert_after — 在指定节点之后插入数据
 * @node：参考节点，若为 NULL 则插入到头部
 */
ListNode *list_insert_after(List *list, ListNode *node, void *data);

/**
 * list_insert_sorted — 按 cmp 函数升序插入（保持有序链表的有序性）
 */
ListNode *list_insert_sorted(List *list, void *data, ListCmpFn cmp);

/* ─────────────────────── 删除 ─────────────────────── */

/**
 * list_remove — 移除指定节点
 * @free_fn：若非 NULL，对 data 调用 free_fn
 * 返回值：被移除节点的 data（当 free_fn 为 NULL 时由调用方管理内存）
 */
void     *list_remove(List *list, ListNode *node, ListFreeFn free_fn);

/**
 * list_pop_front — 移除头节点，返回其 data
 */
void     *list_pop_front(List *list, ListFreeFn free_fn);

/**
 * list_pop_back — 移除尾节点，返回其 data
 */
void     *list_pop_back(List *list, ListFreeFn free_fn);

/**
 * list_remove_if — 删除所有满足 cmp(data, target) == 0 的节点
 * 返回值：删除的节点数量
 */
size_t    list_remove_if(List *list, const void *target,
                         ListCmpFn cmp, ListFreeFn free_fn);

/* ─────────────────────── 查找 ─────────────────────── */

/**
 * list_find — 从头开始查找第一个 cmp(data, target) == 0 的节点
 * 返回值：找到返回节点指针，未找到返回 NULL
 */
ListNode *list_find(const List *list, const void *target, ListCmpFn cmp);

/**
 * list_find_last — 从尾部开始查找
 */
ListNode *list_find_last(const List *list, const void *target, ListCmpFn cmp);

/**
 * list_at — 按下标（0-based）获取节点
 * 返回值：合法下标返回节点指针，越界返回 NULL
 */
ListNode *list_at(const List *list, size_t index);

/* ─────────────────────── 遍历 ─────────────────────── */

/**
 * list_foreach — 正向遍历，对每个 data 调用 fn(data, user_data)
 */
void      list_foreach(const List *list, ListForEachFn fn, void *user_data);

/**
 * list_foreach_rev — 反向遍历
 */
void      list_foreach_rev(const List *list, ListForEachFn fn, void *user_data);

/* ─────────────────────── 工具 ─────────────────────── */

/**
 * list_size — 返回元素数量
 */
size_t    list_size(const List *list);

/**
 * list_is_empty — 返回 1 表示空，0 表示非空
 */
int       list_is_empty(const List *list);

/**
 * list_reverse — 原地反转链表
 */
void      list_reverse(List *list);

/**
 * list_sort — 原地归并排序（稳定，O(n log n)）
 */
void      list_sort(List *list, ListCmpFn cmp);

/**
 * list_to_array — 将链表 data 指针导出为 void* 数组（调用方负责 free 数组本身）
 * @out_len：输出数组长度
 * 返回值：堆分配的 void* 数组，失败返回 NULL
 */
void    **list_to_array(const List *list, size_t *out_len);

/**
 * list_splice — 将 src 链表的所有节点移动到 dst 的尾部（src 变空）
 */
void      list_splice(List *dst, List *src);

#endif /* LIST_H */
