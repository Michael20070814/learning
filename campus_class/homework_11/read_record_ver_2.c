#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 50
// 商品类型
enum ProductType {
    DRINK, // 饮品
    SNACK, // 零食
    INSTANTFOOD, // 速食
    CANDY, // 糖果
    OTHER
};
// 支付状态
enum PaymentStatus {
    SUCCESS, // 成功
    FAILED, // 失败
    PENDING // 待处理
};
// 交易记录
typedef struct RecordItem{
    int userID; // 用户ID
    enum ProductType productType; // 商品类型
    char productName[MAX_NAME_LENGTH]; // 商品名称
    float price; // 销售价格
    int quantity; // 销售数量
    enum PaymentStatus paymentStatus; // 支付状态
    struct tm purchaseTime; // 购买时间
    struct RecordItem* next;
} RecordItem;
enum PaymentStatus getPaymentStatus(const char* statusStr);
int compar_by_time(const void *p1, const void *p2);
struct tm parseTimeString(const char* timeStr);
int read_document(RecordItem *p[], int *quantity);
void swap(RecordItem *p, RecordItem *q);
enum ProductType getProductType(const char* typeStr);
RecordItem *Create_node(RecordItem *input[], int length);
RecordItem* readRecordItemsFromFile(void)
{
    int number, quantity;
    RecordItem* records[1005];//生成一个存放指针的数组
    RecordItem *p, *head;
    number = read_document(records, &quantity);
    if (number == 0)
    {
        printf("0\n");
        return NULL;
    }
    qsort(records, number, sizeof(RecordItem *), compar_by_time);//对指针进行排序
    head = Create_node(records, number);
    p = head;
    printf("%d\n", quantity);
    printf("%d-%02d-%02d %02d:%02d:%02d\n", p->purchaseTime.tm_year + 1900, p->purchaseTime.tm_mon + 1,
           p->purchaseTime.tm_mday, p->purchaseTime.tm_hour, p->purchaseTime.tm_min,
           p->purchaseTime.tm_sec);
    while (p -> next != NULL)
        p = p -> next;
    printf("%d-%02d-%02d %02d:%02d:%02d\n", p->purchaseTime.tm_year + 1900, p->purchaseTime.tm_mon + 1,
           p->purchaseTime.tm_mday, p->purchaseTime.tm_hour, p->purchaseTime.tm_min,
           p->purchaseTime.tm_sec);
    return head;
}
int read_document(RecordItem *p[], int *quantity)
{
    FILE *fp = fopen("record.txt", "r");
    char buffer[300];
    int i = 0;
    *quantity = 0;
    if (fp == NULL){return 0;}
    while (fgets(buffer, 299, fp) != NULL)
    {
        RecordItem *Node = (RecordItem *)calloc(1, sizeof(RecordItem));//使用calloc动态内存，分配到的空间自然都是0，会自动清空
        if (!Node)//分配不到空间，自动退出
            break;
        char tempTimeStr[100] = {0};
        char statusStr[100] = {0};
        char typeStr[20] = {0};
        int count = sscanf(buffer, " %d, %49[^,], %19[^,], %f, %d, %14[^,], %29[^\n]", 
                &Node->userID, Node->productName, typeStr, 
                &Node->price, &Node->quantity, statusStr, tempTimeStr);
        if (count != 7)
        {
            free(Node);
            continue;//确保读取的数据有7个，保证不乱读
        }
        Node->productType = getProductType(typeStr);
        Node->paymentStatus = getPaymentStatus(statusStr);
        Node->purchaseTime = parseTimeString(tempTimeStr);
        Node->next = NULL;
        *quantity += Node->quantity;
        if (i >= 1005)
            break;
        p[i++] = Node;
    }
    fclose(fp);
    return i;
}
enum ProductType getProductType(const char* typeStr) {
    if (strcmp(typeStr, "Drink") == 0 || strcmp(typeStr, "DRINK") == 0) return DRINK;
    if (strcmp(typeStr, "Snack") == 0 || strcmp(typeStr, "SNACK") == 0) return SNACK;
    if (strcmp(typeStr, "InstantFood") == 0 || strcmp(typeStr, "INSTANTFOOD") == 0) return INSTANTFOOD;
    if (strcmp(typeStr, "Candy") == 0 || strcmp(typeStr, "CANDY") == 0) return CANDY;
    return OTHER;
}
enum PaymentStatus getPaymentStatus(const char* statusStr) {
    if (strcmp(statusStr, "Success") == 0) return SUCCESS;
    if (strcmp(statusStr, "Failed") == 0) return FAILED;
    return PENDING;
}
struct tm parseTimeString(const char* timeStr) {
    struct tm tm_time = {0};
    sscanf(timeStr, " %d-%d-%d %d:%d:%d",
           &tm_time.tm_year, &tm_time.tm_mon, &tm_time.tm_mday,
           &tm_time.tm_hour, &tm_time.tm_min, &tm_time.tm_sec);
    tm_time.tm_year -= 1900;  // 年份从1900开始计算
    tm_time.tm_mon -= 1;      // 月份从0开始计算
    tm_time.tm_isdst = -1;    // 不考虑夏令时
    return tm_time;
}
double compareTime(struct tm* tm1, struct tm* tm2) {
    time_t time1 = mktime(tm1);
    time_t time2 = mktime(tm2);//及其昂贵，时间花费高
    return difftime(time1, time2);//计算时间过长导致程序被杀死，无法吐出输出
}//比较时间要先使用mktime转换，再用difftime计算差值
int compar_by_time(const void *p1, const void *p2)
{
    struct RecordItem* itemA = *(struct RecordItem**)p1;
    struct RecordItem* itemB = *(struct RecordItem**)p2;
    
    double diff = compareTime(&itemA->purchaseTime, &itemB->purchaseTime); // time1 - time2
    
    if (diff > 0) return -1;      // time2在time1之后，itemB应该排在itemA之前
    if (diff < 0) return 1;     // time2在time1之前，itemB应该排在itemA之后
    return 0;
}
void swap(RecordItem *p, RecordItem *q)
{
    RecordItem temp = *p;
    *p = *q;
    *q = temp;
}
RecordItem *Create_node(RecordItem *input[], int length)//把指针串联起来
{
    for (int i = 0; i < length - 1; i++)
        input[i]->next = input[i + 1];
    input[length - 1]->next = NULL;
    return input[0];
}