#include <stdio.h>
#include <stdlib.h>


typedef struct Node{
    int idx;            // monkey id
    struct Node *next;  // next monkey in the circle
    
}node;
int main(void){
int n,m,q;
// n: total number of monkeys
// m: remove the m-th monkey while counting
// q: counting starts from the q-th monkey
scanf("%d %d %d",&n,&m,&q);

node *head,*p;
// Create node 1 first as the head of the circular list.
head=malloc(sizeof(node));
head->idx=1;
head->next=NULL;
p=head;
// Create nodes 2 to n.
for (int i=2;i<=n;i++){
    p->next=malloc(sizeof(node));
    p=p->next;
    p->idx=i;
    p->next=NULL;
}
// Link tail back to head to form a circular linked list.
p->next=head;
p=head;
// Move p to the q-th monkey as the starting position.
for (int i=1;i<q;i++)
 p=p->next;
// pre always points to the node before p for deletion.
node *pre=p;
while (pre->next !=p){
    pre=pre->next;
}
int remain=n;
// Keep removing monkeys until only one remains.
while(remain>1){
  // Count forward to the m-th monkey.
  for (int i=1;i<m;i++)
 {   pre=p;
    p=p->next;
 }
 // Remove the current m-th monkey.
 pre->next=p->next;
 free(p);
 // Continue counting from the next monkey.
 p=pre->next;
 remain--;
}
// Output the id of the last monkey.
printf("%d\n",p->idx);
return 0;
}

