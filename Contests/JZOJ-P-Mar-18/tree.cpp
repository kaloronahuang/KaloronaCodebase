// tree.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, head[MAX_N], current, typ, q, lastans, upweight[MAX_N], anti[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

namespace PST
{

struct node
{
    int lson, rson, tag, sum;
} nodes[MAX_N * 50];

int ptot;

#define mid ((l + r) >> 1)

int build(int l, int r)
{
    int p = ++ptot;
    if (l == r)
    {
        nodes[p].sum = upweight[anti[l]];
        return p;
    }
    nodes[p].lson = build(l, mid), nodes[p].rson = build(mid + 1, r);
    nodes[p].sum = nodes[nodes[p].lson].sum + nodes[nodes[p].rson].sum;
    return p;
}

int update(int ql, int qr, int l, int r, int pre, int val)
{
    int p = ++ptot;
    nodes[p] = nodes[pre];
    nodes[p].sum += (min(r, qr) - max(l, ql) + 1) * val;
    if (ql <= l && r <= qr)
        return (nodes[p].tag += val, p);
    if (ql <= mid)
        nodes[p].lson = update(ql, qr, l, mid, nodes[pre].lson, val);
    if (mid < qr)
        nodes[p].rson = update(ql, qr, mid + 1, r, nodes[pre].rson, val);
    return p;
}

int query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    int ret = (min(r, qr) - max(l, ql) + 1) * nodes[p].tag;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

} // namespace PST

namespace TreeManager
{

int dfn[MAX_N], ptot, dep[MAX_N], siz[MAX_N], son[MAX_N], top[MAX_N], fa[MAX_N];

void dfs1(int u)
{
    siz[u] = 1, dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            fa[edges[i].to] = u, dfs1(edges[i].to), siz[u] += siz[edges[i].to];
            if (siz[edges[i].to] > siz[son[u]])
                son[u] = edges[i].to;
        }
}

void dfs2(int u, int org)
{
    dfn[u] = ++ptot, anti[ptot] = u, top[u] = org;
    if (son[u])
        dfs2(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u] && edges[i].to != son[u])
            dfs2(edges[i].to, edges[i].to);
}

int update(int x, int y, int val, int root)
{
    int pt = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        pt = PST::update(dfn[top[x]], dfn[x], 1, n, root, val);
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y])
        swap(dfn[x], dfn[y]);
    pt = PST::update(dfn[x], dfn[y], 1, n, root, val);
    return pt;
}

int query(int x, int y, int root)
{
    int ret = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ret += PST::query(dfn[top[x]], dfn[x], 1, n, root);
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y])
        swap(dfn[x], dfn[y]);
    ret += PST::query(dfn[x], dfn[y], 1, n, root);
    return ret;
}

bool in(int root, int v) { return dfn[root] <= dfn[v] && dfn[v] <= dfn[root] + siz[root] - 1; }

} // namespace TreeManager

namespace connection
{

struct node
{
    int lbound, rbound, pst_root, passthrough_dist, fat_down;
    bool operator<(const node &rhs) const { return lbound < rhs.lbound; }
} nodes[MAX_N];

int ptot, current_pt, fa[20][MAX_N], up[20][MAX_N], dep[MAX_N];
vector<int> G[MAX_N];

void copy_tree(int pos, int w)
{
    int p = ++ptot;
    nodes[p].lbound = nodes[p - 1].rbound + 1;
    nodes[p].rbound = nodes[p].lbound + n - 1;
    nodes[p].pst_root = current_pt = TreeManager::update(1, 1, w, current_pt);
    int fat_node = lower_bound(nodes + 1, nodes + 1 + ptot, node{pos, 0, 0, 0}) - nodes;
    nodes[p].fat_down = pos = (pos - 1) % n + 1;
    fa[0][p] = fat_node, nodes[p].passthrough_dist = TreeManager::query(pos, 1, nodes[fat_node].pst_root) + w;
    dep[p] = dep[fat_node] + 1, up[0][p] = nodes[p].passthrough_dist, G[fat_node].push_back(p);
    for (int i = 1; i < 20; i++)
        fa[i][p] = fa[i - 1][fa[i - 1][p]], up[i][p] = (up[i - 1][p] + up[i - 1][fa[i - 1][p]]);
}

int queryInnerNode(int x, int y)
{
    int ver = (x - 1) / n + 1;
    return TreeManager::query(x, y, nodes[ver].pst_root);
}

int query(int x, int y)
{
    int px = (x - 1) / n + 1, py = (y - 1) / n + 1, posx = (x - 1) % n + 1, posy = (y - 1) % n + 1;
    int ret = 0;
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][px]] >= dep[py])
            ret += up[i][px], posx = nodes[px].fat_down, px = fa[i][px];
    if (px != py)
    {
        for (int i = 19; i >= 0; i--)
            if (fa[i][px] != fa[i][py])
                posx = nodes[px].fat_down, posy = nodes[py].fat_down, px = fa[i][px], py = fa[i][py];
        posx = nodes[px].fat_down, posy = nodes[py].fat_down;
    }
    return ret + queryInnerNode(posx, posy);
}

ll dfs(int u)
{
    ll ret = PST::nodes[nodes[u].pst_root].sum;
    for (int i = 0, siz = G[u].size(); i < siz; i++)
        ret += dfs(G[u][i]);
    return ret;
}

ll querySubtree(int p)
{
    int pt = (p - 1) % n + 1;
    ll ret = PST::query(TreeManager::dfn[pt], TreeManager::dfn[pt] + TreeManager::siz[pt] - 1, 1, n, nodes[p].pst_root);
    for (int i = 0, siz = G[p].size(); i < siz; i++)
        if (TreeManager::in(pt, nodes[G[p][i]].fat_down))
            ret += dfs(G[p][i]);
    return ret;
}

} // namespace connection

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            upweight[edges[i].to] = edges[i].weight, dfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &q, &typ);
    // todo:ll;
    for (int i = 1, u, v, w; i < n; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs(1, 0), connection::current_pt = PST::build(1, n), TreeManager::dfs1(1), TreeManager::dfs2(1, 1);
    connection::nodes[++connection::ptot] = connection::node{1, n, connection::current_pt, 0, 0};
    while (q--)
    {
        int opt, a, b, c;
        scanf("%d%d", &opt, &a), a ^= typ * lastans;
        if (opt == 1)
        {
            scanf("%d%d", &b, &c), b ^= typ * lastans, c ^= typ * lastans;
            connection::current_pt = TreeManager::update((a - 1) % n + 1, (b - 1) % n + 1, c, connection::current_pt);
        }
        else if (opt == 2)
        {
            scanf("%d", &b), b ^= typ * lastans;
            connection::copy_tree(a, b);
        }
        else if (opt == 3)
        {
            scanf("%d", &b), b ^= typ * lastans;
            printf("%d\n", lastans = connection::query(a, b));
        }
        else
            printf("%d\n", lastans = connection::querySubtree(a));
    }
    return 0;
}