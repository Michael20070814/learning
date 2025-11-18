#include <stdio.h>
#include <string.h>
int main(void)
{
    char comet_name[8], group_name[8];
    int comname, grname;
    comname = grname = 1;

    fgets(comet_name, 8, stdin);
    fgets(group_name, 8, stdin);//读入的是字符串，会有末尾的\0
    comet_name[strcspn(comet_name, "\n\r")] = '\0';
    group_name[strcspn(group_name, "\n\r")] = '\0';
    for (int num = 0; comet_name[num] != '\0'; num++)
    {
        comname *= comet_name[num] - 'A' + 1;
    }   
    for (int num = 0; group_name[num] != '\0'; num++)
    {
        grname *= group_name[num] - 'A' + 1;
    }
    if ((grname % 47) == (comname % 47))
        printf("GO");
    else
        printf("STAY");
        
    return 0;
}