// CF1083C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

int n, q, head[MAX_N], current, dep[MAX_N], st[20][MAX_N], wi[MAX_N], ptot, up[MAX_N], pos[MAX_N], log2_[MAX_N], bucket[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    int u, v;
} nodes[MAX_N << 2];

char nc()
{
    static char buffer[1 << 20], *p1, *p2;
    return p1 == p2 && (p2 = (p1 = buffer) + fread(buffer, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char c = nc();
    while (!isdigit(c))
        f = (c == '-' ? -1 : f), c = nc();
    while (isdigit(c))
        x = (x << 3) + (x << 1) + c - '0', c = nc();
    return x * f;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    dep[u] = dep[up[u]] + 1, st[0][++ptot] = u, pos[u] = ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), st[0][++ptot] = u;
}

int getLCA(int x, int y)
{
    if (pos[x] > pos[y])
        swap(x, y);
    int len = pos[y] - pos[x] + 1, d = log2_[len];
    int lft = st[d][pos[x]], rig = st[d][pos[y] - (1 << d) + 1];
    return dep[lft] < dep[rig] ? lft : rig;
}

int getDist(int x, int y) { return dep[x] + dep[y] - (dep[getLCA(x, y)] << 1); }

node mergeNode(node u, int w)
{
    if (u.u == -1 || w == -1)
        return node{-1, -1};
    int d1 = getDist(u.u, u.v), d2 = getDist(u.u, w), d3 = getDist(u.v, w);
    return d1 == d2 + d3 ? u : ((d1 + d3 == d2) ? node{u.u, w} : (d1 + d2 == d3 ? node{u.v, w} : node{-1, -1}));
}

node pushup(node lson, node rson) { return mergeNode(mergeNode(lson, rson.u), rson.v); }

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = node{bucket[l], bucket[l]});
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = pushup(nodes[lson], nodes[rson]);
}

void update(int qx, int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = node{bucket[l], bucket[l]});
    if (qx <= mid)
        update(qx, l, mid, lson);
    else
        update(qx, mid + 1, r, rson);
    nodes[p] = pushup(nodes[lson], nodes[rson]);
}

int query(node &tmp, int l, int r, int p)
{
    if (nodes[p].u != -1)
    {
        if (tmp.u == -1)
            return tmp = nodes[p], r + 1;
        node curt = pushup(tmp, nodes[p]);
        if (curt.u != -1)
            return tmp = curt, r + 1;
    }
    if (l == r)
        return l;
    int ls = query(tmp, l, mid, lson);
    if (ls <= mid)
        return ls;
    else
        return query(tmp, mid + 1, r, rson);
}

#undef mid
#undef rson
#undef lson

int main()
{
    memset(head, -1, sizeof(head)), n = read();
    for (int i = 1; i <= n; i++)
        wi[i] = read(), bucket[wi[i]] = i;
    for (int i = 2; i <= n; i++)
        up[i] = read(), addpath(up[i], i);
    dfs(1);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j + (1 << i) - 1 <= ptot; j++)
            st[i][j] = (dep[st[i - 1][j]] < dep[st[i - 1][j + (1 << (i - 1))]]) ? st[i - 1][j] : st[i - 1][j + (1 << (i - 1))];
    for (int i = 2; i <= ptot; i++)
        log2_[i] = (log2_[i >> 1] + 1);
    build(0, n - 1, 1), q = read();
    while (q--)
    {
        int opt = read(), u, v;
        if (opt == 1)
        {
            u = read(), v = read(), swap(bucket[wi[u]], bucket[wi[v]]), swap(wi[u], wi[v]);
            update(wi[u], 0, n - 1, 1), update(wi[v], 0, n - 1, 1);
        }
        else
        {
            node tmp = node{-1, -1};
            printf("%d\n", query(tmp, 0, n - 1, 1));
        }
    }
    return 0;
}