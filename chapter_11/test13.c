#include <stdio.h>
int main(int argc, char *argv [])//二维数组，第一个永远都是文件名或路径
{
    for (int num = argc - 1; num > 0; num--)
        printf("%s ", argv[num]);
    return 0;
}