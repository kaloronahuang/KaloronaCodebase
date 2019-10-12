// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 2e5 + 200;

int head[MAX_N], n, m, current, vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    int cnt = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis[edges[i].to])
            vis[edges[i].to] = vis[u] ^ 3, dfs(edges[i].to);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        cnt += (vis[edges[i].to] == vis[u]);
    if (cnt == 2)
        vis[u] ^= 3;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n; i++)
        if (vis[i] == 0)
            vis[i] = 1, dfs(i);
    for (int i = 1; i <= n; i++)
        printf("%d ", vis[i]);
    puts("");
    return 0;
}