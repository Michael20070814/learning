#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int cal_space(char input[]);
int cal_alpha(char input[]);
int cal_sentence(char input[]);
int cal_grade(int space, int alpha, int sentence);
int main(void)
{
    char *input = malloc(1000 * sizeof(char));
    printf("Text: ");
    fgets(input, 1000, stdin);
    int space = cal_space(input);
    int alpha_num = cal_alpha(input);
    int sentence_num = cal_sentence(input);
    int grade_index = cal_grade(space, alpha_num, sentence_num);
    if (grade_index >= 1 && grade_index <= 15)
        printf("Grade %d", grade_index);
    else if (grade_index < 1)
        printf("Before Grade 1");
    else
        printf("Grade 16+");

    return 0;
}
int cal_space(char input[])
{
    char *p = input;
    int space = 0;
    while (*p != '\0')
    {
        if (*p == ' ')
            space++;
        p++;
    }
    space++;
    return space;
}
int cal_alpha(char input[])
{
    char *p = input;
    int alpha_num = 0;
    while (*p != '\0')
    {
        if (isalpha(*p))
            alpha_num++;
        p++;
    }
    return alpha_num;
}
int cal_sentence(char input[])
{
    char *p = input;
    int sentence_num = 0;
    while (*p != '\0')
    {
        if (*p == '.' || *p == '?')
            sentence_num++;
        p++;
    }
    return sentence_num;
}
int cal_grade(int space, int alpha, int sentence)
{
    float L = alpha * 100 / space;
    float s = sentence * 100 / alpha;
    int index = (int) 0.0588 * L - 0.296 * s - 15.8;
    return index;
}
