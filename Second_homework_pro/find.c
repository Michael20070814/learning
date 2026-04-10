#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000
#define LENGTH 30

char *search_str(char *src, char *obj);
char *extract_string(char *src, int *index, char *variable);
char *replace(char *src, char *replacement, char *BeReplace);

int main(void)
{
    char source[LENGTH];
    char object[LENGTH];

    scanf("%s", source); scanf("%s", object);

    int index = -1;
    char *variable = (char *) malloc (sizeof(char) * LENGTH);
    char *result = (char *) malloc(sizeof(char) * SIZE);
    size_t n = fread(result, 1, SIZE - 1, stdin);
    result[n] = '\0';
    char *NewSource = extract_string(source, &index, variable);
    if (index != -1)
    {
        for (int m = 0; variable[m] != '\0'; m++)
        {
            NewSource[index] = variable[m];
            result = replace(result, object, NewSource);
        }
    }
    else
        result = replace(result, object, NewSource);
    
    printf("%s", result);

    return 0;
}

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

char *extract_string(char *src, int *index, char *variable)
{
    char *result = (char *) malloc(sizeof(char) * LENGTH);
    int n = 0; int m = 0; int var = 0;
    int flag = 0;

    while (src[m] != '\0')
    {
        if (src[m] != '[' && src[m] != ']')
        {
            if (flag == 0)
                result[n++] = src[m];
            else if (flag == 1)
                variable[var++] = src[m];
        }

        if (src[m] == '[')
        {    
            flag = 1;
            *index = m;
            n++;
        }
        else if (src[m] == ']')
            flag = 0;

        m++;
    }

    result[n] = '\0';
    variable[var] = '\0';

    return result;
}

char *replace(char *src, char *replacement, char *BeReplace)
{
    char *new_src = (char *)malloc(sizeof(char) * SIZE);
    char *p = src;
    char *q;
    int index = 0;
    int len_replace = strlen(replacement);
    int len_be = strlen(BeReplace);

    while ((q = search_str(p, BeReplace)) != NULL)
    {
        int sub = q - p;

        // 先复制匹配位置之前的内容
        for (int i = 0; i < sub; i++)
            new_src[index++] = p[i];

        // 跳过被替换串
        p = q + len_be;

        // 加入替换串
        for (int i = 0; i < len_replace; i++)
            new_src[index++] = replacement[i];
    }

    // 把剩余内容复制过去
    while (*p != '\0')
        new_src[index++] = *p++;

    free(src);

    new_src[index] = '\0';
    return new_src;
}