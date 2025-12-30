#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
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

typedef struct Client_cost // 构造输出的结构体
{
    int userID;
    int times;
    float money;
}Client_cost;
void sequence(Client_cost list[], int length);
void write_into_doc(Client_cost list[], int length);
void swap(Client_cost *obj1, Client_cost *obj2);
int search_client(Client_cost list[], int userID, int length);
int convert_array(struct RecordItem *historyRecords, int length, Client_cost array[]);
struct RecordItem *Delete_Fail(const struct RecordItem * historyRecords, int *num);
void reportConsumerSummary(const struct RecordItem *historyRecords)
{
    struct RecordItem *object;
    int length;
    object = Delete_Fail(historyRecords, &length);
    Client_cost rubbish[length];
    length = convert_array(object, length, rubbish);//先转换一遍，获取长度
    Client_cost result[length];
    convert_array(object, length, result);//获取正式数组
    sequence(result, length);
    write_into_doc(result, length);
}
struct RecordItem *Delete_Fail(const struct RecordItem * historyRecords, int *num)
{
    struct RecordItem *origin = historyRecords;
    struct RecordItem *new_head = NULL;
    struct RecordItem *tail = NULL;
    struct RecordItem *new_node;
    int temp = 0;
    while (origin != NULL)
    {
        if (origin -> paymentStatus == SUCCESS)
        {    
            new_node = (struct RecordItem *) malloc(sizeof(struct RecordItem));//找到一块数据再分配内存
            *new_node = *origin;
            if (new_head == NULL)
            {    
                new_head = new_node;
                tail = new_node;
            }
            else
            {   
                tail -> next = new_node;
                tail = tail -> next;
                tail -> next = NULL;
            }
            temp++;
        }
        origin = origin -> next;
    }
    *num = temp;
    /*while (origin != NULL)
    {
        if (origin -> paymentStatus == SUCCESS)
        {    
            *search = *origin;
            search -> next = (struct RecordItem *) malloc(sizeof(struct RecordItem));//书写错误，无论有几个数据最后会多出来一个僵尸数据
            search = search -> next;
            search -> next = NULL;
            temp++;
        }
        origin = origin -> next;
    }
    search = NULL;
    *num = temp - 1;//num是一个交易记录的总次数*/
    return new_head;
}
int convert_array(struct RecordItem *historyRecords, int length, Client_cost array[])//length应该是用户的数量
{ // 把用户的不同交易记录合成消费总额
    struct RecordItem *origin = historyRecords;
    memset(array, 0, sizeof(Client_cost) * length);
    int index = 0;
    int obj;
    while (origin != NULL)
    {
        obj = search_client(array, origin -> userID, index);
        if (obj != -1)
        {
            array[obj].money += origin -> price * origin -> quantity;
            array[obj].times += 1;
        }
        else
        {
            array[index].userID = origin -> userID;
            array[index].money += origin -> price * origin -> quantity;
            array[index].times += 1;
            index++;
        }
        origin = origin -> next;
    }
    return index;
}
int search_client(Client_cost list[], int userID, int length)
{
    for (int num = 0; num < length; num++)
    {
        if (list[num].userID == userID)
            return num;
    }
    return -1;
}
void sequence(Client_cost list[], int length)
{
    for (int num = 0; num < length; num++)
    {
        for (int i = 0; i < length - 1; i++)
        {
            if (list[i].money < list[i + 1].money)
                swap(&list[i], &list[i + 1]);
            if (list[i].money == list[i + 1].money && list[i].times < list[i + 1].times)
                swap(&list[i], &list[i + 1]);
            if (list[i].money == list[i + 1].money && list[i].userID > list[i + 1].userID)
                swap(&list[i], &list[i + 1]);//三个条件多重判定
        }
    }
/*   for (int num = 0; num < length; num++)
        for (int i = 0; i < length - 1; i++)
            if (list[i].money == list[i + 1].money && list[i].times < list[i + 1].times)
                swap(&list[i], &list[i + 1]);
    for (int num = 0; num < length; num++)
        for (int i = 0; i < length - 1; i++)
            if (list[i].money == list[i + 1].money && list[i].userID > list[i + 1].userID)
                swap(&list[i], &list[i + 1]);*/
}
void swap(Client_cost *obj1, Client_cost *obj2)
{
    Client_cost temp;
    temp = *obj1;
    *obj1 = *obj2;
    *obj2 = temp;
}
void write_into_doc(Client_cost list[], int length)
{
    FILE *fp = fopen("summary.txt", "a");
    for (int num = 0; num < length; num++)
        fprintf(fp, "%d %.2f %d\n", list[num].userID, list[num].money, list[num].times);
    fclose(fp);
}