#include <stdio.h>
#include <time.h>
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

// 商品库存结构
struct Product {
    char name[MAX_NAME_LENGTH]; // 商品名称
    enum ProductType type; // 商品类型
    float purchasePrice; // 进货单价
    float salePrice; // 销售单价
    int stock; // 库存数量
    int maxStock; // 最大库存容量
    int minStock; // 最小库存阈值（触发补货）
    struct Product* next;
};
void updateInventory(const struct RecordItem *currentCart,
                     struct Product *currentInventory)
{
    struct Product *head = currentInventory;
    struct Product *p;
    p = head;
    struct RecordItem *q = currentCart;
    while (q != NULL)
    {
        while (p != NULL)
        {
            if (strcmp(p -> name, q -> productName) == 0 && q -> paymentStatus == SUCCESS)
            {    
                p -> stock -= q -> quantity;
                printf("%s %d\n", p -> name, p -> stock);
            }
            p = p -> next;
        }
        p = head;
        q = q -> next;
    }
}