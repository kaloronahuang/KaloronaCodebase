// P2014.cpp
#include <iostream>
#include <queue>
using namespace std;

const int maxn = 2100;
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

int F[maxn][maxn];
int sizes[maxn];

void dfss(int u)
{
    sizes[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next)
    {
        dfss(edges[i].to);
        sizes[u] += sizes[edges[i].to];
    }
}

void dfs(int u)
{
    for (int i = 1; i <= m; i++)
        F[u][i] = weight[u];
    for (int i = head[u]; i != -1; i = edges[i].next)
    {
        dfs(edges[i].to);
        int jto = edges[i].to;
        for (int len = m + 1; len >= 2; len--)
            for (int lens = 0; lens < len; lens++)
                F[u][len] = max(F[u][len], F[u][len - lens] + F[jto][lens]);
    }
}

int main()
{
    fill(head, head + maxn, -1);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int k, s;
        cin >> k >> s;
        weight[i] = s;
        addpath(k, i), indeg[i]++, deg[k]++;
    }
    dfss(0);
    dfs(0);
    cout << F[0][m + 1];
    return 0;
}