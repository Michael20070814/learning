#include <stdio.h>
int sum(int i, int p);
void print(int start, int count, FILE *fp);

int main(void)
{
    int num, i, object;
    FILE *fp = fopen("scpi.in", "r");
    FILE *fp1 = fopen("scpi.out", "a");
    fscanf(fp, "%d", &num);
    for (i = 1; i <= num / 2; i++)
    {    
        if ((object = sum(i, num)))
            break;
    }
    if (sum(i, num))
    {   
        fprintf(fp1, "%d=", num);
        print(i, object, fp1);
    }
    else
        fprintf(fp1, "%d:NOANSWER", num);
    fclose(fp);
    fclose(fp1);
}
int sum(int i, int p)
{
    int j, sum;
    sum = 0;   
    for (j = 0; sum <= p; j++)
    {    
        sum += (i + j);
        if (sum == p)
            break;
    }
    if (sum == p)
        return j + 1;
    else
        return 0;
}
void print(int start, int count, FILE *fp)
{
    for (int t = start; t < start + count - 1; t++)
        fprintf(fp, "%d+", t);
    fprintf(fp, "%d", start + count - 1);
}