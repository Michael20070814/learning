#include <stdio.h>
#include <stdlib.h>
struct node {
        int n;
        struct node *link;
};

int main()
{
    int n;
    struct node *list=NULL, *tail, *q;
    
    scanf("%d",&n);
    while(n!=-1)
    {
        q = (struct node *)malloc(sizeof(struct node));
        q->n = n; 
        q->link = list;
        if(list==NULL) 
            list=q;
        else
            tail->link=q;
        tail=q;                
        scanf("%d",&n);
    }
    
    if (list == NULL)
        return 0;
    q = list;
    while (q -> link != NULL && q != q -> link)
    {
        printf("%d ", q -> n);
        // delete the node
        tail -> link = q -> link;
        free(q);
        q = tail -> link;
        q = q -> link;
        tail = tail -> link;

    }
    printf("%d ", q -> n);
    free(q);
    
    return 0;
} 
