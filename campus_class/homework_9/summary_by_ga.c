#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct people
{
    int id;
    char gender;
    int age;
};
double average(struct people ar[], int num);
int max(struct people ar[], int length);
void swap(struct people *a, struct people *b);
int *countifs(struct people ar[], int num);
int main(void)
{
    FILE *fp = fopen("data.txt", "r");
    FILE *fp1 = fopen("summary.txt", "a");
    int i = 0;
    int *p;

    char buffer[100];
    struct people human[100];
    while (fgets(buffer, 99, fp) != NULL)
    {
        sscanf(buffer, "%d %c %d", &human[i].id, &human[i].gender, &human[i].age);
        i++;
    }
    double aver = average(human, i);
    int max_age = max(human, i);
    p = countifs(human, i);
    fprintf(fp1, "Total: %d\nAverage Age: %.1lf\nMax Age: %d\n\n", i, aver, max_age);
    fprintf(fp1, "M: %d\nF: %d\n\n", p[8], p[9]);
    fprintf(fp1, "Age Groups (M):\n0-17: %d\n18-35: %d\n36-60: %d\n60+: %d\n\n",
            p[0], p[1], p[2], p[3]);
    fprintf(fp1, "Age Groups (F):\n0-17: %d\n18-35: %d\n36-60: %d\n60+: %d",
            p[4], p[5], p[6], p[7]);
    
    fclose(fp);
    fclose(fp1);
}
double average(struct people ar[], int num)
{
    double sum = 0;
    for (int i = 0; i < num; i++)
        sum += ar[i].age;
    return sum / num;
}
int max(struct people ar[], int length)
{
    for (int num = 0; num < length; num++)
        for (int q = 0; q < length; q++)
            if (q< length - 1 && ar[q].age < ar[q + 1].age)
                swap(&ar[q], &ar[q + 1]);
    return ar[0].age;
}
int *countifs(struct people ar[], int num)
{
    int *p = (int *) malloc(sizeof(int) *(10));
    memset(p, 0, sizeof(int) * 10);
    for (int i = 0; i < num; i++)
    {
        if (ar[i].gender == 'M')
        {
            if (ar[i].age >= 0 && ar[i].age <= 17)
                p[0] +=1;
            if (ar[i].age >= 18 && ar[i].age <= 35)
                p[1] +=1;
            if (ar[i].age >= 36 && ar[i].age <= 60)
                p[2] +=1;
            if (ar[i].age > 60)
                p[3] +=1;
            p[8] += 1;
        }
        if (ar[i].gender == 'F')
        {
            if (ar[i].age >= 0 && ar[i].age <= 17)
                p[4] +=1;
            if (ar[i].age >= 18 && ar[i].age <= 35)
                p[5] +=1;
            if (ar[i].age >= 36 && ar[i].age <= 60)
                p[6] +=1;
            if (ar[i].age > 60)
                p[7] +=1;
            p[9] += 1;
        }
    }
    return p;
}
void swap(struct people *a, struct people *b)
{
    struct people temp = *a;
    *a = *b;
    *b = temp;
}