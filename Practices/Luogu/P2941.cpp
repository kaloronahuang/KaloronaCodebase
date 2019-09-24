// P2941.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550;

int dist[MAX_N][MAX_N], head[MAX_N], current, stk[MAX_N];
int componentId[MAX_N], ctot, dfn[MAX_N], low[MAX_N], ptot, tail, n;
bool instack[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, instack[u] = true, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (!componentId[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u] && ++ctot)
        do
        {
            componentId[stk[tail]] = ctot;
        } while (stk[tail--] != u);
}

int main()
{
    memset(head, -1, sizeof(head)), memset(dist, 0x3f, sizeof(dist));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        for (int j = 1, tmp; j <= n; j++)
        {
            scanf("%d", &tmp);
            dist[componentId[i]][componentId[j]] = min(dist[componentId[i]][componentId[j]], tmp);
        }
    long long ans = 0x3f3f3f3f3f3f3f3f;
    for (long long i = 1, tmp = 0; i <= ctot; i++)
    {
        for (int j = 1; j <= ctot; j++)
            if (i != j)
                tmp += dist[i][j];
        ans = min(ans, tmp), tmp = 0;
    }
    printf("%lld", ans << 1);
    return 0;
}