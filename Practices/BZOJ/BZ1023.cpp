// BZ1023.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 51000, MAX_M = 1e5 + 200;

int n, m, head[MAX_N], current, ans = 1, dfn[MAX_N], up[MAX_N], low[MAX_N], ptot, dep[MAX_N];
int f[MAX_N], q[MAX_N << 1], q2[MAX_N << 1];

struct edge
{
    int to, nxt;
} edges[MAX_M << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void process(int u, int v)
{
    int top = 0;
    for (int i = v; i != u; i = up[i])
        q[++top] = i;
    q[++top] = u;
    reverse(q + 1, q + top + 1);
    for (int i = 1; i <= top; i++)
        q[i + top] = q[i];
    int head = 1, tail = 0;
    for (int i = 1; i <= (top << 1); i++)
    {
        while (head <= tail && i - q2[head] > (top >> 1))
            head++;
        if (head <= tail)
            ans = max(ans, f[q[i]] + f[q[q2[head]]] + i - q2[head]);
        while (head <= tail && f[q[i]] - i > f[q[q2[tail]]] - q2[tail])
            tail--;
        q2[++tail] = i;
    }
    for (int i = v; i != u; i = up[i])
        f[u] = max(f[u], f[i] + min(dep[i] - dep[u], 1 + dep[v] - dep[i]));
}

void dfs(int u, int fa)
{
    up[u] = fa, dfn[u] = low[u] = ++ptot, dep[u] = dep[fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (dfn[edges[i].to] == 0)
            dfs(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
        else if (edges[i].to != fa)
            low[u] = min(low[u], dfn[edges[i].to]);
        if (low[edges[i].to] > dfn[u])
            ans = max(ans, f[u] + f[edges[i].to] + 1), f[u] = max(f[u], f[edges[i].to] + 1);
    }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (up[edges[i].to] != u && dfn[edges[i].to] > dfn[u])
            process(u, edges[i].to);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, tot; i <= m; i++)
    {
        scanf("%d%d", &tot, &u);
        for (int j = 2; j <= tot; j++)
            scanf("%d", &v), addpath(u, v), addpath(v, u), swap(u, v);
    }
    dfs(1, 0), printf("%d\n", ans);
    return 0;
}