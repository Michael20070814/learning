#include <stdio.h>
#define MAX_STUDENT 100
typedef struct student
{
    int id;
    int score;
    char name[10];
}student;
void make_UI(void);
int read_information(student arr[], int max_size);
void print_information(student arr[], int length);
void write_information(student obj[], int num);
int main(void)
{
    student save[MAX_STUDENT];
    int number, choice, temp;
    number = read_information(save, MAX_STUDENT);
    temp = number;
    make_UI();
    scanf("%d", &choice);
    while (choice != 3)
    {
        switch (choice)
        {
            case 1:
            if (number == MAX_STUDENT)
            {   
                printf("Student is full. Don't input more. \n");
                break;
            }
            printf("Please enter new student' information. \n");
            scanf("%d %9s %d", &save[number].id, save[number].name, &save[number].score);
            number++;//限制只可以读入9个字母
            break;
            case 2:
            if (number == 0)
            {   
                printf("Error opening file. \n");
                printf("There is no data. Please enter first. \n");
                break;
            }
            print_information(save, number);
            break;
        }
        make_UI();
        printf("What's the next: \n");
        scanf("%d", &choice);
    }
    write_information(save + temp, number - temp);

    return 0;
}
int read_information(student arr[], int max_size)//最好加入一个数组的最大长度，防止越界读入
{
    FILE *fp = fopen("student1.txt", "r");
    char buffer[MAX_STUDENT];
    int i = 0;
    if (fp == NULL)
        return 0;
    while (fgets(buffer, 99, fp) != NULL && i < max_size)
    {
        sscanf(buffer, "%d%s%d", &arr[i].id, arr[i].name, &arr[i].score);
        i++;
    }
    fclose(fp);
    
    return i;
}
void print_information(student arr[], int length)
{
    for (int i = 0; i < length; i++)
        printf("%d %s %d\n", arr[i].id, arr[i].name, arr[i].score);
}
void write_information(student obj[], int num)
{
    FILE *fp = fopen("student1.txt", "a");
    for (int i = 0; i < num; i++)
        fprintf(fp, "%d %s %d\n", obj[i].id, obj[i].name, obj[i].score);
    fclose(fp);
}
void make_UI(void)
{
    printf("Please select what you want to do from three numbers below:\n");
    printf("1. Add new student. \n");
    printf("2. Display total students' information. \n");
    printf("3. Quit. \n");
}