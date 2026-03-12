#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 51
#define FILE_SIZE 10000

char *input(void);
char *gain_encrypt(char *arr);
char *read_file(char *filename);
void process_file(char *buffer, char *encrypt);
void output_file(char *filename, char *buffer);

int main(void)
{
    char in[] = "encrypt.txt";
    char out[] = "output.txt";
    char *secret = input();
    char *encrypt = gain_encrypt(secret);

    free(secret);

    char *buffer = read_file(in);
    process_file(buffer, encrypt);

    free(encrypt);

    output_file(out, buffer);

    free(buffer);

    return 0;
}

char *input(void)
{
    // 第一块内存：读入原始字符串
    char *buf = (char *)malloc(51 * sizeof(char));
    if (buf == NULL) 
        return NULL;

    if (scanf("%50s", buf) != 1) 
    {
        free(buf);
        return NULL;
    }

    // 第二块内存：存放去重后的结果
    char *result = (char *)malloc(51 * sizeof(char));
    if (result == NULL)
    {
        free(buf);
        return NULL;
    }

    int index = 0;

    for (int i = 0; buf[i] != '\0'; i++)
    {
        int found = 0;
        for (int j = 0; j < index; j++)
            if (result[j] == buf[i]) 
            {
                found = 1;
                break;
            }
        // 没出现过才写入
        if (!found) {
            result[index++] = buf[i];
        }
    }
    result[index] = '\0';

    free(buf);
    return result;
}

char *gain_encrypt(char *arr)
{
    // 分配27单位的内存
    char *result = (char *)malloc(27 * sizeof(char));
    if (result == NULL)
    {
        return NULL;
    }

    // 先把 arr 里的内容搬进去
    int index = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        result[index++] = arr[i];
    }

    // 按26字母表逆序（z -> a）
    for (char ch = 'z'; ch >= 'a'; ch--) 
    {
        int found = 0;
        for (int j = 0; j < index; j++)
            if (result[j] == ch)
            {
                found = 1;
                break;
            }
        if (!found) 
            result[index++] = ch;
    }
    result[index] = '\0';

    return result;
}

char *read_file(char *filename)
{
    // 打开文件
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return NULL;

    // 分配 FILE_SIZE 大小的内存
    char *buf = (char *)malloc(FILE_SIZE * sizeof(char));
    if (buf == NULL) 
    {
        fclose(fp);
        return NULL;
    }

    // 读取文件内容存入 buf
    int read_size = fread(buf, sizeof(char), FILE_SIZE - 1, fp);
    buf[read_size] = '\0';

    fclose(fp);
    return buf;
}

void process_file(char *buffer, char *encrypt)
{
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if (isalpha(buffer[i]))
            buffer[i] = encrypt[buffer[i] - 'a'];
    }
}

void output_file(char *filename, char *buffer)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        return;
    }

    fputs(buffer, fp);

    fclose(fp);
}