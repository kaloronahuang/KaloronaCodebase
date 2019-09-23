// P3478.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 1e6 + 200;

int head[MAX_N], current, n, dep[MAX_N], siz[MAX_N];
ll total[MAX_N], val, target, fa[MAX_N], util[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void predfs(int u, int fat)
{
    siz[u] = 1, dep[u] = dep[fat] + 1, total[u] = dep[u], fa[u] = fat;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            predfs(edges[i].to, u), siz[u] += siz[edges[i].to], total[u] += total[edges[i].to] + siz[edges[i].to];
}

void dfs_moving_root(int u, int fat)
{
    if (u != 1)
        util[u] = util[fa[u]] + total[fa[u]] - total[u] - 2LL * siz[u] + n;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs_moving_root(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    predfs(1, 0), dfs_moving_root(1, 0);
    for (int i = 1; i <= n; i++)
        if (val < total[i] + util[i])
            val = total[i] + util[i], target = i;
    printf("%d", target);
    return 0;
}