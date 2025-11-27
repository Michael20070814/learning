#define LEN 100
#include <stdio.h>
#include <string.h>
int find_repeat(char arr[], char srh[], int size_srh);
int main(void)
{
    int i;
    char s[LEN];
    char retrival[LEN];
    scanf("%s", s);
    scanf("%s", retrival);
    i = find_repeat(s, retrival, strlen(retrival));
    printf("%d", i);
    return 0;
}
int find_repeat(char arr[], char srh[], int size_srh)
{
    int count, max_appear;
    max_appear = 0;
    const char *p = arr;
    const char *q;
    while ((q = strstr(p, srh)) != NULL)
    {
        count = 0;
        

        while (!strncmp(q, srh, size_srh))
        {
            count++;
            q += size_srh;
        }

        if (count > max_appear)
            max_appear = count;

        p = q;
    }
    return max_appear;
}