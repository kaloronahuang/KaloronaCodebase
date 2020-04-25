// CF1305D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int n, head[MAX_N], current, deg[MAX_N];
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

int query(int x, int y)
{
    printf("? %d %d\n", x, y), fflush(stdout);
    return scanf("%d", &x), x;
}

void dfs(int u, int fa)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
}

int report(int u)
{
    printf("! %d\n", u), fflush(stdout);
    exit(0);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    while (true)
    {
        // find the leaf;
        int u = 0;
        for (int i = 1; i <= n && u == 0; i++)
            if (deg[i] == 1 && !vis[i])
                u = i;
        if (u == 0)
            for (int i = 1; i <= n; i++)
                if (!vis[i])
                    report(i);
        int v = 0;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (!vis[edges[i].to])
                v = edges[i].to;
        if (v == 0)
            report(u);
        int w = 0;
        for (int i = head[v]; i != -1; i = edges[i].nxt)
            if (!vis[edges[i].to] && edges[i].to != u)
                w = edges[i].to;
        if (w == 0)
        {
            // 2 pts rem;
            report(query(u, v) == u ? u : v);
        }
        int res = query(u, w);
        if (res == v)
            deg[v] -= 2, dfs(w, v), dfs(u, v);
        else if (res == u)
            report(u);
        else
            dfs(v, w), deg[w]--;
    }
    return 0;
}