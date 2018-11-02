// P3379.cpp
// tags:LCA
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdio>

using namespace std;

struct ios{
    inline char read(){
        static const int IN_LEN=1<<18|1;
        static char buf[IN_LEN],*s,*t;
        return (s==t)&&(t=(s=buf)+fread(buf,1,IN_LEN,stdin)),s==t?-1:*s++;
    }
    template <typename _Tp> inline ios & operator >> (_Tp&x){
        static char c11,boo;
        for(c11=read(),boo=0;!isdigit(c11);c11=read()){
            if(c11==-1)return *this;
            boo|=c11=='-';
        }
        for(x=0;isdigit(c11);c11=read())x=x*10+(c11^'0');
        boo&&(x=-x);
        return *this;
    }
}io;

const int maxn = 1000010;
int DFS_seq[maxn];
int depth[maxn];
int N, M, S;
const int INF = 2100000000;
int pos[maxn];
int log_arr[maxn];

void init()
{
    log_arr[1] = 0;
    for (int i = 2; i < maxn; i++)
        log_arr[i] = log_arr[(int)(i / 2)] + 1;
}

vector<int> map[maxn];

int cursor = 0;

void DFS(int next, int father, int dep)
{
    depth[next] = dep;
    pos[next] = cursor;
    DFS_seq[cursor++] = next;
    int limit = map[next].size();
    for (int i = 0; i < limit; i++)
        if (map[next][i] != father)
            DFS(map[next][i], next, dep + 1), DFS_seq[cursor++] = next;
}

void build_map()
{
    io >> N >> M >> S;
    for (int i = 0; i < N - 1; i++)
    {
        int src, target;
        io >> src >> target;
        map[src].push_back(target);
        map[target].push_back(src);
    }
    DFS(S, -1, 1);
    init();
}

int lca[32][maxn];


void getLCA()
{
    for (int i = 0; i < cursor; i++)
        lca[0][i] = DFS_seq[i];
    for (int i = 1; (1 << i) <= cursor; i++)
        for (int l = 0; l + (1 << i) - 1 < cursor; l++)
            if (depth[lca[i - 1][l]] < depth[lca[i - 1][l + (1 << (i - 1))]])
                lca[i][l] = lca[i - 1][l];
            else
                lca[i][l] = lca[i - 1][l + (1 << (i - 1))];
}

void inquire(int a, int b)
{
    int l = pos[a], r = pos[b];
    if (pos[a] > pos[b])
        swap(l, r);
    int key = log_arr[r - l + 1];
    int num = lca[key][l];
    if (depth[lca[key][l]] > depth[lca[key][r - (1 << key) + 1]])
        num = lca[key][r - (1 << key) + 1];
    printf("%d\n",num);
}

int main()
{
    build_map();
    getLCA();
    for (int i = 0; i < M; i++)
    {
        int a, b;
        io >> a >> b;
        if (a == S || b == S)
            printf("%d\n", S);
        else
            inquire(a, b);
    }
    return 0;
}