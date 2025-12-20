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
struct tm parseTimeString(const char* timeStr);
int compareTime(struct tm* tm1, struct tm* tm2);
int read_document(RecordItem p[], int *quantity);
void sequence_by_time(RecordItem p[], int length);
void swap(RecordItem *p, RecordItem *q);
enum ProductType getProductType(const char* typeStr);
RecordItem *Create_node(RecordItem input[], int length);
RecordItem* readRecordItemsFromFile(void);
int main(void)
{
    RecordItem* head = readRecordItemsFromFile();
    return 0;
}
RecordItem* readRecordItemsFromFile(void)
{
    int number, quantity;
    RecordItem* records = (RecordItem *)malloc(1000 * sizeof(RecordItem));
    RecordItem *p, *head;
    number = read_document(records, &quantity);
    if (number == 0)
    {
        free(records);
        printf("0\n");
        return NULL;
    }
    sequence_by_time(records, number);
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
    fflush(stdout);//清空缓冲区，但是没有输出多半是因为程序在结束前崩溃
    return head;
}
int read_document(RecordItem p[], int *quantity)
{
    FILE *fp = fopen("record.txt", "r");
    char buffer[300];
    int m, i;
    m = i = 0;
    *quantity = m;
    if (fp == NULL){return 0;}
    while (fgets(buffer, 299, fp) != NULL)
    {
        char temp[100] = {0};
        char status[100] = {0};
        char Type[20] = {0};
        buffer[strcspn(buffer, "\r\n")] = 0;
        sscanf(buffer, " %d, %[^,], %[^,], %f, %d, %14[^,], %29[^\n]", &p[i].userID, p[i].productName,
                Type, &p[i].price, &p[i].quantity, status, temp);
        p[i].productType = getProductType(Type);// 转换商品类型字符串为枚举值
        p[i].paymentStatus = getPaymentStatus(status);
        p[i].purchaseTime = parseTimeString(temp);
        p[i].next = NULL;
        m += p[i].quantity;
        i++;
    }
    *quantity = m;
    fclose(fp);
    return i;
}
enum ProductType getProductType(const char* typeStr) {
    if (strcmp(typeStr, "DRINK") == 0) return DRINK;
    if (strcmp(typeStr, "SNACK") == 0) return SNACK;
    if (strcmp(typeStr, "INSTANTFOOD") == 0) return INSTANTFOOD;
    if (strcmp(typeStr, "CANDY") == 0) return CANDY;
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
int compareTime(struct tm* tm1, struct tm* tm2) {
    time_t time1 = mktime(tm1);
    time_t time2 = mktime(tm2);
    return difftime(time1, time2);
}
void sequence_by_time(RecordItem p[], int length)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length - 1; j++)
        {
            if (compareTime(&p[j].purchaseTime, &p[j + 1].purchaseTime) < 0)
                swap(&p[j], &p[j + 1]);
        }
    }
}
void swap(RecordItem *p, RecordItem *q)
{
    RecordItem temp = *p;
    *p = *q;
    *q = temp;
}
RecordItem *Create_node(RecordItem input[], int length)
{
    for (int i = 0; i < length - 1; i++)
        input[i].next = &input[i + 1];
    return &input[0];
}//禁止使用假链表,oj上提交释放内存时会导致崩溃