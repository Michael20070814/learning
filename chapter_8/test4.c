#include <stdio.h>//计算单词的平均长度
#include <ctype.h>
int main(void)
{
    int ch;
    int letter_num, number;
    letter_num = number = 0;
    float average_letter;

    while ((ch = getchar()) != EOF)
    {   
        if (ch == ' ' || ch == '\n')
            number++;
        else if (ch != ' ' && !(ispunct(ch)))
            letter_num++;
    }
    average_letter = (float)letter_num / number;
    printf("The average letter number of the vocabulary is %.2f", average_letter);

    return 0;
}