#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
int num;
char a[25];
char b[15];
}Node;
Node list[150];
int total=0;
int search(char*x,char*y){
for(int i=0;i<total;i++){
if(strcmp(list[i].a,x)==0){
return i;
}
}
return -1;
}
int comp(const void*p,const void*q){
Node*u=(Node*)p;
Node*v=(Node*)q;
return strcmp(u->a,v->a);
}
char s1[25];
char s2[15];
int main(){
for(int k=0;k<150;k++){
list[k].num=0;
}
int t;
scanf("%d",&t);
for(int k=0;k<t;k++){
scanf("%s%s",s1,s2);
int pos=search(s1,s2);
int del=0;
if(pos!=-1){
if(strcmp(list[pos].b,s2)!=0){
int L=strlen(s1);
s1[L]='_';
s1[L+1]=++list[pos].num+'0';
s1[L+2]='\0';
}else{
del=1;
}
}
if(del==0){
strcpy(list[total].a,s1);
strcpy(list[total].b,s2);
total++;
}
}
qsort(list,total,sizeof(list[0]),comp);
for(int k=0;k<total;k++){
printf("%s %s\n",list[k].a,list[k].b);
}
return 0;
}