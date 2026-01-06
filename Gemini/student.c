typedef struct Student
{
    int id;
    char name[10];
    int score;
}Student;
#include <stdio.h>
#include <stdlib.h>
#define NUMBER 10
int compar(const void *first, const void *second);
int main(void)
{
    Student class1[NUMBER] = 
    {
        {1, "Bob", 90},
        {2, "Alice", 60},
        {3, "Alex", 40},
        {4, "Altman", 100},
        {5, "Chaollot", 95},
        {6, "Peter", 96},
        {7, "Black", 94},
        {8, "Michael", 83},
        {9, "Minga", 72},
        {10, "MAGA", 90},
    };
    qsort(class1, 10, sizeof(Student), compar);
    FILE *fp = fopen("student.txt", "w");
    for (int num = 0; num < NUMBER; num++)
        fprintf(fp, "Index: %d\nName: %s\nScore: %d\n", class1[num].id, class1[num].name,
                class1[num].score);
    fclose(fp);
    return 0;
}
int compar(const void *first, const void *second)
{
    const Student *one = (const void *)first;
    const Student *two = (const void *)second;
    return one->score - two->score;
}