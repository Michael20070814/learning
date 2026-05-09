/*
 * 常见数组与链表算法模板，使用普通 C 语言接口实现。
 *
 * 约定：
 * 1. 一维数组统一用 int *nums 和 int numsSize 表示。
 * 2. 需要返回数组时，函数返回 malloc 出来的 int *，并通过 returnSize 返回长度。
 * 3. 需要返回二维数组时，函数返回 malloc 出来的 int **，
 *    并通过 returnSize 和 returnColumnSizes 返回行数与每行列数。
 * 4. 调用者负责释放返回的动态内存。
 */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int maxInt(int a, int b) {
    return a > b ? a : b;
}

static int minInt(int a, int b) {
    return a < b ? a : b;
}

/*
 * ==================== 数组相关算法 ====================
 */

/* 704. 二分查找：在升序数组中查找 target，找到返回下标，否则返回 -1。 */
int binarySearch(int *nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

/* 35. 搜索插入位置：返回 target 应插入的位置。 */
int searchInsert(int *nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

static int lowerBound(int *nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    int ans = numsSize;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] >= target) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return ans;
}

static int upperBound(int *nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    int ans = numsSize;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (nums[mid] > target)
        {
            ans = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return ans;
}

/*
 * 34. 在排序数组中查找元素的第一个和最后一个位置。
 * 返回长度为 2 的数组：[first, last]；调用者负责 free。
 */
int *searchRange(int *nums, int numsSize, int target, int *returnSize) {
    int *ans = (int *)malloc(sizeof(int) * 2);

    *returnSize = 2;
    if (ans == NULL) {
        *returnSize = 0;
        return NULL;
    }

    ans[0] = -1;
    ans[1] = -1;

    int first = lowerBound(nums, numsSize, target);
    int last = upperBound(nums, numsSize, target) - 1;

    if (first <= last && first < numsSize && nums[first] == target)
    {
        ans[0] = first;
        ans[1] = last;
    }

    return ans;
}

/* 69. x 的平方根：返回不超过 sqrt(x) 的最大整数。 */
int mySqrt(int x) {
    if (x < 2) {
        return x;
    }

    int left = 1;
    int right = x / 2;
    int ans = 0;

    while (left <= right) {
        long long mid = left + (right - left) / 2;

        if (mid * mid <= x) {
            ans = (int)mid;
            left = (int)mid + 1;
        } else {
            right = (int)mid - 1;
        }
    }

    return ans;
}

/* 367. 有效的完全平方数：判断 num 是否为某个整数的平方。 */
bool isPerfectSquare(int num)
{
    long long left = 0;
    long long right = num;

    while (left <= right)
    {
        long long mid = left + (right - left) / 2;
        long long square = mid * mid;

        if (square == num)
        {
            return true;
        }
        else if (square < num)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return false;
}

/* 26. 删除排序数组中的重复项：原地去重，返回新长度。 */
int removeDuplicates(int *nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    int slow = 0;
    for (int fast = 1; fast < numsSize; ++fast)
    {
        if (nums[fast] != nums[slow])
        {
            nums[++slow] = nums[fast];
        }
    }

    return slow + 1;
}

/* 27. 移除元素：原地删除所有等于 val 的元素，返回新长度。 */
int removeElement(int *nums, int numsSize, int val) {
    int slow = 0;

    for (int fast = 0; fast < numsSize; ++fast) 
    {
        if (nums[fast] != val) {
            nums[slow++] = nums[fast];
        }
    }

    return slow;
}

/* 283. 移动零：把 0 移到末尾，并保持非零元素相对顺序。 */
void moveZeroes(int *nums, int numsSize) {
    int slow = 0;

    for (int fast = 0; fast < numsSize; ++fast)
    {
        if (nums[fast] != 0)
        {
            nums[slow++] = nums[fast];
        }
    }

    while (slow < numsSize) {
        nums[slow++] = 0;
    }
}

/*
 * 977. 有序数组的平方。
 * 返回新数组；returnSize 返回数组长度；调用者负责 free。
 */

// 这里可能存在负数
int *sortedSquares(int *nums, int numsSize, int *returnSize) {
    int *ans = (int *)malloc(sizeof(int) * numsSize);

    *returnSize = numsSize;
    if (numsSize == 0) {
        return ans;
    }
    if (ans == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int left = 0;
    int right = numsSize - 1;
    int pos = numsSize - 1;

    while (left <= right) {
        int leftSquare = nums[left] * nums[left];
        int rightSquare = nums[right] * nums[right];

        if (leftSquare > rightSquare) {
            ans[pos--] = leftSquare;
            ++left;
        } else {
            ans[pos--] = rightSquare;
            --right;
        }
    }

    return ans;
}

/* 53. 最大子数组和：Kadane 算法。 */
// 子数组不需要保留顺序
int maxSubArray(int *nums, int numsSize) {
    int current = nums[0];
    int ans = nums[0];

    for (int i = 1; i < numsSize; ++i) {
        current = maxInt(nums[i], current + nums[i]);
        ans = maxInt(ans, current);
    }

    return ans;
}

/* 152. 乘积最大子数组：同时维护最大乘积和最小乘积。 */
int maxProduct(int *nums, int numsSize) {
    int ans = nums[0];
    int curMax = nums[0];
    int curMin = nums[0];

    for (int i = 1; i < numsSize; ++i) {
        int x = nums[i];

        // 如果是负的，最大和最小互换
        if (x < 0) {
            int temp = curMax;
            curMax = curMin;
            curMin = temp;
        }

        curMax = maxInt(x, curMax * x);
        curMin = minInt(x, curMin * x);
        ans = maxInt(ans, curMax);
    }

    return ans;
}

/* 209. 长度最小的子数组：滑动窗口。 */
// 和要大于target，并且需要保持连续
int minSubArrayLen(int target, int *nums, int numsSize)
{
    int left = 0;
    int sum = 0;
    int ans = INT_MAX;

    for (int right = 0; right < numsSize; ++right)
    {
        sum += nums[right];

        while (sum >= target)
        {
            ans = minInt(ans, right - left + 1);
            sum -= nums[left++];
        }
    }

    return ans == INT_MAX ? 0 : ans;
}

/*
 * 54. 螺旋矩阵。
 * matrixSize 是行数，matrixColSize[i] 是第 i 行列数。
 * 返回一维数组；returnSize 返回元素个数；调用者负责 free。
 */
/* 把矩阵用顺时针螺旋的方式读取为一维数组 */
int *spiralOrder(int **matrix, int matrixSize, int *matrixColSize, int *returnSize) {
    int rows = matrixSize;
    int cols = matrixSize == 0 ? 0 : matrixColSize[0];
    int total = rows * cols;
    int *ans = NULL;

    *returnSize = total;
    if (total == 0)
    {
        return NULL;
    }

    ans = (int *)malloc(sizeof(int) * total);
    if (ans == NULL)
    {
        *returnSize = 0;
        return NULL;
    }

    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;
    int index = 0;

    while (top <= bottom && left <= right)
    {
        for (int j = left; j <= right; ++j)
        {
            ans[index++] = matrix[top][j];
        }
        ++top;

        for (int i = top; i <= bottom; ++i) {
            ans[index++] = matrix[i][right];
        }
        --right;

        // 保证是否还有下边
        if (top <= bottom) {
            for (int j = right; j >= left; --j) {
                ans[index++] = matrix[bottom][j];
            }
            --bottom;
        }

        // 保证是否还有左边
        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                ans[index++] = matrix[i][left];
            }
            ++left;
        }
    }

    return ans;
}

/*
 * 59. 螺旋矩阵 II。
 * 返回 n 行二维数组；returnColumnSizes 保存每一行的列数。
 * 调用者需要依次 free 每一行、free(returnColumnSizes)、free(返回值)。
 */
// 顺时针递增生成一个n阶矩阵
int **generateMatrix(int n, int *returnSize, int **returnColumnSizes)
{
    int **matrix = NULL;

    *returnSize = n;
    *returnColumnSizes = NULL;

    if (n <= 0)
    {
        *returnSize = 0;
        return NULL;
    }

    matrix = (int **)malloc(sizeof(int *) * n);
    *returnColumnSizes = (int *)malloc(sizeof(int) * n);
    if (matrix == NULL || *returnColumnSizes == NULL) {
        free(matrix);
        free(*returnColumnSizes);
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    for (int i = 0; i < n; ++i)
    {
        matrix[i] = (int *)calloc(n, sizeof(int));
        (*returnColumnSizes)[i] = n;

        if (matrix[i] == NULL)
        {
            for (int j = 0; j < i; ++j)
            {
                free(matrix[j]);
            }
            free(matrix);
            free(*returnColumnSizes);
            *returnSize = 0;
            *returnColumnSizes = NULL;
            return NULL;
        }
    }

    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;
    int value = 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j) {
            matrix[top][j] = value++;
        }
        ++top;

        for (int i = top; i <= bottom; ++i) {
            matrix[i][right] = value++;
        }
        --right;

        if (top <= bottom) {
            for (int j = right; j >= left; --j) {
                matrix[bottom][j] = value++;
            }
            --bottom;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                matrix[i][left] = value++;
            }
            ++left;
        }
    }

    return matrix;
}

/*
 * ==================== 链表相关算法 ====================
 */

struct ListNode
{
    int val;
    struct ListNode *next;
};

// 创建新链表节点
static struct ListNode *newListNode(int val)
{
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));

    if (node == NULL) {
        return NULL;
    }

    node->val = val;
    node->next = NULL;
    return node;
}

/* 19. 删除链表倒数第 n 个节点。 */
// fast比slow快n个，当fast到了结尾，则slow到了倒数第n个
struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
    struct ListNode dummy;
    struct ListNode *fast = &dummy;
    struct ListNode *slow = &dummy;

    dummy.val = 0;
    dummy.next = head;

    for (int i = 0; i < n; ++i)
    {
        fast = fast->next;
    }

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    struct ListNode *del = slow->next;
    slow->next = del->next;
    free(del);

    return dummy.next;
}

/* 82. 删除排序链表中的重复元素 II：重复值全部删除。 */
/* 排序链表相同的值会紧挨着，重复值需要全部删掉 */
struct ListNode *deleteDuplicatesII(struct ListNode *head)
{
    struct ListNode dummy;
    struct ListNode *prev = &dummy;

    // 制作一个哨兵节点
    dummy.val = 0;
    dummy.next = head;

    while (head != NULL)
    {
        bool duplicated = false;

        // 删到最后一个重复元素之前
        while (head->next != NULL && head->val == head->next->val)
        {
            duplicated = true;
            struct ListNode *del = head;
            head = head->next;
            free(del);
        }

        if (duplicated)
        {
            struct ListNode *del = head;
            head = head->next;
            free(del);
            prev->next = head;
        }
        else
        {
            prev = head;
            head = head->next;
        }
    }

    return dummy.next;
}

/* 83. 删除排序链表中的重复元素：每个值保留一个节点。 */
struct ListNode *deleteDuplicates(struct ListNode *head)
{
    struct ListNode *cur = head;

    while (cur != NULL && cur->next != NULL)
    {
        if (cur->val == cur->next->val)
        {
            struct ListNode *del = cur->next;
            cur->next = del->next;
            free(del);
        }
        else
        {
            cur = cur->next;
        }
    }

    return head;
}

/* 203. 移除链表元素。 */
struct ListNode *removeElements(struct ListNode *head, int val) {
    struct ListNode dummy;
    struct ListNode *prev = &dummy;
    struct ListNode *cur = head;

    dummy.val = 0;
    dummy.next = head;

    while (cur != NULL)
    {
        if (cur->val == val)
        {
            prev->next = cur->next;
            free(cur);
            cur = prev->next;
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }

    return dummy.next;
}

/* 206. 反转链表。 */
// 返回值是翻转过后的链表的第一个
struct ListNode *reverseList(struct ListNode *head)
{
    struct ListNode *prev = NULL;
    struct ListNode *cur = head;

    // 从前往后调转指针方向
    while (cur != NULL)
    {
        struct ListNode *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return prev;
}

/* 92. 反转链表 II：反转第 left 到第 right 个节点。 */
struct ListNode *reverseBetween(struct ListNode *head, int left, int right) {
    struct ListNode dummy;
    struct ListNode *prev = &dummy;

    if (head == NULL || left == right)
    {
        return head;
    }

    dummy.val = 0;
    dummy.next = head;

    for (int i = 1; i < left; ++i)
    {
        prev = prev->next;
    }

    struct ListNode *tail = prev->next;
    struct ListNode *cur = tail->next;

    // 一个个逐渐往后面推
    for (int i = 0; i < right - left; ++i)
    {
        tail->next = cur->next;
        cur->next = prev->next;
        prev->next = cur;
        cur = tail->next;
    }

    return dummy.next;
}

/* 24. 两两交换链表中的节点。 */
struct ListNode *swapPairs(struct ListNode *head)
{
    struct ListNode dummy;
    struct ListNode *prev = &dummy;

    // 统统设置一个哨兵节点来控制一个元素
    dummy.val = 0;
    dummy.next = head;

    while (head != NULL && head->next != NULL)
    {
        struct ListNode *first = head;
        struct ListNode *second = head->next;

        prev->next = second;
        first->next = second->next;
        second->next = first;

        prev = first;
        head = first->next;
    }

    return dummy.next;
}

/* 25. K 个一组翻转链表。 */
/* k个节点为一组进行翻转 若不够k个 则不翻转*/
struct ListNode *reverseKGroup(struct ListNode *head, int k)
{
    struct ListNode dummy;
    struct ListNode *groupPrev = &dummy;

    if (k <= 1 || head == NULL)
    {
        return head;
    }

    dummy.val = 0;
    dummy.next = head;

    while (true) 
    {
        struct ListNode *kth = groupPrev;

        for (int i = 0; i < k; ++i)
        {
            kth = kth->next;
            if (kth == NULL)
            {
                return dummy.next;
            }
        }

        struct ListNode *groupNext = kth->next;
        struct ListNode *prev = groupNext;
        struct ListNode *cur = groupPrev->next;

        while (cur != groupNext)
        {
            // 逐个往后调转
            struct ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        struct ListNode *newGroupTail = groupPrev->next;
        groupPrev->next = kth;
        groupPrev = newGroupTail;
    }
}

/* 21. 合并两个升序链表。 */
struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    struct ListNode dummy;
    struct ListNode *tail = &dummy;

    dummy.val = 0;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL)
    {
        // 逐个往后 谁小先加谁
        if (list1->val < list2->val)
        {
            tail->next = list1;
            list1 = list1->next;
        }
        else
        {
            tail->next = list2;
            list2 = list2->next;
        }

        tail = tail->next;
    }

    // 最后会有一个先到空，则把另外一个直接加到后面即可
    tail->next = list1 != NULL ? list1 : list2;
    return dummy.next;
}

// 合并很多个有序链表，采用分治法进行合成
static struct ListNode *mergeListRange(struct ListNode **lists, int left, int right) {
    int mid;

    if (left == right)
    {
        return lists[left];
    }

    mid = left + (right - left) / 2;
    return mergeTwoLists(mergeListRange(lists, left, mid),
                         mergeListRange(lists, mid + 1, right));
}

/* 23. 合并 K 个升序链表。 */
struct ListNode *mergeKLists(struct ListNode **lists, int listsSize) {
    if (lists == NULL || listsSize == 0) {
        return NULL;
    }

    return mergeListRange(lists, 0, listsSize - 1);
}

/* 2. 两数相加：链表按逆序存储数字。 */
/* 可以实现超长数字的相加 */
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    struct ListNode dummy;
    struct ListNode *tail = &dummy;
    int carry = 0;

    dummy.val = 0;
    dummy.next = NULL;

    while (l1 != NULL || l2 != NULL || carry != 0)
    {
        int sum = carry;

        if (l1 != NULL)
        {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL)
        {
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10;
        tail->next = newListNode(sum % 10);
        if (tail->next == NULL)
        {
            return dummy.next;
        }
        tail = tail->next;
    }

    return dummy.next;
}

static int getListLength(struct ListNode *head) {
    int length = 0;

    while (head != NULL) {
        ++length;
        head = head->next;
    }

    return length;
}

/* 445. 两数相加 II：链表按正序存储数字，用数组模拟栈。 */
struct ListNode *addTwoNumbersII(struct ListNode *l1, struct ListNode *l2)
{
    int len1 = getListLength(l1);
    int len2 = getListLength(l2);
    int *stack1 = (int *)malloc(sizeof(int) * (len1 == 0 ? 1 : len1));
    int *stack2 = (int *)malloc(sizeof(int) * (len2 == 0 ? 1 : len2));
    int top1 = 0;
    int top2 = 0;
    int carry = 0;
    struct ListNode *head = NULL;

    if (stack1 == NULL || stack2 == NULL) {
        free(stack1);
        free(stack2);
        return NULL;
    }

    // 把数字升序存进去就当作是stack进行存储了
    while (l1 != NULL)
    {
        stack1[top1++] = l1->val;
        l1 = l1->next;
    }
    while (l2 != NULL) {
        stack2[top2++] = l2->val;
        l2 = l2->next;
    }

    while (top1 > 0 || top2 > 0 || carry != 0)
    {
        int sum = carry;

        if (top1 > 0)
        {
            sum += stack1[--top1];
        }
        if (top2 > 0) {
            sum += stack2[--top2];
        }

        carry = sum / 10;
        struct ListNode *node = newListNode(sum % 10);
        if (node == NULL) {
            break;
        }

        node->next = head;
        head = node;
    }

    free(stack1);
    free(stack2);
    return head;
}

/* 141. 环形链表：快慢指针判断是否有环。 */
/* 如果没环，则fast先到链表结尾，从而结束 
   有环的话，slow一定会被fast追上 */
bool hasCycle(struct ListNode *head) 
{
    struct ListNode *slow = head;
    struct ListNode *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

/* 142. 环形链表 II：返回环的入口节点。 */
struct ListNode *detectCycle(struct ListNode *head) 
{
    struct ListNode *slow = head;
    struct ListNode *fast = head;

    /* 这里可以推导一下 */
    while (fast != NULL && fast->next != NULL) 
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) 
        {
            fast = head;
            while (fast != slow)
            {
                fast = fast->next;
                slow = slow->next;
            }
            return slow;
        }
    }

    return NULL;
}

/* 160. 相交链表：返回两条链表第一个公共节点。 */
/* 他们最后的部分是一样的，只是前面有不相同的 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) 
{
    struct ListNode *a = headA;
    struct ListNode *b = headB;

    while (a != b) 
    {
        a = a == NULL ? headB : a->next;
        b = b == NULL ? headA : b->next;
    }

    return a;
}

/* 86. 分隔链表。 */
struct ListNode *partition(struct ListNode *head, int x)
{
    struct ListNode lessDummy;
    struct ListNode greaterDummy;
    struct ListNode *lessTail = &lessDummy;
    struct ListNode *greaterTail = &greaterDummy;

    lessDummy.val = 0;
    lessDummy.next = NULL;
    greaterDummy.val = 0;
    greaterDummy.next = NULL;

    while (head != NULL)
    {
        if (head->val < x)
        {
            lessTail->next = head;
            lessTail = head;
        }
        else
        {
            greaterTail->next = head;
            greaterTail = head;
        }

        head = head->next;
    }

    lessTail->next = greaterDummy.next;
    greaterTail->next = NULL;
    return lessDummy.next;
}

/*
 * 725. 分隔链表。
 * 返回长度为 k 的 struct ListNode* 数组；returnSize 返回 k；调用者负责 free 数组。
 */
struct ListNode **splitListToParts(struct ListNode *head, int k, int *returnSize)
{
    // 分配一个二维数组
    struct ListNode **ans = (struct ListNode **)calloc(k, sizeof(struct ListNode *));
    int length = getListLength(head);
    int baseSize = k == 0 ? 0 : length / k;
    int extra = k == 0 ? 0 : length % k;
    struct ListNode *cur = head;

    *returnSize = k;
    if (ans == NULL)
    {
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < k && cur != NULL; ++i)
    {
        // 把多余的均分到前面去
        int partSize = baseSize + (extra-- > 0 ? 1 : 0);
        ans[i] = cur;

        for (int j = 1; j < partSize; ++j)
            cur = cur->next;

        struct ListNode *nextPart = cur->next;
        cur->next = NULL;
        cur = nextPart;
    }

    return ans;
}

/* 148. 排序链表：归并排序。 */
/* 大链表分化为小链表进行排序 */
struct ListNode *sortList(struct ListNode *head)
{
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    struct ListNode *prev = NULL;

    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    while (fast != NULL && fast->next != NULL)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    prev->next = NULL;
    return mergeTwoLists(sortList(head), sortList(slow));
}

/* 143. 重排链表：L0->Ln->L1->Ln-1... */
void reorderList(struct ListNode *head)
{
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    struct ListNode *second;
    struct ListNode *first;

    if (head == NULL || head->next == NULL)
    {
        return;
    }

    while (fast->next != NULL && fast->next->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    second = reverseList(slow->next);
    slow->next = NULL;
    first = head;

    while (second != NULL) 
    {
        struct ListNode *next1 = first->next;
        struct ListNode *next2 = second->next;

        // 交错插入
        first->next = second;
        second->next = next1;

        first = next1;
        second = next2;
    }
}

/* 234. 回文链表：比较前半段和反转后的后半段，最后恢复链表。 */
bool isPalindrome(struct ListNode *head) 
{
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    struct ListNode *second;
    struct ListNode *p1;
    struct ListNode *p2;
    bool ans = true;

    if (head == NULL || head->next == NULL) {
        return true;
    }

    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    second = reverseList(slow->next);
    p1 = head;
    p2 = second;

    while (p2 != NULL) {
        if (p1->val != p2->val) {
            ans = false;
            break;
        }

        p1 = p1->next;
        p2 = p2->next;
    }

    slow->next = reverseList(second);
    return ans;
}

/*
 * ==================== 设计链表：C 风格接口 ====================
 *
 * 这里按常见 C 题目接口写：
 * MyLinkedList* myLinkedListCreate();
 * int myLinkedListGet(MyLinkedList* obj, int index);
 * void myLinkedListAddAtHead(MyLinkedList* obj, int val);
 * void myLinkedListAddAtTail(MyLinkedList* obj, int val);
 * void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val);
 * void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index);
 * void myLinkedListFree(MyLinkedList* obj);
 */

typedef struct MyLinkedList {
    int val;
    struct MyLinkedList *next;
} MyLinkedList;

MyLinkedList *myLinkedListCreate(void) {
    MyLinkedList *dummy = (MyLinkedList *)malloc(sizeof(MyLinkedList));

    if (dummy == NULL) {
        return NULL;
    }

    dummy->val = 0;      /* 哑节点的 val 用来记录链表长度。 */
    dummy->next = NULL;
    return dummy;
}

int myLinkedListGet(MyLinkedList *obj, int index) {
    MyLinkedList *cur;

    if (obj == NULL || index < 0 || index >= obj->val) {
        return -1;
    }

    cur = obj->next;
    for (int i = 0; i < index; ++i) {
        cur = cur->next;
    }

    return cur->val;
}

void myLinkedListAddAtHead(MyLinkedList *obj, int val) {
    MyLinkedList *node;

    if (obj == NULL) {
        return;
    }

    node = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    if (node == NULL) {
        return;
    }

    node->val = val;
    node->next = obj->next;
    obj->next = node;
    // 用来表示链表的长度
    ++obj->val;
}

void myLinkedListAddAtTail(MyLinkedList *obj, int val) {
    MyLinkedList *cur;
    MyLinkedList *node;

    if (obj == NULL) {
        return;
    }

    cur = obj;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    node = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    if (node == NULL) {
        return;
    }

    node->val = val;
    node->next = NULL;
    cur->next = node;
    ++obj->val;
}

// 指定位置的添加
void myLinkedListAddAtIndex(MyLinkedList *obj, int index, int val) {
    MyLinkedList *prev;
    MyLinkedList *node;

    if (obj == NULL) {
        return;
    }
    if (index < 0) {
        index = 0;
    }
    if (index > obj->val) {
        return;
    }

    prev = obj;
    for (int i = 0; i < index; ++i) {
        prev = prev->next;
    }

    node = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    if (node == NULL) {
        return;
    }

    node->val = val;
    node->next = prev->next;
    prev->next = node;
    ++obj->val;
}

// 指定位置删除
void myLinkedListDeleteAtIndex(MyLinkedList *obj, int index) {
    MyLinkedList *prev;
    MyLinkedList *del;

    if (obj == NULL || index < 0 || index >= obj->val) {
        return;
    }

    prev = obj;
    for (int i = 0; i < index; ++i) {
        prev = prev->next;
    }

    del = prev->next;
    prev->next = del->next;
    free(del);
    --obj->val;
}

// 整个链表的free
void myLinkedListFree(MyLinkedList *obj) {
    while (obj != NULL) {
        MyLinkedList *next = obj->next;
        free(obj);
        obj = next;
    }
}

/*
 * ==================== 链表测试辅助函数 ====================
 */

// 根据数组的数字创建一个链表
struct ListNode *createLinkedList(int *nums, int numsSize) {
    struct ListNode dummy;
    struct ListNode *tail = &dummy;

    dummy.val = 0;
    dummy.next = NULL;

    for (int i = 0; i < numsSize; ++i) {
        tail->next = newListNode(nums[i]);
        if (tail->next == NULL) {
            return dummy.next;
        }
        tail = tail->next;
    }

    return dummy.next;
}

// 释放内存空间
void freeLinkedList(struct ListNode *head) {
    while (head != NULL) {
        struct ListNode *next = head->next;
        free(head);
        head = next;
    }
}

void printLinkedList(struct ListNode *head) {
    while (head != NULL) {
        printf("%d", head->val);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    printf("\n");
}
