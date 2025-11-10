#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 41

int main(void)
{
    FILE *fp;
    char words[MAX];

    if ((fp = fopen("wordy", "a+")) == NULL)
    {
        fprintf(stdout, "Can't open \"wordy\" file. \n");
        exit(EXIT_FAILURE);
    }

    puts("Enter words to add to the file; press the #");
    puts("key at the beginning of a line to terminate.");
    while ((fscanf(stdin, "%40s", words) == 1) && (words[0] != '#'))//输入存入word，stdin为键盘输入
        fprintf(fp, "%s\n", words);//从words中读取写入fp
    /* 读取过程中指针发生变化，写入之后已经不在最初位置了 */
    puts("File contents: ");
    rewind(fp);//回到文件开头，重新读取
    while (fscanf(fp, "%s", words) == 1)
        puts(words);
    puts("Done!");
    if (fclose(fp) != 0)//正常关闭文件返回0
        fprintf(stderr, "Error closing file\n");
    
    return 0;
}