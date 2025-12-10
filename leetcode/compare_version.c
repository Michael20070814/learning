int compareVersion(char* version1, char* version2) 
{
    int num1, num2;
    int value1, value2, value, i;
    value1 = value2 = i = 0;
    char *p = version1;
    char *q = version2;

    for (int num = 0; version1[num] != '\0'; num++)
        if (version1[num] == '.')
            value1 += 1;
    for (int num = 0; version2[num] != '\0'; num++)
        if (version2[num] == '.')
            value2 += 1;
    value = (value1 < value2)? value2 : value1;
    
    while (i < value)
    {   
        while (*p != '.')
            continue;
        p++;
        while (*q != '.')
            continue;
        q++;
        if (i > value1)
            num1 = 0;
        else
            num1 = atoi(q);
        if (i > value2)
            num2 = 0;
        else
            num2 = atoi(q);
        if (num1 > num2)
            return 1;
        else if (num1 < num2)
            return -1;
        i++;
    }
}