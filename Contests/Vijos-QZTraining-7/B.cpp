// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200100, MAX_L = 23;

int head[MAX_N], current, n, q, dep[MAX_N], dfn[MAX_N], antidfn[MAX_N], ptot, edpt[MAX_N];

struct edge
{
    int from, to, nxt;
} edges[MAX_N << 1], org[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fat)
{
    dep[u] = dep[fat] + 1, dfn[u] = ++ptot, antidfn[dfn[u]] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs(edges[i].to, u);
    edpt[u] = ptot;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), org[i] = (edge){u, v, 0};
    dfs(1, 0), scanf("%d", &q);
    while (q--)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        int up, low;
        up = org[z].from, low = org[z].to;
        if (dep[up] > dep[low])
            swap(up, low);
        bool xInLow = (dfn[low] <= dfn[x] && dfn[x] <= edpt[low]);
        bool yInLow = (dfn[low] <= dfn[y] && dfn[y] <= edpt[low]);
        if (xInLow ^ yInLow)
            puts("NO");
        else
            puts("YES");
    }
    return 0;
}