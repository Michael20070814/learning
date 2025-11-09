#include <stdio.h>
#include <ctype.h>
#define LEN 40
char * s_gets(char * st, int n);
int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1][0] != '-')
        return 1;
    char ch[LEN];
    printf("Please enter what you want: ");
    while (s_gets(ch, LEN) != NULL)
        continue;
    switch (argv[1][1])
    {
        case 'p':
        puts(ch);
        break;
        case 'u':
        for (int num = 0; ch[num] != '\0'; num++)
        {
            if ((islower(ch[num])))
                ch[num] = ch[num] - 32;
        }
        puts(ch);
        break;
        case 'l':
        for (int num = 0; ch[num] != '\0'; num++)
        {
            if (isupper(ch[num]))
                ch[num] = ch[num] + 32;
        }
        puts(ch);
        break;
    }
    printf("Done!");

    return 0;
}
char * s_gets(char * st, int n)
{
    char * ret_val;
    int i = 0;

    ret_val = fgets(st, n, stdin);
    if (ret_val) //ret_val != NULL
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}