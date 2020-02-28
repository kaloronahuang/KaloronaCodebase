// CF1179D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

typedef long long ll;

int n, head[MAX_N], current, siz[MAX_N];
ll weight[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void preprocess(int u, int fa)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            preprocess(edges[i].to, u), siz[u] += siz[edges[i].to];
}

void collect(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            weight[edges[i].to] = weight[u] + 1LL * (siz[u] - siz[edges[i].to]) * siz[edges[i].to];
            collect(edges[i].to, u);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    preprocess(1, 0), weight[1] = (1LL * n * (n - 1)) >> 1, collect(1, 0);
    int pt = 2;
    for (int i = 3; i <= n; i++)
        if (weight[i] > weight[pt])
            pt = i;
    preprocess(pt, 0), weight[pt] = (1LL * n * (n - 1)) >> 1, collect(pt, 0);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        if (i != pt)
            ans = max(ans, weight[i]);
    printf("%lld\n", ans);
    return 0;
}