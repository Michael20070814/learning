#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_NAME_LENGTH 50
#define CATEGORY_OF_DISCOUNT 5

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
bool judge_new(int user_id, struct RecordItem *historyRecords);
bool judge_first_five(struct RecordItem *historyRecords);
bool judge_50(int price);
bool judge_A(struct RecordItem *currentCart);
bool judge_B(struct RecordItem *currentCart);
float calc_price(struct RecordItem *currentCart);
float find_smallest(float input[], int length);
float calculateDiscount(const struct RecordItem *historyRecords,
                       const int userId,
                       const struct tm *purchaseTime,
                       const struct RecordItem *currentCart)
{
    float price;
    float result[CATEGORY_OF_DISCOUNT];
    price = calc_price(currentCart);
    if (judge_new(userId, historyRecords))
        result[0] = 0.85 * price;
    else
        result[0] = price;
    if (judge_first_five(historyRecords))
        result[1] = 0.9 * price;
    else
        result[1] = price;
    if (judge_50(price))
        result[2] = price - 10 * ((int) price / 50);
    else
        result[2] = price;
    if (judge_A(currentCart))
        result[3] = price * 0.95;
    else
        result[3] = price;
    if (judge_B(currentCart))
        result[4] = price * 0.9;
    else
        result[4] = price;
    price = find_smallest(result, CATEGORY_OF_DISCOUNT);

    return price;
}
bool judge_new(int user_id, struct RecordItem *historyRecords)
{
    struct RecordItem *p = historyRecords;
    while (p != NULL)
    {
        if (p -> userID == user_id)
            return false;
            p = p -> next;
    }
    return true;
}
bool judge_first_five(struct RecordItem *historyRecords)
{
    int today, times;
    times = 0;
    today = historyRecords[0].purchaseTime.tm_mday;
    struct RecordItem *p = historyRecords;
    while (p != NULL && today == p -> purchaseTime.tm_mday)
    {
            p = p->next;
            times += 1;
    }
    if (times >= 5)
        return false;
    else
        return true;
}
bool judge_50(int price)
{
    if (price >= 50)
        return true;
    else 
        return false;
}
bool judge_A(struct RecordItem *currentCart)
{
    int value = 0;
    int value2 = 0;
    struct RecordItem *p = currentCart;
    while (p != NULL)
    {
        if(p->productType == DRINK)// 购买了饮品
            value = 1;
        if (p -> productType == SNACK) // 购买零食
            value2 = 1;
        p = p-> next;
    }
    if (value == 1 && value2 == 1)
        return true;
    return false;
}
bool judge_B(struct RecordItem *currentCart)
{
    int value = 0;
    int value2 = 0;
    struct RecordItem *p = currentCart;
    while (p != NULL)
    {
        if(strcmp(p->productName, "Juice") == 0)
            value = 1;
        if (p -> productType == INSTANTFOOD)
            value2 = 1;
        p = p -> next;
    }
    if (value == 1 && value2 == 1)
            return true;
    return false;
}
float calc_price(struct RecordItem *currentCart)
{
    float money = 0;
    struct RecordItem *p = currentCart;
    while (p != NULL)
    {
        money += p -> price * p -> quantity;
        p = p -> next;
    }
    return money;
}
float find_smallest(float input[], int length)
{
    float temp = input[0];
    for (int num = 1; num < length; num++)
    {
        if (input[num] < temp)
            temp = input[num];
    }
    return temp;
}