// UOJ388.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353;

int n, m, head[MAX_N], current, siz[MAX_N], son[MAX_N], nodes[MAX_N << 2][2][2], seq[MAX_N], upweight[MAX_N], ans;
vector<int> pos[MAX_N];
bool tag[MAX_N << 2];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

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

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void prep(int u, int fa)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            prep(edges[i].to, u), siz[u] += siz[edges[i].to], upweight[edges[i].to] = edges[i].weight;
            son[u] = siz[edges[i].to] > siz[son[u]] ? edges[i].to : son[u];
        }
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            nodes[p][i][j] = nodes[lson][i][j] + nodes[rson][i][j];
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p][l & 1][0] = 1);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void mark(int p)
{
    tag[p] ^= 1;
    swap(nodes[p][0][0], nodes[p][0][1]);
    swap(nodes[p][1][0], nodes[p][1][1]);
}

void pushdown(int p)
{
    if (tag[p])
        mark(lson), mark(rson), tag[p] = 0;
}

void update(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return (void)(mark(p));
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson);
    pushup(p);
}

#undef mid
#undef rson
#undef lson

void insert(int u)
{
    for (auto &x : pos[u])
        update(x, m, 0, m, 1);
}

void collect(int u, int fa)
{
    insert(u);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            collect(edges[i].to, u);
}

void solve(int u, int fa, bool save)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && edges[i].to != son[u])
            solve(edges[i].to, u, false);
    if (son[u] != 0)
        solve(son[u], u, true);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && edges[i].to != son[u])
            collect(edges[i].to, u);
    insert(u);
    ans = (0LL + ans + 1LL * upweight[u] * ((1LL * nodes[1][0][0] * nodes[1][0][1] % mod + 1LL * nodes[1][1][0] * nodes[1][1][1] % mod) % mod) % mod) % mod;
    if (!save)
        collect(u, fa);
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read(), m = read();
    for (int i = 1, u, v, w; i <= n - 1; i++)
        u = read(), v = read(), w = read(), addpath(u, v, w), addpath(v, u, w);
    for (int i = 1; i <= m; i++)
        pos[read()].push_back(i);
    prep(1, 0), build(0, m, 1), solve(1, 0, true), printf("%d\n", ans);
    return 0;
}