// P2014.cpp
#include <iostream>
#include <queue>
using namespace std;

const int maxn = 320;
struct edge
{
    int to, next;
} edges[maxn << 1];
int deg[maxn];
int indeg[maxn];
int head[maxn];
int weight[maxn];
int current = 0;

int n, m;

void addpath(int src, int dst)
{
    edges[current].to = dst;
    edges[current].next = head[src];
    head[src] = current++;
}

int res[maxn];
int cur = 0;

int F[maxn][maxn];

void dfs(int u)
{
    F[u][0] = 0;
    for (int len = 1; len <= deg[u]; len++)
    {
        for (int i = head[u]; i != -1; i = edges[i].next)
        {
            int jto = edges[i].to;
            dfs(jto);
            for (int lens = 1; lens <= deg[jto] && lens <= len; lens++)
                F[u][len] = max(F[u][len], F[u][len - lens] + F[jto][lens]);
        }
    }
}

int HF[maxn];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int k, s;
        cin >> k >> s;
        weight[i] = s;
        if (k != 0)
            addpath(k, i), indeg[i]++, deg[k]++;
    }
    for (int len = 1; len <= m; len++)
    {
    }
    return 0;
}