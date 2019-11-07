// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030;

int head[MAX_N], current, n, p, q, dep[MAX_N], dfn_seq[MAX_N], rig, lca, stot;
long long ans, bucket_p[MAX_N], bucket_q[MAX_N], ptot, qtot;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].nxt = head[src], edges[current].to = dst;
    head[src] = current++;
}

void dfs_sub(int u, int fa)
{
    dfn_seq[++stot] = u;
    for (int sub = 1; sub <= rig; sub++)
    {
        int pt = dfn_seq[sub];
        if (dep[pt] + dep[u] - (dep[lca] << 1) == p)
        {
            bucket_p[lca]++, ptot++, ans -= bucket_q[u];
            if (sub != 1)
                ans -= bucket_q[pt];
        }
        if (dep[pt] + dep[u] - (dep[lca] << 1) == q)
        {
            bucket_q[lca]++, qtot++, ans -= bucket_p[u];
            if (sub != 1)
                ans -= bucket_p[pt];
        }
    }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs_sub(edges[i].to, u);
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dep[edges[i].to] = dep[u] + 1, dfs(edges[i].to, u);
    rig = stot = 1;
    dfn_seq[1] = lca = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            rig = stot, dfs_sub(edges[i].to, u);
    // delete the invaild first;
    ans -= bucket_p[u] * bucket_q[u];
    for (int i = 2; i <= stot; i++)
        bucket_p[dfn_seq[i]] += bucket_p[u], bucket_q[dfn_seq[i]] += bucket_q[u];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &p, &q);
    for (int i = 1, u, v; i < n; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), ans += qtot * ptot;
    // printf("%lld %lld\n", ptot, qtot);
    printf("%lld", ans << 2);
    return 0;
}