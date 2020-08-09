// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, head[MAX_N], current, deg[MAX_N], A, B;
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

void dfs(int u, int fa)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (i != fa && edges[i].to != B)
            if (!vis[edges[i].to])
                dfs(edges[i].to, i ^ 1);
            else
                puts("Yes"), exit(0);
    vis[u] = false;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    int mdeg = 0;
    for (int i = 1; i <= n; i++)
        if (deg[i] & 1)
            puts("No"), exit(0);
        else
            mdeg = max(mdeg, deg[i]);
    if (mdeg == 4)
    {
        for (int i = 1; i <= n; i++)
            if (deg[i] == 4)
                if (A == 0)
                    A = i;
                else if (B == 0)
                    B = i;
                else
                    puts("Yes"), exit(0);
        if (B)
            dfs(A, 0);
        puts("No"), exit(0);
    }
    else if (mdeg > 4)
        puts("Yes"), exit(0);
    else
        puts("No"), exit(0);
    return 0;
}