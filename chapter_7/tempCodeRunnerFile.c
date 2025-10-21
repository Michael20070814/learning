main(void)
{
    char ch;

    while ((ch = getchar()) != '#')
    {
        if (!(ch == '\n'))
            printf("Step1\n");
        else if (ch == 'q')
            printf("Step2\n");
        else if (ch == 'c')
            ;
        else
            printf("Step3\n");
    }
    printf("Done\n");
    return 0;
}