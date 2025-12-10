#include <stdio.h>
#include <string.h>
int main(void)
{
    char *p;
    char *temp;
    int percentage, total, num = 0;
    char buffer[1025];
    FILE *fp = fopen("filein.c", "r");
    total = fread(buffer, 1, 1024, fp);
    fclose(fp);
    buffer[total] = '\0';
    p = buffer;
    while (p = strstr(p, "/*"))
    {
        p = p + 2;
        temp = strstr(p, "*/");
        while (p != temp)  
        {    
            num++;
            p++;
        }
    }
    percentage = num * 100 / total;
    printf("%d%%", percentage);
    
    return 0;
}