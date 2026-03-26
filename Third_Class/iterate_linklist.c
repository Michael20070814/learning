#include <stdio.h>
#include <stdlib.h>
struct node {
        int n;
        struct node *link;
};

void print(int input);
void reverse(char *arr, int length);

int main()
{
    int n;
    struct node *list=NULL, *tail, *q;
    
    scanf("%d",&n);

    while(n!=-1){
        q = (struct node *)malloc(sizeof(struct node));
        q->n = n; 
        q->link = NULL;
        
        if(list == NULL)
            list = q;
        else 
            tail->link = q;
        tail=q;
        
        scanf("%d",&n);
    }
    q = list;
    while (q != NULL)
    {
        char result[50];
        int n = 0; int flag = 0;
        int input = q -> n;

        while (input > 0)
        {
            int temp;
            temp = input % 10;
            if (flag == 0 || flag % 3 != 0)
                result[n++] = temp + '0';
            else
            {
                result[n++] = ',';
                result[n++] = temp + '0';
            }

            input = input / 10;
            flag++;
        }   
        result[n] = '\0';

        int m = 0;
        int right = n - 1;

        while (m < right)
        {
            char temp = result[m];
            result[m] = result[right];
            result[right] = temp;
            m++;
            right--;
        }
        printf("%s ", result);
        q = q -> link;
    }

    return 0;
    
}
void print(int input)
{
    char result[50];
    int n = 0; int flag = 0;

    while (input > 0)
    {
        int temp;
        temp = input % 10;
        if (flag == 0 || flag % 3 != 0)
            result[n++] = temp + '0';
        else
        {
            result[n++] = ',';
            result[n++] = temp + '0';
        }

        input = input / 10;
        flag++;
    }
    result[n] = '\0';

    reverse(result, n);
    printf("%s", result);

}

void reverse(char *arr, int length)
{
    int m = 0;
    int n = length - 1;

    while (m < n)
    {
        char temp = arr[m];
        arr[m] = arr[n];
        arr[n] = temp;
        m++;
        n--;
    }
}