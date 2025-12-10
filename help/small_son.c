#include<stdio.h>
#define n 4
char countries[n][20];
int score[n][2];
int cmp(int A[],int a,int b){
    if(score[a][0]>score[b][0])return 1;
    if(score[a][0]<score[b][0])return 0;
    if(score[a][1]>score[b][1])return 1;
}
void sort(int A[]){
    for(int i=0;i<=n-2;i++){
        int maxp=0;
        for(int j=1;j<=n-i-1;j++){
            if(!cmp(A,A[j],A[maxp])){
                maxp=j;
            }
        }
        if(maxp!=n-i-1){
            int temp=A[maxp];
            A[maxp]=A[n-i-1];
            A[n-i-1]=temp;
        }
    }
}
int main(){
    for(int i=0;i<n;i++){
        scanf("%s",&countries[i]);
    }
    int win,draw,lose,goal;
    for(int i=0;i<n;i++){
        scanf("%d %d %d %d",&win,&draw,&lose,&goal);
        score[i][0]=win*3+draw*1;
        score[i][1]=goal;
    }
    int teamIndex[n];
    for(int i=0;i<n;i++){
        teamIndex[i]=i;
    }
    sort(teamIndex);
    printf("该小组直接出线的是%s和%s\n",countries[teamIndex[0]],countries[teamIndex[1]]);
    return 0;
}