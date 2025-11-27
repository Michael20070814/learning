#include <stdio.h>
int main()
{
    FILE *fp;
    char x[200];

    fp = fopen("test.txt", "w");
    if (!fp)
        return 0;
    fprintf(fp, "Hello C!\n");
    fputs("This is a test.\n", fp);
    fclose(fp);
    
    fp = fopen("test.txt", "r");
    fscanf(fp, "%s", &x);
    printf("%s", x);
    return 0;
}