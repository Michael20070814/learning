#include <stdio.h>
char * find_space(char * st)
{
    int i = 0;
    while (st[i] != ' ' && st[i] != '\0')//要能够结束
    {
        i++;
    }
    if (st[i] = '\0')
        return NULL;
    else
        return st[i];
}
