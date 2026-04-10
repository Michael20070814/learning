#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define SIZE 10000

char *input(char *filename);
char *process_buffer(char *buffer, char *replacement, char *be_replaced);
void output(char *filename, char *buffer);
char *search_str(char *src, char *obj);

int main(void)
{
    char in[] = "filein.txt";
    char out[] = "fileout.txt";
    char replace[500]; char be_replace[500];

    char *buffer = input(in);
    scanf("%s", be_replace);
    scanf("%s", replace);
    char *new_buffer = process_buffer(buffer, replace, be_replace);

    output(out, new_buffer);

    free(buffer);
    free(new_buffer);

    return 0;
}
// read the file
char *input(char *filename) 
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) 
    {
        perror("fopen");
        return NULL;
    }
    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *buf = (char *)malloc(sizeof(char) * SIZE);
    if (buf == NULL) {
        perror("malloc");
        fclose(fp);
        return NULL;
    }
    // 读取文件内容
    size_t n = fread(buf, 1, size, fp);
    buf[n] = '\0';

    fclose(fp);
    return buf;
}

char *process_buffer(char *buffer, char *replacement, char *be_replaced)
{
    char *new_buffer = (char *) malloc(sizeof(char) * SIZE);
    char *p = buffer;char *q;
    int length = strlen(replacement);

    int index = 0;

    while ((q = search_str(p, be_replaced)) != NULL)
    {
        int sub = q - p;
        // move the string
        for (int m = 0; m < sub; m++)
            new_buffer[index++] = *(p + m);
        p = q + strlen(be_replaced);
        // add the replacement
        for (int i = 0; i < length; i++)
            new_buffer[index++] = replacement[i];
    }
    while (*p != '\0')
        new_buffer[index++] = *p++;
    new_buffer[index] = '\0';

    return new_buffer;
}

void output(char *filename, char *buffer) 
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) 
    {
        perror("fopen");
        return ;
    }

    int ret = fputs(buffer, fp);
    if (ret == EOF)
    {
        perror("fputs");
        fclose(fp);
        return ;
    }

    fclose(fp);
    return ;
}
// check the string and return the length
char *search_str(char *src, char *obj)
{
    int src_length = strlen(src); int obj_length = strlen(obj);
    char *new_src = (char *)malloc(sizeof(char) * src_length + 1);
    char *new_obj = (char *)malloc(sizeof(char) * obj_length + 1);
    int index = 0;

    while (src[index] != '\0')
    {
        new_src[index] = tolower(src[index]);  
        index++;
    }
    new_src[index] = '\0';  

    index = 0;
    while (obj[index] != '\0')
    {
        new_obj[index] = tolower(obj[index]);
        index++;
    }
    new_obj[index] = '\0';  

    char *result = strstr(new_src, new_obj);

    char *ret = NULL;
    if (result != NULL)
    {
        ret = src + (result - new_src);
    }

    free(new_src);
    free(new_obj);
    return ret;
}