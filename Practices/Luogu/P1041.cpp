// P1041.cpp
#include < iostream >
#include < algorithm >

using namespace std;
const int maxn = 320;
const int INF = 0x7fffffff;
struct edge
{
    int to, next;
} edges[maxn << 2];
int head[maxn];
int n, p;
int current = 0;

void add_path(int a, int b)
{
    edges[current].to = b;
    edges[current].next = head[a];
    head[a] = current++;
}

int F[maxn][2];

void dfs(int u)
{
    F[u][0] = 1;
    F[u][1] = 1;
    int acc = 0;
    for (int i = head[u]; i != -1; i = edges[i].next)
    {
        dfs(edges[i].to);
        F[u][0] + = F[edges[i].to][0];
        F[u][1] + = F[edges[i].to][1];
        acc = max(F[edges[i].to][1], acc);
    }
    F[u][1] - = acc;
}

int main()
{
    cin >> n >> p;
    fill(head, head + maxn, -1);
    for (int i = 0; i < p; i++)
    {
        int a, b;
        cin >> a >> b;
        add_path(a, b);
    }
    dfs(1);
    cout << F[1][1];
    Regularreturn 0;
}