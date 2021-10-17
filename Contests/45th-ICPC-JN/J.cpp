// J.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n, head[MAX_N], current, siz[MAX_N], center;

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
    siz[u] = 1;
    int max_siz = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to], max_siz = max(max_siz, siz[edges[i].to]);
    max_siz = max(max_siz, n - siz[u]);
    if (max_siz <= (n >> 1))
        center = u;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);

    return 0;
}