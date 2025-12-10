#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
struct customer
{
    int index;
    struct tm time;
};
typedef struct log
{
    int index;
    struct tm time[10];
    int times;
}log;
int find_latest(struct tm *input, int total);
bool find_24h(struct tm *input, int total);
bool find_48h(struct tm *input, int total);
void updateBlacklist(void);
int main(void)
{
    updateBlacklist();
    return 0;
}
void updateBlacklist(void)
{
    FILE *fp = fopen("record.txt", "r");
    FILE *fp1 = fopen("blacklist.txt", "a");
    struct customer client[50];
    char buffer[100];
    int n, i, client_num, value, journal, n1, n2;
    n = i = client_num = journal = 0;
    log customer1[50];
    memset(customer1, 0, sizeof(customer1));
    float litter;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        sscanf(buffer, "%d, %*[^,],%f, %*[^,],%d-%d-%d %d:%d:%d\n", &client[n].index, 
                &litter, &n1, &n2, 
                &client[n].time.tm_mday, &client[n].time.tm_hour, &client[n].time.tm_min,
                &client[n].time.tm_sec);
        client[n].time.tm_year = n1 - 1900;
        client[n].time.tm_mon = n2 - 1;
        client[n].time.tm_isdst = 0;
        n++;
    }

    for (int num = 0; num < n; num++)
    {
        value = 0;
        for (i = 0; i < client_num; i++)
        {
            if (client[num].index == customer1[i].index)
            {
                value = 1;
                break;
            }
        }
        if (value == 0)
        {
            customer1[i].index = client[num].index;
            for (int temp = num; temp < n; temp++)
            {
                if (customer1[i].index == client[temp].index)
                {
                    customer1[i].time[journal] = client[temp].time;
                    customer1[i].time[journal].tm_isdst = 0;
                    journal++;
                }
            }
            customer1[i].times = journal;
            client_num++;
        }
        journal = 0;
    }

    for (int num = 0; num < client_num; num++)
    {
        if (customer1[num].times >= 5)
        {
            int temp = find_latest(customer1[num].time, customer1[num].times);
            fprintf(fp1, "%d,%04d-%02d-%02d %02d:%02d:%02d,INF\n", customer1[num].index, customer1[num].time[temp].tm_year + 1900, 
                    customer1[num].time[temp].tm_mon + 1, customer1[num].time[temp].tm_mday, 
                    customer1[num].time[temp].tm_hour, customer1[num].time[temp].tm_min,
                    customer1[num].time[temp].tm_sec);
        }
        else if (find_24h(customer1[num].time, customer1[num].times) && !(find_48h(customer1[num].time, customer1[num].times)))
        {
            int temp = find_latest(customer1[num].time, customer1[num].times);
            time_t timestamp = mktime(&customer1[num].time[temp]);
            timestamp += 86400 * 2;
            struct tm *future_tm = localtime(&timestamp);
            fprintf(fp1, "%d,%04d-%02d-%02d %02d:%02d:%02d,%04d-%02d-%02d %02d:%02d:%02d\n", customer1[num].index, customer1[num].time[temp].tm_year + 1900, 
                    customer1[num].time[temp].tm_mon + 1, customer1[num].time[temp].tm_mday, 
                    customer1[num].time[temp].tm_hour, customer1[num].time[temp].tm_min,
                    customer1[num].time[temp].tm_sec, future_tm->tm_year + 1900, 
                    future_tm->tm_mon + 1, future_tm->tm_mday, future_tm->tm_hour,
                    future_tm->tm_min, future_tm->tm_sec);
        }
        else if (find_48h(customer1[num].time, customer1[num].times))
        {
            int temp = find_latest(customer1[num].time, customer1[num].times);
            time_t timestamp = mktime(&customer1[num].time[temp]);
            timestamp += 7 * 86400;
            struct tm *future_tm = localtime(&timestamp);
            fprintf(fp1, "%d,%04d-%02d-%02d %02d:%02d:%02d,%04d-%02d-%02d %02d:%02d:%02d\n", customer1[num].index, customer1[num].time[temp].tm_year + 1900, 
                    customer1[num].time[temp].tm_mon + 1, customer1[num].time[temp].tm_mday, 
                    customer1[num].time[temp].tm_hour, customer1[num].time[temp].tm_min,
                    customer1[num].time[temp].tm_sec, future_tm->tm_year + 1900, 
                    future_tm->tm_mon + 1, future_tm->tm_mday, future_tm->tm_hour,
                    future_tm->tm_min, future_tm->tm_sec);
        }
    }

    fclose(fp1);
    fclose(fp);
}
int find_latest(struct tm *input, int total)//获取所有时间中最新的时间
{
    int temp[total];
    int max, max_index;
    for (int num = 0; num < total; num++)
        temp[num] = mktime(&input[num]);
    max = temp[0];
    max_index = 0;
    for (int i = 1; i < total; i++)
    {
        if (temp[i] > max)
        {
            max = temp[i];
            max_index = i;
        }
    }
    return max_index;
}
bool find_24h(struct tm *input, int total)
{
    int value;
    for (int num = 0; num < total; num++)
    {
        value = 0;
        time_t now = mktime(&input[num]); 
        time_t future = mktime(&input[num]) + 86400;
        for (int i = 0; i < total; i++)
        {
            time_t temp = mktime(&input[i]);
            if (temp <= future && temp >= now)
                value += 1;
        }
        if (value >= 3)
            return true;
    }
    return false;
}
bool find_48h(struct tm *input, int total)
{
    int value;
    for (int num = 0; num < total; num++)
    {
        value = 1;
        time_t now = mktime(&input[num]); 
        time_t future = mktime(&input[num]) + 2 * 86400;
        for (int i = 0; i < total; i++)
        {
            time_t temp = mktime(&input[i]);
            if (temp < future && temp > now)
                value += 1;
        }
        if (value == 4)
            return true;
    }
    return false;
}