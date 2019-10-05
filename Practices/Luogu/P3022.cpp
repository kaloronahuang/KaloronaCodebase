// P3022.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 50100, MAX_E = 101000;

int head[MAX_N], current, n, m, deg[MAX_N];
bool vis[MAX_N], tag[MAX_E];

struct edge
{
    int to, nxt, id;
} edges[MAX_E << 1];

void addpath(int src, int dst, int id)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].id = id, head[src] = current++;
}

bool dfs(int u)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis[edges[i].to] && dfs(edges[i].to))
            deg[u]++, tag[edges[i].id] = true;
    return (deg[u] % 2 == 0);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v, i), addpath(v, u, i);
    for (int i = 1; i <= n; i++)
        if (!vis[i] && dfs(i))
            puts("-1"), exit(0);
    int ans = 0;
    for (int i = 1; i <= m; i++)
        if (tag[i])
            ans++;
    printf("%d\n", ans);
    for (int i = 1; i <= m; i++)
        if (tag[i])
            printf("%d\n", i);
    return 0;
}