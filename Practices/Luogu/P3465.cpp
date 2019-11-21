// P3465.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100;

int head[MAX_N], current, n, m, fa[MAX_N], ans[MAX_N];
bool vis[MAX_N], gflag;

struct edge
{
    int to, nxt;
} edges[MAX_N << 2];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void jump(int u, int provider)
{
    if (ans[u] != 0)
        jump(ans[u], u);
    ans[u] = provider;
}

void dfs(int u, int fat)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            if (vis[edges[i].to] && gflag == false)
                gflag = true, jump(edges[i].to, u);
            else if (vis[edges[i].to] == false)
                ans[edges[i].to] = u, dfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n; i++)
        if (vis[i] == false)
        {
            gflag = false, dfs(i, 0);
            if (gflag == false)
                puts("NIE"), exit(0);
        }
    puts("TAK");
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return 0;
}