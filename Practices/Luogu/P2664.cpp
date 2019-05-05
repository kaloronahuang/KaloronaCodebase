// P2664.cpp
#include <bits/stdc++.h>
#define ll long long
#define int ll
using namespace std;

const int MAX_N = 1e5 + 2000;

int head[MAX_N], current, n, color[MAX_N], tmpx, tmpy, siz[MAX_N], colorTot;
ll virtualSiz[MAX_N], rmVal[MAX_N], tag[MAX_N], ans[MAX_N], acc;
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
bool vis[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    siz[u] = 1;
    ll pre_vs = rmVal[color[fa]];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
    rmVal[color[u]]++;
    if (fa != 0)
    {
        virtualSiz[u] = siz[u] - (rmVal[color[fa]] - pre_vs);
        rmVal[color[fa]] += virtualSiz[u];
    }
}

void getAns(int u, int fa)
{
    ll prev_tag = tag[color[fa]];
    acc += virtualSiz[u] - tag[color[fa]];
    tag[color[fa]] = virtualSiz[u];
    ans[u] = n * colorTot - acc + tag[color[u]];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            getAns(edges[i].to, u);
    tag[color[fa]] = prev_tag;
    acc -= virtualSiz[u] - tag[color[fa]];
}

signed main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &color[i]);
        if (!vis[color[i]])
            vis[color[i]] = true, colorTot++;
    }
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs(1, 0);
    for (int i = 1; i < MAX_N; i++)
        if (vis[i])
            acc += n - rmVal[i], tag[i] = n - rmVal[i];
    getAns(1, 0);
    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);
    return 0;
}