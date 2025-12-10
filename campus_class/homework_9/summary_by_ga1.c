#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calc.h"

struct people
{
    int id;
    char gender;
    int age;
};

int is_0_17(double age) { return (age >= 0 && age <= 17); }
int is_18_35(double age) { return (age >= 18 && age <= 35); }
int is_36_60(double age) { return (age >= 36 && age <= 60); }
int is_60_plus(double age) { return (age > 60); }

int *countifs_manual(struct people ar[], int num);

int main(void)
{
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) return 1;

    FILE *fp1 = fopen("summary.txt", "w");
    if (fp1 == NULL) { fclose(fp); return 1; }

    int i = 0;
    struct people human[100];
    char buffer[100];
    double m_ages[100]; 
    int m_count = 0;
    
    double f_ages[100]; 
    int f_count = 0;
    
    double all_ages[100];

    condition_func rule_0_17[] = {is_0_17};
    condition_func rule_18_35[] = {is_18_35};
    condition_func rule_36_60[] = {is_36_60};
    condition_func rule_60_plus[] = {is_60_plus};

    while (fgets(buffer, 99, fp) != NULL && i < 100)
    {
        sscanf(buffer, "%d %c %d", &human[i].id, &human[i].gender, &human[i].age);
        
        all_ages[i] = (double)human[i].age;

        if (human[i].gender == 'M') {
            m_ages[m_count] = (double)human[i].age;
            m_count++;
        } else if (human[i].gender == 'F') {
            f_ages[f_count] = (double)human[i].age;
            f_count++;
        }
        
        i++;
    }

    double aver = AVERAGE(all_ages, i);
    double max_age = MAX(all_ages, i);

    int m_0_17_cnt = COUNTIFS(m_ages, m_count, rule_0_17, 1);
    int m_18_35_cnt = COUNTIFS(m_ages, m_count, rule_18_35, 1);
    int m_36_60_cnt = COUNTIFS(m_ages, m_count, rule_36_60, 1);
    int m_60_plus_cnt = COUNTIFS(m_ages, m_count, rule_60_plus, 1);

    int f_0_17_cnt = COUNTIFS(f_ages, f_count, rule_0_17, 1);
    int f_18_35_cnt = COUNTIFS(f_ages, f_count, rule_18_35, 1);
    int f_36_60_cnt = COUNTIFS(f_ages, f_count, rule_36_60, 1);
    int f_60_plus_cnt = COUNTIFS(f_ages, f_count, rule_60_plus, 1);

    fprintf(fp1, "Total: %d\nAverage Age: %.1lf\nMax Age: %.lf\n\n", i, aver, max_age);
    fprintf(fp1, "M: %d\nF: %d\n\n", m_count, f_count);
    fprintf(fp1, "Age Groups (M):\n0-17: %d\n18-35: %d\n36-60: %d\n60+: %d\n\n",
            m_0_17_cnt, m_18_35_cnt, m_36_60_cnt, m_60_plus_cnt); 
    fprintf(fp1, "Age Groups (F):\n0-17: %d\n18-35: %d\n36-60: %d\n60+: %d",
            f_0_17_cnt, f_18_35_cnt, f_36_60_cnt, f_60_plus_cnt);
    fclose(fp);
    fclose(fp1);
    return 0;
}