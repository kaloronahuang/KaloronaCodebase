// CF487E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, q, head[MAX_N], current, val[MAX_N], ncnt, ptot, dfn[MAX_N], low[MAX_N], lft[MAX_N], stk[MAX_N], tail, top[MAX_N], up[MAX_N];
int siz[MAX_N], son[MAX_N], nodes[MAX_N << 2], dep[MAX_N], idx[MAX_N];
vector<int> G[MAX_N], aff[MAX_N];
multiset<int> rect[MAX_N];
char cmdlet[20];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
        {
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
            if (dfn[u] == low[edges[i].to])
            {
                int bcc = ++ncnt;
                for (int x = 0; x != edges[i].to; tail--)
                    x = stk[tail], G[bcc].push_back(x), G[x].push_back(bcc);
                G[u].push_back(bcc), G[bcc].push_back(u);
            }
        }
        else
            low[u] = min(low[u], dfn[edges[i].to]);
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = val[idx[l]]);
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = min(nodes[lson], nodes[rson]);
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
        return (void)(nodes[p] = val);
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    nodes[p] = min(nodes[lson], nodes[rson]);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    int ret = 0x7fffffff;
    if (ql <= mid)
        ret = min(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = min(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

void dfs1(int u, int fa)
{
    siz[u] = 1, up[u] = fa, dep[u] = dep[fa] + 1;
    for (int v : G[u])
        if (v != fa)
            dfs1(v, u), siz[u] += siz[v], son[u] = siz[v] > siz[son[u]] ? v : son[u];
}

void dfs2(int u, int org)
{
    lft[u] = ++ptot, top[u] = org, idx[ptot] = u;
    if (son[u] != 0)
        dfs2(son[u], org);
    for (int v : G[u])
        if (v != up[u] && v != son[u])
            dfs2(v, v);
}

int query(int x, int y)
{
    int ret = 0x7fffffff;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ret = min(ret, query(lft[top[x]], lft[x], 1, ncnt, 1));
        x = up[top[x]];
    }
    if (lft[x] > lft[y])
        swap(x, y);
    ret = min(ret, query(lft[x], lft[y], 1, ncnt, 1));
    if (x > n)
        ret = min(ret, val[up[x]]);
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q), ncnt = n;
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i);
    ptot = 0, dfs1(1, 0), dfs2(1, 0);
    for (int i = 1; i <= n; i++)
        if (up[i] != 0)
            rect[up[i]].insert(val[i]);
    for (int i = n + 1; i <= ncnt; i++)
        val[i] = *rect[i].begin();
    build(1, ncnt, 1);
    while (q--)
    {
        int a, b;
        scanf("%s%d%d", cmdlet + 1, &a, &b);
        if (cmdlet[1] == 'C')
        {
            update(lft[a], 1, ncnt, 1, b);
            if (up[a] != 0)
            {
                rect[up[a]].erase(rect[up[a]].find(val[a]));
                rect[up[a]].insert(b);
            }
            if (up[a] > n)
                val[up[a]] = *rect[up[a]].begin(), update(lft[up[a]], 1, ncnt, 1, val[up[a]]);
            val[a] = b;
        }
        else
            printf("%d\n", query(a, b));
    }
    return 0;
}