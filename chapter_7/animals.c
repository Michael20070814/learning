#include <stdio.h>
#include <ctype.h>
int main(void)
{
    char ch;

    printf("Give me a letter of the alphabet, and I will give you ");
    printf("an animal name that starts with that letter.\n");
    printf("Please type in a letter; type # to end my act.\n");
    while ((ch = getchar()) != '#')
    {
        if ('\n' == ch)
            continue;
        if (islower(ch))
        {
            switch (ch)
            {
            case 'a':
                printf("argali, a wild sheep of Asia\n");
                break;
            case 'b':
                printf("babirusa, a wild pig of Indonesia\n");
                break;
            case 'c':
                printf("capybara, the largest rodent\n");
                break;
            case 'd':
                printf("dik-dik, a small African antelope\n");
                break;
            case 'e':
                printf("echidna, an egg-laying mammal\n");
                break;
            default:
                printf("That's a stumper!\n");
            }
        }
        else
           printf("I recognize only lowercase letters. \n");
        while (getchar() != '\n')/* 丢弃一行中除了第一个以外的字符 */
            continue;
        printf("Please type in another letter or a # to end my act.\n");
    }
    printf("Bye!\n");
    return 0;
}