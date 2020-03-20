// BZ3730.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200, INF = 0x3f3f3f3f;

int n, head[MAX_N], current, val[MAX_N], ptot, q, siz[MAX_N], up[MAX_N], dep[MAX_N], lastans;
int st[20][MAX_N], log2_[MAX_N], stot, pos[MAX_N], groot, max_dep[MAX_N], roots[MAX_N], froots[MAX_N];
vector<int> G[MAX_N];
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    int lson, rson, sum;
} nodes[int(1e7) + 20];

inline char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
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

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int p, int val)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].sum += val;
    if (l == r)
        return p;
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
        return nodes[p].sum;
    int ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

int stack_counter = 0;

void dfs(int u, int fa)
{
    stack_counter++;
    st[0][++stot] = u, dep[u] = dep[fa] + 1, pos[u] = stot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), st[0][++stot] = u;
    stack_counter--;
}

int gmin(int x, int y) { return dep[x] < dep[y] ? x : y; }

int getLCA(int x, int y)
{
    if (pos[x] > pos[y])
        swap(x, y);
    int d = log2_[pos[y] - pos[x] + 1];
    return gmin(st[d][pos[x]], st[d][pos[y] - (1 << d) + 1]);
}

int getDist(int x, int y) { return dep[x] + dep[y] - (dep[getLCA(x, y)] << 1); }

namespace rootFinding
{

int val = INF, root;

void find_root(int u, int fa, int capacity)
{
    siz[u] = 1;
    int upper_siz = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
        {
            find_root(edges[i].to, u, capacity);
            siz[u] += siz[edges[i].to];
            upper_siz = max(upper_siz, siz[edges[i].to]);
        }
    upper_siz = max(upper_siz, capacity - siz[u]);
    if (upper_siz < val)
        root = u, val = upper_siz;
}

int find_root(int entry_point, int capacity)
{
    val = INF, root = 0;
    find_root(entry_point, 0, capacity);
    return root;
}

} // namespace rootFinding

int makeSize(int u, int fa, int d)
{
    siz[u] = 1;
    int ret = d;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !tag[edges[i].to])
            ret = max(ret, makeSize(edges[i].to, u, d + 1)), siz[u] += siz[edges[i].to];
    return ret;
}

int solve(int u, int capacity)
{
    tag[u] = true;
    if (capacity != 1)
    {
        max_dep[u] = makeSize(u, 0, 1);
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (!tag[edges[i].to])
            {
                int csiz = siz[edges[i].to], nxt = solve(rootFinding::find_root(edges[i].to, csiz), csiz);
                G[u].push_back(nxt), up[nxt] = u;
            }
    }
    return u;
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read(), q = read();
    for (int i = 1; i <= n; i++)
        val[i] = read();
    for (int i = 1, u, v; i <= n - 1; i++)
        u = read(), v = read(), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 2; i <= stot; i++)
        log2_[i] = log2_[i >> 1] + 1;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= stot; j++)
            st[i][j] = gmin(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    groot = solve(rootFinding::find_root(1, n), n);
    for (int i = 1; i <= n; i++)
        for (int u = i; u; u = up[u])
        {
            roots[u] = update(getDist(i, u), 0, max_dep[u], roots[u], val[i]);
            if (up[u])
                froots[u] = update(getDist(i, up[u]), 0, max_dep[up[u]], froots[u], val[i]);
        }
    while (q--)
    {
        int opt = read(), x = read() ^ lastans, y = read() ^ lastans;
        if (opt == 1)
        {
            for (int u = x; u; u = up[u])
            {
                roots[u] = update(getDist(x, u), 0, max_dep[u], roots[u], y - val[x]);
                if (up[u])
                    froots[u] = update(getDist(x, up[u]), 0, max_dep[up[u]], froots[u], y - val[x]);
            }
            val[x] = y;
        }
        else
        {
            // take y as radius;
            int ret = 0;
            for (int u = x; u; u = up[u])
            {
                if (getDist(u, x) <= y)
                    ret += query(0, y - getDist(u, x), 0, max_dep[u], roots[u]);
                if (up[u] && getDist(x, up[u]) <= y)
                    ret -= query(0, y - getDist(x, up[u]), 0, max_dep[up[u]], froots[u]);
            }
            printf("%d\n", lastans = ret);
        }
    }
    return 0;
}