#include <stdio.h>
typedef struct student
{
    int id;
    int score;
    char name[10];
}student;
void make_UI(void);
int read_information(student arr[]);
void print_information(student arr[], int length);
void write_information(student obj);
int main(void)
{
    student save[100];
    student temp;
    int number, choice;
    make_UI();
    scanf("%d", &choice);
    while (choice != 3)
    {
        switch (choice)
        {
            case 1:
            printf("Please enter new student' information. \n");
            scanf("%d %9s %d", &temp.id, temp.name, &temp.score);//限制只可以读入9个字母
            write_information(temp);
            break;
            case 2:
            number = read_information(save);
            if (number == 0)
            {   
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

    return 0;
}
int read_information(student arr[])//最好加入一个数组的最大长度，防止越界读入
{
    FILE *fp = fopen("student.txt", "r");
    char buffer[100];
    int i = 0;
    if (fp == NULL)
    {    
        printf("Error opening file");//当文件不存在时，强行打开文件
        return 0;
    }
    while (fgets(buffer, 99, fp) != NULL)
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
void write_information(student obj)
{
    FILE *fp = fopen("student.txt", "a");
    fprintf(fp, "%d %s %d\n", obj.id, obj.name, obj.score);
    fclose(fp);
}
void make_UI(void)
{
    printf("Please select what you want to do from three numbers below:\n");
    printf("1. Add new student. \n");
    printf("2. Display total students' information. \n");
    printf("3. Quit. \n");
}