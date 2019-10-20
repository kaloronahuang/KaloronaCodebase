// P3066.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define ll long long

using namespace std;

const int MAX_N = 4e5 + 200;

int head[MAX_N], current, n, roots[MAX_N], ptot, dfn[MAX_N], low[MAX_N], ncnt;
int anti[MAX_N], upper;
ll dist[MAX_N], limit;
vector<ll> mp;

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

struct node
{
    int sum, lson, rson;
} nodes[MAX_N * 20];

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].sum++;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    return p;
}

int query(int ql, int qr, int l, int r, int lft, int rig)
{
    if (ql <= l && r <= qr)
        return nodes[rig].sum - nodes[lft].sum;
    int ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[lft].lson, nodes[rig].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[lft].rson, nodes[rig].rson);
    return ret;
}

void dfs(int u, int fa)
{
    dfn[u] = low[u] = ++ncnt, anti[ncnt] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dist[edges[i].to] = dist[u] + edges[i].weight, dfs(edges[i].to, u);
    low[u] = ncnt;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%lld", &n, &limit);
    for (ll i = 2, v, w; i <= n; i++)
        scanf("%lld%lld", &v, &w), addpath(i, v, w), addpath(v, i, w);
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        mp.push_back(dist[i]), mp.push_back(dist[i] + limit);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    upper = mp.size();
    for (int i = 1; i <= n; i++)
        roots[i] = update(lower_bound(mp.begin(), mp.end(), dist[anti[i]]) - mp.begin() + 1, 1, upper, roots[i - 1]);
    for (int i = 1; i <= n; i++)
    {
        int up = lower_bound(mp.begin(), mp.end(), dist[i] + limit) - mp.begin() + 1;
        int lw = lower_bound(mp.begin(), mp.end(), dist[i]) - mp.begin() + 1;
        printf("%d\n", query(lw, up, 1, upper, roots[dfn[i] - 1], roots[low[i]]));
    }
    return 0;
}