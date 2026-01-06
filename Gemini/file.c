#include <stdio.h>
int main(void)
{
    FILE *fp = fopen("student.txt", "a+");
    fprintf(fp, "Hello World");
    char buffer[100];
    rewind(fp); // 光标归位
    fgets(buffer, 99, fp);
    printf(buffer);
    fclose(fp);
}