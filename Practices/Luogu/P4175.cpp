// P4175.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8e4 + 200;
typedef pair<int, int> pii;

int head[MAX_N], n, q, current, dep[MAX_N], lft[MAX_N], rig[MAX_N], ptot, segtot, q_k[MAX_N];
int roots[MAX_N], top[MAX_N], anti[MAX_N], siz[MAX_N], son[MAX_N], fa[MAX_N], org_ai[MAX_N];
int q_a[MAX_N], q_b[MAX_N];
deque<pii> queryLine;
vector<int> mp;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    int lson, rson, val;
} nodes[MAX_N * 200];

inline char gc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read()
{
    int x = 0, f = 1;
    char ch = gc();
    if (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = gc();
    return x * f;
}

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int update(int qx, int l, int r, int p, int val)
{
    if (p == 0)
        p = ++segtot;
    nodes[p].val += val;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    return p;
}

int query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].val;
    int ret = 0, mid = (l + r) >> 1;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

inline int lowbit(int x) { return x & (-x); }

void update(int x, int pos, int d)
{
    for (; x <= n; x += lowbit(x))
        roots[x] = update(pos, 1, mp.size(), roots[x], d);
}

int query(int x, int ql, int qr, int ret = 0)
{
    for (; x >= 1; x -= lowbit(x))
        ret += query(ql, qr, 1, mp.size(), roots[x]);
    return ret;
}

// Splitting functions;

void pre_dfs(int u)
{
    dep[u] = dep[fa[u]] + 1, siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            fa[edges[i].to] = u, pre_dfs(edges[i].to), siz[u] += siz[edges[i].to];
            son[u] = (siz[son[u]] < siz[edges[i].to]) ? edges[i].to : son[u];
        }
}

void dfs(int u, int org)
{
    lft[u] = ++ptot, anti[ptot] = u, top[u] = org;
    if (son[u] != 0)
        dfs(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != son[u] && edges[i].to != fa[u])
            dfs(edges[i].to, edges[i].to);
    rig[u] = ptot;
}

// extracting functions;

void extract(int x, int y)
{
    queryLine.clear();
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        queryLine.push_back(make_pair(lft[top[x]], lft[x]));
        // printf("Extract Event: l = %d, r = %d.\n", lft[top[x]], lft[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    queryLine.push_back(make_pair(lft[x], lft[y]));
    // printf("Extract Event: l = %d, r = %d.\n", lft[x], lft[y]);
}

int getLCA(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] > dep[y] ? y : x;
}

int querySegments(int k, int l, int r)
{
    if (l == r)
        return l;
    int rval = 0, mid = (l + r) >> 1;
    for (deque<pii>::iterator it = queryLine.begin(); it != queryLine.end(); it++)
        rval += query(it->second, mid + 1, r) - query(it->first - 1, mid + 1, r);
    if (k <= rval)
        return querySegments(k, mid + 1, r);
    else
        return querySegments(k - rval, l, mid);
}

int queryKth(int x, int y, int k)
{
    int lca = getLCA(x, y), siz = dep[x] + dep[y] - dep[lca] - dep[fa[lca]];
    if (siz < k)
        return -1;
    extract(x, y);
    return querySegments(k, 1, mp.size());
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read(), q = read();
    for (int i = 1; i <= n; i++)
        org_ai[i] = read(), mp.push_back(org_ai[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        u = read(), v = read(), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= q; i++)
    {
        q_k[i] = read(), q_a[i] = read(), q_b[i] = read();
        if (q_k[i] == 0)
            mp.push_back(q_b[i]);
    }
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    pre_dfs(1), dfs(1, 1);
    for (int i = 1; i <= n; i++)
        update(lft[i], ripe(org_ai[i]), 1);
    for (int idx = 1; idx <= q; idx++)
    {
        int k = q_k[idx], a = q_a[idx], b = q_b[idx];
        if (k == 0)
            update(lft[a], ripe(org_ai[a]), -1), update(lft[a], ripe(org_ai[a] = b), 1);
        else
        {
            int res = queryKth(a, b, k);
            if (res == -1)
                puts("invalid request!");
            else
                printf("%d\n", mp[res - 1]);
        }
    }
    return 0;
}