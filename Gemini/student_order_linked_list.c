#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 【必须加】为了用 strcpy 交换名字

// 【修正1】必须加 struct 后的标签名 Node，否则内部不能定义 next 指针
typedef struct Node
{
    char name[20];
    int score;
    struct Node *next; 
} Student;

Student *input(int *num);
void swap(Student *p1, Student *p2);
void order(Student *head, int number);    // 参数名改成了 head 方便理解
void print_student(Student *head, int number);

int main(void)
{
    int student_number = 0;
    // input 会把人数填入 student_number
    Student *list = input(&student_number);
    
    // 只有有人数才排序，防止崩溃
    if (student_number > 0) {
        order(list, student_number);
        print_student(list, student_number);
    }

    // 考试时间不够可以不写 free，系统会自动回收，先把功能跑通最重要
    return 0;
}

// 【修正2】链表交换最忌讳直接 *p1=*p2，那样链表就断了！
// 必须只交换“数据域”（名字和分数），不要动 next 指针
void swap(Student *p1, Student *p2)
{
    // 1. 交换分数
    int temp_score = p1->score;
    p1->score = p2->score;
    p2->score = temp_score;

    // 2. 交换名字 (字符串不能直接等号赋值，要用 strcpy)
    char temp_name[20];
    strcpy(temp_name, p1->name);
    strcpy(p1->name, p2->name);
    strcpy(p2->name, temp_name);
}

Student *input(int *num)
{
    char ch;
    int count = 0; // 必须在函数里计数

    Student *head = (Student *)malloc(sizeof(Student));
    // 安全检查，防止空指针
    if(head == NULL) return NULL; 

    Student *p;
    
    printf("Please enter the 1st student's name and score.\n");
    // head->name 不需要取地址&，head->score 需要取地址&
    scanf("%s%d", head->name, &head->score);
    head->next = NULL; // 【重要】一定要封口
    count++;           // 计数 +1
    
    getchar(); // 吃掉 scanf 留下的回车

    printf("Do you want to continue to input another student ?(y/n)\n");
    p = head;
    
    // 这里的逻辑帮你修整了一下，更稳健
    while ((ch = getchar()) == 'y')
    {
        p->next = (Student *)malloc(sizeof(Student));
        p = p->next; // 指针后移
        
        printf("Please enter name and score:\n");
        scanf("%s%d", p->name, &p->score);
        p->next = NULL; // 【重要】新节点必须封口
        count++;        // 计数 +1

        getchar(); // 吃掉 scanf 留下的回车
        printf("Do you want to continue to input another student ?(y/n)\n");
        // 这里不需要再 getchar() 了，因为上面的 getchar 吃掉了回车，留给下一次循环判断
    }
    
    *num = count; // 【重要】把数出来的人数传出去
    return head;
}

// 【修正3】链表排序不能用 list[n]，必须用指针 p 移动
void order(Student *head, int number)
{
    if (head == NULL || head->next == NULL) return;

    // 外层循环控制次数，还是用 m
    for (int m = 0; m < number - 1; m++)
    {
        Student *p = head; // 每次都要从头开始跑
        
        // 内层循环：用指针 p 往后跳
        // 注意范围是 number - 1 - m
        for (int n = 0; n < number - 1 - m; n++)
        {
            // 比较 p 和 p的下一个节点
            if (p->score < p->next->score) // 降序
            {
                swap(p, p->next); // 交换数据
            }
            p = p->next; // 指针向后移动
        }
    }
}

// 【修正4】打印也不能用下标，要用 while 循环
void print_student(Student *head, int number)
{
    Student *p = head;
    while (p != NULL) // 只要 p 不是空就打印
    {
        printf("%s\t%d\n", p->name, p->score);
        p = p->next; // 移到下一个
    }
}