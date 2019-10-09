// P2661.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int head[MAX_N], current, deg[MAX_N], n, fa[MAX_N], dep[MAX_N], ans = 0x3f3f3f3f;
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int dist, int from)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (vis[edges[i].to] && from == edges[i].to)
        {
            ans = min(ans, dist + 1);
            return;
        }
        else if (!vis[edges[i].to])
            dfs(edges[i].to, dist + 1, from);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &fa[i]), deg[fa[i]]++, addpath(i, fa[i]);
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (--deg[edges[i].to] == 0)
                q.push(edges[i].to);
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] != 0 && vis[i] == false)
            dfs(i, 0, i);
    printf("%d", ans);
    return 0;
}