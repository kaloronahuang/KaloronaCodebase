// CF1280C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int T, n, head[MAX_N], current, siz[MAX_N], tmp[MAX_N];
ll dep[MAX_N], gans[2];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fa)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
}

void dfs_min(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs_min(edges[i].to, u); 
            if (siz[edges[i].to] & 1)
                gans[0] += edges[i].weight;
        }
}

void dfs_max(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs_max(edges[i].to, u);
            gans[1] += 1LL * min(siz[edges[i].to], n - siz[edges[i].to]) * edges[i].weight;
        }
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0, scanf("%d", &n), n <<= 1;
        for (int i = 1, a, b, t; i <= n - 1; i++)
            scanf("%d%d%d", &a, &b, &t), addpath(a, b, t), addpath(b, a, t);
        gans[0] = gans[1] = 0, dfs(1, 0), dfs_min(1, 0), dfs_max(1, 0);
        printf("%lld %lld\n", gans[0], gans[1]);
    }
    return 0;
}