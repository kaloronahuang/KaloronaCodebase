// LOJ3166.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;
typedef pair<ll, ll> pii;

int n, m, k, fa[MAX_N], roots[MAX_N], ptot, head[MAX_N], current, frames[MAX_N];
ll yields[MAX_N];

inline char nc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    ll sum;
    int lson, rson;
} nodes[MAX_N * 50];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    nodes[x].sum += nodes[y].sum;
    nodes[x].lson = merge(nodes[x].lson, nodes[y].lson);
    nodes[x].rson = merge(nodes[x].rson, nodes[y].rson);
    return x;
}

int update(int qx, int l, int r, int p, int val)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].sum += val;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    return p;
}

pii query(int qx, int l, int r, int p)
{
    if (nodes[p].sum == 0)
        return make_pair(0, 0);
    if (l == r)
        return make_pair(l, nodes[p].sum);
    int mid = (l + r) >> 1;
    if (qx <= mid)
    {
        pii res = query(qx, l, mid, nodes[p].lson);
        if (res.first)
            return res;
    }
    return query(qx, mid + 1, r, nodes[p].rson);
}

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), roots[u] = merge(roots[u], roots[edges[i].to]);
    while (frames[u] < k && yields[u])
    {
        pii res = query(frames[u] + 1, 1, k, roots[u]);
        if (res.first == 0)
            break;
        ll tmp = min(yields[u], res.second);
        yields[u] -= tmp;
        roots[u] = update(res.first, 1, k, roots[u], -tmp);
    }
}

int main()
{
    freopen("4.000.in", "r", stdin);
    freopen("test.out", "w", stdout);
    memset(head, -1, sizeof(head));
    n = read(), m = read(), k = read();
    for (int i = 2; i <= n; i++)
        fa[i] = read(), addpath(fa[i], i);
    for (int i = 1, x, frame, yield; i <= m; i++)
        x = read(), frame = frames[x] = read(), yield = yields[x] = read(),
        roots[x] = update(frame, 1, k, roots[x], yield);
    dfs(1), printf("%lld\n", nodes[roots[1]].sum);
    return 0;
}