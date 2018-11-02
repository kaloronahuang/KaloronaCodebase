#include <bits/stdc++.h>
using namespace std;
int a[300][1000];
int main(){
    a[1][0]=1,a[1][1]=1;  //a[i][0]表示第i位的长度
    a[2][0]=1,a[2][1]=3;
    for(int i=3;i<=250;i++){
        for(int j=1;j<=max(a[i-1][0],a[i-2][0]);j++)
            a[i][j]=a[i-1][j]+a[i-2][j]*2;
        a[i][0]=max(a[i-1][0],a[i-2][0]);
        for(int j=1;j<=a[i][0];j++)
        if(a[i][j]>=10){
            a[i][j+1]+=a[i][j]/10;
            a[i][j]%=10;
        }
        if(a[i][a[i][0]+1])a[i][0]++;
    }
    int n;
    while(scanf("%d",&n)!=EOF){
        if(n==0)printf("1\n");
        else{
            for(int i=a[n][0];i>=1;i--)
                printf("%d",a[n][i]);
            printf("\n");
        }
    }
    return 0;
}