// P5157.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, phead[MAX_N], current, mhead[MAX_N], deg[MAX_N];
bool vis[MAX_N], ans[MAX_N];

struct edge
{
    int to, nxt;
} edges[(MAX_N << 1) + MAX_N];

void addpath(int *head, int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void clearExit()
{
    for (int i = 1; i <= n; i++)
        puts("0");
    exit(0);
}

void dfs(int u, int fa)
{
    ans[u] = true;
    for (int i = phead[u]; i != -1; i = edges[i].nxt)
        if (!vis[edges[i].to] && edges[i].to != fa)
            dfs(edges[i].to, u);
}

int main()
{
    memset(phead, -1, sizeof(phead)), memset(mhead, -1, sizeof(mhead));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(phead, u, v), addpath(phead, v, u), deg[u]++, deg[v]++;
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(mhead, u, v), deg[v]++, vis[u] = true;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            q.push(i);
    int pt = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (deg[u] != 1)
        {
            if (deg[u] < 1)
            {
                pt = u;
                break;
            }
            clearExit();
        }
        for (int i = phead[u]; i != -1; i = edges[i].nxt)
        {
            deg[edges[i].to]--;
            if (deg[edges[i].to] == 1)
                q.push(edges[i].to);
        }
        for (int i = mhead[u]; i != -1; i = edges[i].nxt)
        {
            deg[edges[i].to]--;
            if (deg[edges[i].to] == 1)
                q.push(edges[i].to);
        }
    }
    if (pt == 0)
        clearExit();
    dfs(pt, 0);
    for (int i = 1; i <= n; i++)
        puts(ans[i] ? "1" : "0");
    return 0;
}