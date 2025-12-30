#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
struct RecordItem{
    int userID; // 用户ID
    enum ProductType productType; // 商品类型
    char productName[MAX_NAME_LENGTH]; // 商品名称
    float price; // 销售价格
    int quantity; // 销售数量
    enum PaymentStatus paymentStatus; // 支付状态
    struct tm purchaseTime; // 购买时间
    struct RecordItem* next;
};

// 字符串转商品类型
enum ProductType getProductType(const char* typeStr) {
    if (strcmp(typeStr, "DRINK") == 0) return DRINK;
    if (strcmp(typeStr, "SNACK") == 0) return SNACK;
    if (strcmp(typeStr, "INSTANTFOOD") == 0) return INSTANTFOOD;
    if (strcmp(typeStr, "CANDY") == 0) return CANDY;
    return OTHER;
}

// 字符串转支付状态
enum PaymentStatus getPaymentStatus(const char* statusStr) {
    if (strcmp(statusStr, "Success") == 0) return SUCCESS;
    if (strcmp(statusStr, "Failed") == 0) return FAILED;
    return PENDING;
}

// 解析时间字符串
struct tm parseTimeString(const char* timeStr) {
    struct tm tm_time = {0};
    sscanf(timeStr, "%d-%d-%d %d:%d:%d",
           &tm_time.tm_year, &tm_time.tm_mon, &tm_time.tm_mday,
           &tm_time.tm_hour, &tm_time.tm_min, &tm_time.tm_sec);
    tm_time.tm_year -= 1900;  // 年份从1900开始计算
    tm_time.tm_mon -= 1;      // 月份从0开始计算
    tm_time.tm_isdst = -1;    // 不考虑夏令时
    return tm_time;
}

// 比较两个时间
int compareTime(struct tm* tm1, struct tm* tm2) {
    time_t time1 = mktime(tm1);
    time_t time2 = mktime(tm2);
    return difftime(time1, time2);
}

// 格式化输出时间
void printTime(struct tm* t) {
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", 
           t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
           t->tm_hour, t->tm_min, t->tm_sec);
}

struct RecordItem* readRecordItemsFromFile(void) {
    FILE* file = fopen("record.txt", "r");
    if (file == NULL) {
        printf("无法打开文件 record.txt\n");
        return NULL;
    }
    
    struct RecordItem* head = NULL;
    int totalQuantity = 0;
    struct tm earliestTime = {0}, latestTime = {0};
    int firstRecord = 1; // 标记是否是第一条记录
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // 移除行尾的换行符
        line[strcspn(line, "\n")] = 0;//计算出\n的下标
        
        // 解析CSV格式的每一行
        char* token;
        char* tokens[7];
        int i = 0;
        
        token = strtok(line, ",");
        while (token != NULL && i < 7) {
            // 去除首尾空格
            while (*token == ' ') token++;
            char* end = token + strlen(token) - 1;
            while (end > token && *end == ' ') {
                *end = '\0';
                end--;
            }
            tokens[i++] = token;
            token = strtok(NULL, ",");
        }//把字符串分割并进行储存
        
        if (i == 7) {
            // 创建新节点
            struct RecordItem* newItem = (struct RecordItem*)malloc(sizeof(struct RecordItem));
            
            // 填充数据
            newItem->userID = atoi(tokens[0]);
            strncpy(newItem->productName, tokens[1], MAX_NAME_LENGTH - 1);
            newItem->productName[MAX_NAME_LENGTH - 1] = '\0';
            newItem->productType = getProductType(tokens[2]);
            newItem->price = atof(tokens[3]);
            newItem->quantity = atoi(tokens[4]);
            newItem->paymentStatus = getPaymentStatus(tokens[5]);
            newItem->purchaseTime = parseTimeString(tokens[6]);
            newItem->next = NULL;
            
            // 更新总数量
            totalQuantity += newItem->quantity;
            
            // 更新最早和最晚时间
            if (firstRecord) {
                earliestTime = newItem->purchaseTime;
                latestTime = newItem->purchaseTime;
                firstRecord = 0;
            } else {
                if (compareTime(&newItem->purchaseTime, &earliestTime) < 0) {
                    earliestTime = newItem->purchaseTime;
                }
                if (compareTime(&newItem->purchaseTime, &latestTime) > 0) {
                    latestTime = newItem->purchaseTime;
                }
            }
            
            // 插入链表（按照购买时间从晚到早排序）
            if (head == NULL) {
                head = newItem;
            } else {
                // 找到合适的位置插入
                struct RecordItem* current = head;
                struct RecordItem* prev = NULL;
                
                while (current != NULL && 
                       compareTime(&newItem->purchaseTime, &current->purchaseTime) <= 0) {
                    prev = current;
                    current = current->next;
                }
                
                if (prev == NULL) {
                    // 插入到链表头部
                    newItem->next = head;
                    head = newItem;
                } else {
                    // 插入到prev和current之间
                    prev->next = newItem;
                    newItem->next = current;
                }
            }
        }
    }
    
    fclose(file);
    
    // 输出结果
    if(totalQuantity==0){
        printf("%d\n", totalQuantity);
    }
    else{
        printf("%d\n", totalQuantity);
        printTime(&latestTime);
        printTime(&earliestTime);
    }
    
    return head;
}