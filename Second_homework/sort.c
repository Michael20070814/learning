#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    char display_name[35];
    char phone[12];
} Entry;

int compare(const void *a, const void *b) 
{
    return strcmp(((Entry*)a)->display_name, ((Entry*)b)->display_name);
}

int main()  // 边读取边处理
{
    int n;
    scanf("%d", &n);
    
    char names[100][21];
    char phones[100][12];
    int name_count[100]; // 记录对应名字出现次数
    int total = 0;
    
    Entry entries[100];
    int entry_count = 0;
    
    // 记录唯一姓名列表
    char unique_names[100][21];
    int unique_count = 0;
    
    for (int i = 0; i < n; i++) 
    {
        char name[21], phone[12];
        scanf("%s %s", name, phone);
        
        // 检查是否完全重复
        int duplicate = 0;
        for (int j = 0; j < entry_count; j++) 
        {
            // 直接比较原始输入更简单，用另一个数组记录原始名
            if (strcmp(names[j], name) == 0 && strcmp(phones[j], phone) == 0) 
            {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) continue;
        
        // 记录原始姓名和电话
        strcpy(names[entry_count], name);
        strcpy(phones[entry_count], phone);
        
        // 查找该姓名出现与否
        int found = -1;
        for (int j = 0; j < unique_count; j++) 
        {
            if (strcmp(unique_names[j], name) == 0) 
            {
                found = j;
                break;
            }
        }
        
        if (found == -1) 
        {
            // 首次出现
            strcpy(unique_names[unique_count], name);
            name_count[unique_count] = 0;
            strcpy(entries[entry_count].display_name, name);
            unique_count++;
        }
        else 
        {
            // 重复姓名
            name_count[found]++; // 记录对应名字出现次数
            sprintf(entries[entry_count].display_name, "%s_%d", name, name_count[found]);
        }
        
        strcpy(entries[entry_count].phone, phone);
        entry_count++;
    }
    
    // 按姓名排序
    qsort(entries, entry_count, sizeof(Entry), compare);
    
    // 输出
    for (int i = 0; i < entry_count; i++)
        printf("%s %s\n", entries[i].display_name, entries[i].phone);
    
    return 0;
}