#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
typedef struct client
{
    int id;
    char password[50];
    struct tm black;
    struct tm open;
}client;
int value;
int read_user(client *customer);
void read_black(client *customer, int num);
int judge_client(int id, char *pwd, client *customer, int num);
bool judge_time(client customer, char *now);
time_t analyse_time(char *now);
int login(int id, char *pwd, char *now);
int main(void)
{
    int num = login(9999, "Pq2R8sTv", "2025-12-02 09:00:00");
    printf("%d\n", num);

    return 0;
}
int login(int id, char *pwd, char *now)
{
    value = 0;
    client customer_group[20];
    int total_customer, index;
    memset(customer_group, 0, sizeof(customer_group));
    total_customer = read_user(customer_group);
    index = judge_client(id, pwd, customer_group, total_customer);
    switch (value)
    {
        case 0:
        return 0;
        case 1:
        return 1;
        case 2:
        break;
    }
    read_black(customer_group, total_customer);
    if (judge_time(customer_group[index], now))
        return 2;
    else
        return 3;
}
int read_user(client *customer)
{
    FILE *fp = fopen("users.txt", "r");
    char buffer[100];
    int rubbish;
    int i = 0;
    while (fgets(buffer, 100, fp) != NULL)
    {
        sscanf(buffer, "%d,%*[^,],%[^,],%d", &customer[i].id, customer[i].password,
                &rubbish);
        i++;
    }
    fclose(fp);
    return i;
}
int judge_client(int id, char *pwd, client *customer, int num)
{
    int i;
    for (i = 0; i < num; i++)
    {
        if (customer[i].id == id)
        {    
            value += 1;
            if (strcmp(customer[i].password, pwd) == 0)
                value += 1;
            break;
        }
    }
    if (i == num)
        return -1;
    else
        return i;
}
void read_black(client *customer, int num)
{
    FILE *fp = fopen("blacklist.txt", "r");
    char buffer[100];
    int index;
    if (fp != NULL)
    {
        while (fgets(buffer, 100, fp) != NULL)
        {
            sscanf(buffer, "%d", &index);
            for (int i = 0; i < num; i++)
            {
                int n1, n2, n3, n4;
                if (index == customer[i].id)
                {   
                    if (sscanf(buffer, "%*[^,],%d-%d-%d %d:%d:%d,%d-%d-%d %d:%d:%d", &n3, 
                            &n4, &customer[i].black.tm_mday, 
                            &customer[i].black.tm_hour, &customer[i].black.tm_min, 
                            &customer[i].black.tm_sec, &n1, 
                            &n2, &customer[i].open.tm_mday, 
                            &customer[i].open.tm_hour, &customer[i].open.tm_min, 
                            &customer[i].open.tm_sec) == 12)
                        {
                            customer[i].black.tm_year = n3 - 1900;
                            customer[i].black.tm_mon = n4 - 1;
                            customer[i].black.tm_isdst = 0;
                            customer[i].open.tm_year = n1 - 1900;
                            customer[i].open.tm_mon = n2 - 1;
                            customer[i].open.tm_isdst = 0;
                        }
                    else
                    {   
                        customer[i].open.tm_year = 199;
                        customer[i].open.tm_isdst = 0;
                    }
                }
            }
        }
    }
    fclose(fp);
}
bool judge_time(client customer, char *now)
{
    time_t open = mktime(&customer.open);
    time_t black = mktime(&customer.black);
    if (open <= analyse_time(now) || black > analyse_time(now))
        return false;
    else
        return true;
}
time_t analyse_time(char *now)
{
    struct tm temp;
    int n1, n2;
    sscanf(now, "%d-%d-%d %d:%d:%d", &n1, &n2, &temp.tm_mday, &temp.tm_hour,
            &temp.tm_min, &temp.tm_sec);
    temp.tm_year = n1 - 1900;
    temp.tm_mon = n2 - 1;
    temp.tm_isdst = 0;
    time_t result = mktime(&temp);

    return result;
}