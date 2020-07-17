#include<bits/stdc++.h>

void Solve(int N);

const int maxn=50000,MAX_CALLS=1000000;

class minerals_233666 {
private:
    int n,sum,num_calls,num_Answers;
    int belong[maxn*2],num[maxn],appears[maxn*2];
    bool in[maxn*2];
public:
    minerals_233666(){}
    void init(){
        scanf("%d",&n);
        for (int i=1;i<=n;i++){
            int x,y;
            scanf("%d %d",&x,&y);
            belong[x]=i;belong[y]=i;
        }
        return ;
    }
    void add(int x,int k){
        if(num[x]==0)sum++;
        num[x]+=k;
        if(num[x]==0)sum--;
    }
    int Query(int x){
        if(x<1 || x>2*n) return -1;
        if(++num_calls>MAX_CALLS) return -2;
        if(!in[x])in[x]=true,add(belong[x],1);
        else in[x]=false,add(belong[x],-1);
        return sum;
    }
    int Answer(int a,int b){
        if(a<1 || a>2*n || b<1 || b>2*n) return 3;
        if(++appears[a]>1 || ++appears[b]>1) return 4;
        if(belong[a]!=belong[b]) return 5;
        num_Answers++;
        return 0;
    }
    bool finish(){
        if (num_Answers!=n) return false;
        return true;
    }
    int getQuery(){
        return num_calls;
    }
    int getN(){
        return n;
    }
}a;

int Query(int x)
{
    int res=a.Query(x);
    if (res<0)
    {
        printf("%d\n",-res);fflush(stdout);
        exit(0);
    }
    return res;
}

void Answer(int x,int y)
{
    int res=a.Answer(x,y);
    if (!res) return ;
    printf("%d\n", res);fflush(stdout);
    exit(0);
}

int main(){
    
    a.init();
    Solve(a.getN());
    if (!a.finish()) puts("6");
    else printf("0 %d\n", a.getQuery());
    fflush(stdout);
    return 0;
}