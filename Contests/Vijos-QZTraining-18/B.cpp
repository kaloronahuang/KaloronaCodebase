// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100;

int head[MAX_N], current, n, m, dfn[MAX_N], low[MAX_N], stk[MAX_N], ptot, ans, hd;
bool inst[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, inst[u] = true;
    stk[++hd] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[edges[i].to], low[u]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        int siz = 0;
        do
        {
            inst[stk[hd]] = false, siz++;
        } while (stk[hd--] != u);
        ans = max(ans, siz);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i);
    printf("%d", ans);
    return 0;
}