#include <stdio.h>
#include <stdlib.h>
#define LENGTH 50
char *AnalyzeNum(char *input, int *power);
void PrintNum(char *num, int power);

int main(void)
{
    char buffer[100];
    char *num;
    int power;

    scanf("%s", buffer);
    num = AnalyzeNum(buffer, &power);
    PrintNum(num, power);

    free(num);

    return 0;
}

char *AnalyzeNum(char *input, int *power)
{
    int index = 0;
    int m = 0;

    char *result = (char *) malloc(sizeof(char) * LENGTH);

    while (input[index] != 'e' && input[index] != 'E')
    {
        if (input[index] != '.')
            result[m++] = input[index];
        index++;
    }

    index++;
    result[m] = '\0';

    *power = atoi(&input[index]);

    return result;
}

void PrintNum(char *num, int power)
{
    if (power >= 0)
    {
        int m;
        for (m = 0; num[m] != '\0'; m++)
        {
            printf("%c", num[m]);
            if (m == power && num[m + 1] != '\0')
                printf(".");
        }
        if (power >= m)
            for (; m <= power; m++)
                printf("0");
    }
    else if (power < 0)
    {
        printf("0.");

        for (int n = -1; n > power; n--)
            printf("0");
        
        for (int n = 0; num[n] != '\0'; n++)
            printf("%c", num[n]);
    }
}