#include <stdio.h>
#include <stdlib.h>
struct Student
{
    char name[20];
    int score;
};
int findHighestStudents(struct Student *arr, int size, struct Student ***resultPtr);
int main(void)
{
    int num, i;
    struct Student **result = NULL;

    printf("Please enter the number of students: \n");
    scanf("%d", &num);
    struct Student *class = malloc(num * sizeof(struct Student));
    printf("Please enter %d students' name and score: \n", num);
    for (int n = 0; n < num; n++)
        scanf("%s%d", class[n].name, &class[n].score);
    i = findHighestStudents(class, num, &result);
    printf("Highest score: %d", result[0]->score);
    for (int n = 0; n < i; n++)
        printf("Name: %s\nScore: %d\n", result[n]->name, result[n]->score);
    
    return 0;
}
int findHighestStudents(struct Student *arr, int size, struct Student ***resultPtr)
{
    int highest, n, j;
    n = j = 0;
    highest = arr[0].score;
    for (int num = 0; num < size; num++)
    {
        if (arr[num].score > highest)
            highest = arr[num].score;
    }
    for (int num = 0; num < size; num++)
    {    
        if (arr[num].score == highest)
            n += 1;
    }
    *resultPtr = malloc(n * sizeof(struct Student*));
    for (int num = 0; num < size; num++)
    {    
        if (arr[num].score == highest)
        {    
            (*resultPtr)[j] = &arr[num];
            j++;
        }
    }

    return n;
}