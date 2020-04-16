// CF1338B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, head[MAX_N], current, deg[MAX_N], root, dist[MAX_N], lcnt, parity[2];
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dist[edges[i].to] = dist[u] + 1, dfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            root = i, lcnt++;
    dfs(root, 0);
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            parity[dist[i] & 1]++;
    if (parity[0] == lcnt)
        printf("%d ", 1);
    else
        printf("%d ", 3);
    for (int u = 1; u <= n; u++)
        if (deg[u] == 1)
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if (deg[edges[i].to] != 1)
                    tag[edges[i].to] = true;
    int ans2 = n - 1 - lcnt;
    for (int i = 1; i <= n; i++)
        if (tag[i])
            ans2++;
    printf("%d\n", ans2);
    return 0;
}