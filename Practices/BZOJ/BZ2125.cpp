// BZ2125.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;
typedef pair<int, int> pii;

int n, m, head[MAX_N], current, dfn[MAX_N], low[MAX_N], dtot, ctot;
int up[20][MAX_N], fa[MAX_N], aff[MAX_N], dep[MAX_N], q;
ll dist[MAX_N], tot_len[MAX_N], pre[MAX_N];
vector<int> components[MAX_N];
vector<pii> G[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void connectEdge(int src, int dst, int weight)
{
    G[src].push_back(make_pair(dst, weight));
    G[dst].push_back(make_pair(src, weight));
}

void calc(int u, int cid)
{
    int v = edges[cid].to;
    ctot++, tot_len[ctot] = dist[v] - dist[u] + edges[cid].weight;
    while (v != fa[u])
    {
        int w = min(dist[v] - dist[u], tot_len[ctot] - (dist[v] - dist[u]));
        aff[v] = ctot, connectEdge(ctot, v, w), v = fa[v];
    }
}

void tarjan(int u, int fat)
{
    dfn[u] = low[u] = ++dtot, fa[u] = fat;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
        {
            if (!dfn[edges[i].to])
            {
                dist[edges[i].to] = dist[u] + edges[i].weight;
                tarjan(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
            }
            else
                low[u] = min(low[u], dfn[edges[i].to]);
            if (low[edges[i].to] > dfn[u])
                connectEdge(u, edges[i].to, edges[i].weight);
        }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat && fa[edges[i].to] != u && dfn[edges[i].to] > dfn[u])
            calc(u, i);
}

void collect(int u, int fa)
{
    up[0][u] = fa, dep[u] = dep[fa] + 1;
    for (pii x : G[u])
    {
        int v = x.first, w = x.second;
        if (v != fa)
            pre[v] = pre[u] + w, collect(v, u);
    }
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[up[i][x]] >= dep[y])
            x = up[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (up[i][x] != up[i][y])
            x = up[i][x], y = up[i][y];
    return up[0][x];
}

int jump(int u, int stop)
{
    for (int i = 19; i >= 0; i--)
        if (dep[up[i][u]] > dep[stop])
            u = up[i][u];
    return u;
}

ll getDistOnLoop(int x, int y)
{
    ll ret = abs(dist[x] - dist[y]);
    return min(ret, tot_len[aff[x]] - ret);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    ctot = n, tarjan(1, 0), collect(1, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= ctot; j++)
            up[i][j] = up[i - 1][up[i - 1][j]];
    while (q--)
    {
        int u, v, lca, u_, v_;
        scanf("%d%d", &u, &v), lca = getLCA(u, v);
        if (lca <= n)
            printf("%lld\n", pre[u] + pre[v] - 2LL * pre[lca]);
        else
        {
            u_ = jump(u, lca), v_ = jump(v, lca);
            printf("%lld\n", pre[u] - pre[u_] + pre[v] - pre[v_] + getDistOnLoop(u_, v_));
        }
    }
    return 0;
}