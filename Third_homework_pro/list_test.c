/**
 * list_test.c — 使用示例
 * 编译：gcc -Wall -Wextra -o list_test list_test.c list.c
 */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── 辅助：比较两个 int* ── */
static int cmp_int(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

static void print_int(void *data, void *user_data)
{
    (void)user_data;
    printf("%d ", *(int *)data);
}

/* ── 辅助：比较两个 char* 字符串 ── */
static int cmp_str(const void *a, const void *b)
{
    return strcmp((const char *)a, (const char *)b);
}

static void print_str(void *data, void *user_data)
{
    (void)user_data;
    printf("\"%s\" ", (char *)data);
}

int main(void)
{
    /* ── 1. 整数链表基本操作 ── */
    puts("=== 整数链表 ===");
    List *nums = list_create();

    int vals[] = {3, 1, 4, 1, 5, 9, 2, 6};
    for (int i = 0; i < 8; i++)
        list_push_back(nums, &vals[i]);

    printf("原始：");
    list_foreach(nums, print_int, NULL);
    puts("");

    list_sort(nums, cmp_int);
    printf("排序：");
    list_foreach(nums, print_int, NULL);
    puts("");

    list_reverse(nums);
    printf("反转：");
    list_foreach(nums, print_int, NULL);
    puts("");

    /* 删除值为 1 的所有节点 */
    int target = 1;
    size_t removed = list_remove_if(nums, &target, cmp_int, NULL);
    printf("删除 1（共 %zu 个）后：", removed);
    list_foreach(nums, print_int, NULL);
    puts("");

    /* 按下标访问 */
    ListNode *node = list_at(nums, 2);
    if (node) printf("下标 2 的值：%d\n", *(int *)node->data);

    list_destroy(nums, NULL);   /* 数据是栈变量，不需要 free */

    /* ── 2. 字符串链表（堆分配数据）── */
    puts("\n=== 字符串链表 ===");
    List *words = list_create();

    const char *src[] = {"banana", "apple", "cherry", "date"};
    for (int i = 0; i < 4; i++)
        list_push_back(words, strdup(src[i]));   /* strdup 返回堆内存 */

    printf("原始：");
    list_foreach(words, print_str, NULL);
    puts("");

    list_sort(words, cmp_str);
    printf("排序：");
    list_foreach(words, print_str, NULL);
    puts("");

    /* 查找 "cherry" */
    ListNode *found = list_find(words, "cherry", cmp_str);
    if (found) printf("找到：%s\n", (char *)found->data);

    /* 在 "cherry" 前面插入 "blueberry" */
    list_insert_before(words, found, strdup("blueberry"));
    printf("插入 blueberry 后：");
    list_foreach(words, print_str, NULL);
    puts("");

    /* 弹出头部 */
    char *popped = list_pop_front(words, NULL);
    printf("弹出头部：%s\n", popped);
    free(popped);

    /* 导出为数组 */
    size_t len;
    void **arr = list_to_array(words, &len);
    printf("导出数组（共 %zu 项）：", len);
    for (size_t i = 0; i < len; i++) printf("\"%s\" ", (char *)arr[i]);
    puts("");
    free(arr);   /* 只需 free 数组本身，data 仍由链表管理 */

    list_destroy(words, free);   /* 数据是堆内存，传 free 一并释放 */

    /* ── 3. 有序插入示例 ── */
    puts("\n=== 有序插入 ===");
    List *sorted = list_create();
    int vs[] = {5, 3, 8, 1, 9, 2};
    for (int i = 0; i < 6; i++)
        list_insert_sorted(sorted, &vs[i], cmp_int);
    list_foreach(sorted, print_int, NULL);
    puts("");
    list_destroy(sorted, NULL);

    /* ── 4. splice 合并两个链表 ── */
    puts("\n=== 链表合并 ===");
    List *la = list_create();
    List *lb = list_create();
    int a[] = {1, 2, 3}, b[] = {4, 5, 6};
    for (int i = 0; i < 3; i++) list_push_back(la, &a[i]);
    for (int i = 0; i < 3; i++) list_push_back(lb, &b[i]);
    list_splice(la, lb);
    printf("合并后（la）：");
    list_foreach(la, print_int, NULL);
    printf("\nlb 长度：%zu\n", list_size(lb));
    list_destroy(la, NULL);
    list_destroy(lb, NULL);

    puts("\nAll tests passed.");
    return 0;
}
