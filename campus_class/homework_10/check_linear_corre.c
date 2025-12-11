#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "calc.h"
typedef struct time_buy
{
    struct tm time;
    bool judge;
}time_buy;
int read_data(time_buy *input);
void output_data(double coefficient);
void class_data(double *arr, time_buy *input, int num);
void checkLinearCorrelation(void);
int main(void)
{
    checkLinearCorrelation();

    return 0;
}
void checkLinearCorrelation(void)
{
    time_buy log[100];
    double classification[8] = {0};
    double time[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    double Linear_relationship;
    memset(log, 0, sizeof(log));
    int data_num = read_data(log);
    class_data(classification, log, data_num);
    Linear_relationship = CORREL(classification, time, 8);
    output_data(Linear_relationship);
}
int read_data(time_buy *input)
{
    FILE *fp = fopen("record.txt", "r");
    char buffer[100];
    int i = 0;
    while (fgets(buffer, 99, fp))
    {
        int n1, n2;
        char temp[10];
        sscanf(buffer, "%*[^,],%*[^,],%*[^,], %[^,]", temp);
        if (strcmp(temp, "Success") == 0)
        {    
            input->judge = true;
            sscanf(buffer, "%*[^,],%*[^,],%*[^,], %*[^,], %d-%d-%d %d:%d:%d", &n1, 
                &n2, &input[i].time.tm_mday, &input[i].time.tm_hour, &input[i].time.tm_min,
                &input[i].time.tm_sec);
            i++;
        }
    }
    fclose(fp);
    return i;
}
void class_data(double *arr, time_buy *input, int num)
{
    for (int i = 0; i < num; i++)
    {
        if (input[i].time.tm_hour <= 3 && input[i].time.tm_hour > 0)
            arr[0] += 1;
        if (input[i].time.tm_hour <= 6 && input[i].time.tm_hour > 3)
            arr[1] += 1;
        if (input[i].time.tm_hour <= 9 && input[i].time.tm_hour > 6)
            arr[2] += 1;
        if (input[i].time.tm_hour <= 12 && input[i].time.tm_hour > 9)
            arr[3] += 1;
        if (input[i].time.tm_hour <= 15 && input[i].time.tm_hour > 12)
            arr[4] += 1;
        if (input[i].time.tm_hour <= 18 && input[i].time.tm_hour > 15)
            arr[5] += 1;
        if (input[i].time.tm_hour <= 21 && input[i].time.tm_hour > 18)
            arr[6] += 1;
        if (input[i].time.tm_hour <= 24 && input[i].time.tm_hour > 21)
            arr[7] += 1;
    }
}
void output_data(double coefficient)
{
    FILE *fp = fopen("result.txt", "a");
    if (coefficient >= 0.8 || coefficient <= -0.8)
        fputs("Linear", fp);
    else
        fputs("Not Linear", fp);
    fclose(fp);
}