// LOJ3163.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, q, head[MAX_N], current, seq[MAX_N], stot, lft[MAX_N], rig[MAX_N];
ll upper, dep[MAX_N];

struct rawEdge
{
    int u, v;
    ll w;
} org[MAX_N];

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_N << 1];

struct node
{
    ll sum, min_val, max_val, lft, rig, tag;
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    nodes[p].min_val = min(nodes[lson].min_val, nodes[rson].min_val), nodes[p].max_val = max(nodes[lson].max_val, nodes[rson].max_val);
    nodes[p].lft = max({nodes[lson].lft, nodes[rson].lft, nodes[lson].max_val - (nodes[rson].min_val << 1)});
    nodes[p].rig = max({nodes[lson].rig, nodes[rson].rig, nodes[rson].max_val - (nodes[lson].min_val << 1)});
    nodes[p].sum = max({nodes[lson].sum, nodes[rson].sum, nodes[lson].lft + nodes[rson].max_val, nodes[lson].max_val + nodes[rson].rig});
}

void pushdown(int p)
{
    if (nodes[p].tag)
    {
        nodes[lson].tag += nodes[p].tag, nodes[rson].tag += nodes[p].tag;

        nodes[lson].max_val += nodes[p].tag, nodes[lson].min_val += nodes[p].tag;
        nodes[lson].lft -= nodes[p].tag, nodes[lson].rig -= nodes[p].tag;

        nodes[rson].max_val += nodes[p].tag, nodes[rson].min_val += nodes[p].tag;
        nodes[rson].lft -= nodes[p].tag, nodes[rson].rig -= nodes[p].tag;

        nodes[p].tag = 0;
    }
}

void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p].sum = 0;
        nodes[p].max_val = nodes[p].min_val = dep[seq[l]];
        nodes[p].lft = nodes[p].rig = -dep[seq[l]];
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int ql, int qr, int l, int r, int p, ll val)
{
    if (ql <= l && r <= qr)
    {
        nodes[p].max_val += val, nodes[p].min_val += val;
        nodes[p].lft -= val, nodes[p].rig -= val;
        nodes[p].tag += val;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fa)
{
    seq[++stot] = u, lft[u] = stot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dep[edges[i].to] = dep[u] + edges[i].weight, dfs(edges[i].to, u), seq[++stot] = u;
    rig[u] = stot;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%lld", &n, &q, &upper);
    for (ll i = 1, u, v, w; i <= n - 1; i++)
        scanf("%lld%lld%lld", &u, &v, &w), addpath(u, v, w), addpath(v, u, w), org[i].u = u, org[i].v = v, org[i].w = w;
    dfs(1, 0), build(1, stot, 1);
    for (int i = 1; i <= n - 1; i++)
        if (dep[org[i].u] > dep[org[i].v])
            swap(org[i].u, org[i].v);
    ll last_ans = 0;
    while (q--)
    {
        ll d, e;
        scanf("%lld%lld", &d, &e);
        d = (d + last_ans) % (n - 1) + 1, e = (e + last_ans) % upper;
        update(lft[org[d].v], rig[org[d].v], 1, stot, 1, e - org[d].w), org[d].w = e;
        printf("%lld\n", last_ans = nodes[1].sum);
    }
    return 0;
}