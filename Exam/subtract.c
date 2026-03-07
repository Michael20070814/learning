#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const char *a, const char *b) // 判断大小，保证为正
{
    int la = strlen(a), lb = strlen(b);
    if (la > lb)
        return 1;
    else if (la < lb)
        return -1;
    
    char *p = a;
    char *q = b;

    while (*p != '\0')
    {
        if (*p > *q)
            return 1;
        else if (*p < *q)
            return -1;
        p++;
        q++;
    }
    return 0;
}

char *subtract(const char *a, const char *b) // 字符串减法实现
{
    int la = strlen(a), lb = strlen(b);
    char *result = (char *)calloc(la + 1, sizeof(char));
    
    int borrow = 0;
    int i = la - 1, j = lb - 1, k = la - 1;
    
    while (i >= 0) 
    {
        int da = a[i] - '0';
        int db = (j >= 0) ? b[j] - '0' : 0;
        int subtr = da - db - borrow;
        
        if (subtr < 0) 
        {
            subtr += 10;
            borrow = 1;
        }
        else 
        {
            borrow = 0;
        }
        
        result[k--] = subtr + '0';
        i--; j--;
    }
    
    char *p = result;
    while (*p == '0' && *(p + 1) != '\0') p++;
    
    return p;
}

int main() {
    char a[1000], b[1000];
    scanf("%s", a);
    scanf("%s", b);
    
    int cmp = compare(a, b);
    if (cmp == 0) 
    {
        printf("0\n");
    } 
    else if (cmp > 0) 
    {
        printf("%s\n", subtract(a, b));
    } else 
    {
        printf("-%s\n", subtract(b, a));
    }
    return 0;
}