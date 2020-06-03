// LOJ6073.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int typ, n, q, head[MAX_N], current, dep[MAX_N], upweight[MAX_N], roots[MAX_N];
int lft[MAX_N], ptot, anti[MAX_N], son[MAX_N], siz[MAX_N], pi[MAX_N], up[MAX_N], top[MAX_N];
ll dist[MAX_N], lans, prefix[MAX_N], fdist[MAX_N];

struct node
{
    int lson, rson;
    ll tag, sum;
} nodes[MAX_N * 250];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs1(int u, int fa)
{
    siz[u] = 1, up[u] = fa, dep[u] = dep[fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dist[edges[i].to] = dist[u] + edges[i].weight, upweight[edges[i].to] = edges[i].weight;
            dfs1(edges[i].to, u), siz[u] += siz[edges[i].to];
            son[u] = siz[edges[i].to] > siz[son[u]] ? edges[i].to : son[u];
        }
}

void dfs2(int u, int org)
{
    top[u] = org, lft[u] = ++ptot, anti[ptot] = u;
    if (son[u])
        dfs2(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != up[u] && edges[i].to != son[u])
            dfs2(edges[i].to, edges[i].to);
}

int getLCA(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = up[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return x;
}

#define mid ((l + r) >> 1)

int update(int ql, int qr, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre];
    if (ql <= l && r <= qr)
        return nodes[p].tag++, p;
    nodes[p].sum += (prefix[min(qr, r)] - prefix[max(ql, l) - 1]);
    if (ql <= mid)
        nodes[p].lson = update(ql, qr, l, mid, nodes[pre].lson);
    if (mid < qr)
        nodes[p].rson = update(ql, qr, mid + 1, r, nodes[pre].rson);
    return p;
}

ll query(int ql, int qr, int l, int r, int p)
{
    ll ret = 1LL * nodes[p].tag * (prefix[min(qr, r)] - prefix[max(ql, l) - 1]);
    if (ql <= l && r <= qr)
        return nodes[p].sum + ret;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

void dfs(int u, int fa)
{
    int p = pi[u];
    roots[u] = roots[fa];
    while (top[p])
        roots[u] = update(lft[top[p]], lft[p], 1, n, roots[u]), p = up[top[p]];
    fdist[u] = fdist[fa] + dist[pi[u]];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
}

ll query(int x, int y)
{
    ll ret = dist[y] * dep[x] + fdist[x];
    while (top[y])
        ret -= (query(lft[top[y]], lft[y], 1, n, roots[x]) << 1), y = up[top[y]];
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &typ, &n, &q);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs1(1, 0), dfs2(1, 1), ptot = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]);
    for (int i = 1; i <= n; i++)
        prefix[lft[i]] = upweight[i];
    for (int i = 1; i <= n; i++)
        prefix[i] += prefix[i - 1];
    dfs(1, 0);
    while (q--)
    {
        ll u, v, k;
        scanf("%lld%lld%lld", &u, &v, &k);
        u ^= (typ * lans), v ^= (typ * lans), k ^= (typ * lans);
        int d = getLCA(u, v);
        printf("%lld\n", lans = query(u, k) + query(v, k) - query(d, k) - query(up[d], k));
    }
    return 0;
}