// P4556.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100010;

struct node
{
    int lson, rson, val, max_pos;
} tree[MAX_N * 60];

int ptot, n, m, head[MAX_N], current, fa[21][MAX_N], dep[MAX_N], roots[MAX_N];
int answer[MAX_N], us[MAX_N], vs[MAX_N], wes[MAX_N], range;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void pushup(int p)
{
    if (tree[tree[p].rson].val <= tree[tree[p].lson].val)
        tree[p].val = tree[tree[p].lson].val, tree[p].max_pos = tree[tree[p].lson].max_pos;
    else
        tree[p].val = tree[tree[p].rson].val, tree[p].max_pos = tree[tree[p].rson].max_pos;
    return;
}

int update(int qx, int l, int r, int p, int val)
{
    if (p == 0)
        p = ++ptot;
    if (l == r)
    {
        tree[p].val += val, tree[p].max_pos = l;
        return p;
    }
    int mid = (l + r) >> 1;
    if (qx <= mid)
        tree[p].lson = update(qx, l, mid, tree[p].lson, val);
    else
        tree[p].rson = update(qx, mid + 1, r, tree[p].rson, val);
    pushup(p);
    return p;
}

int merge(int p, int pre, int l, int r)
{
    if (p == 0)
        return pre;
    if (pre == 0)
        return p;
    if (l == r)
    {
        tree[p].val += tree[pre].val;
        tree[p].max_pos = l;
        return p;
    }
    int mid = (l + r) >> 1;
    tree[p].lson = merge(tree[p].lson, tree[pre].lson, l, mid);
    tree[p].rson = merge(tree[p].rson, tree[pre].rson, mid + 1, r);
    pushup(p);
    return p;
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 20; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 20; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

void dfs1(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
        {
            dep[edges[i].to] = dep[u] + 1, fa[0][edges[i].to] = u;
            dfs1(edges[i].to);
        }
}

void dfs2(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (fa[0][u] != edges[i].to)
            dfs2(edges[i].to), roots[u] = merge(roots[u], roots[edges[i].to], 1, range);
    if (tree[roots[u]].val != 0)
        answer[u] = tree[roots[u]].max_pos;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dep[1] = 1, dfs1(1);
    for (int i = 1; i <= 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &us[i], &vs[i], &wes[i]), range = max(range, wes[i]);
    for (int i = 1; i <= m; i++)
    {
        int u = us[i], v = vs[i], w = wes[i];
        roots[u] = update(w, 1, range, roots[u], 1);
        roots[v] = update(w, 1, range, roots[v], 1);
        int lca = getLCA(u, v);
        roots[lca] = update(w, 1, range, roots[lca], -1);
        if (fa[0][lca])
            roots[fa[0][lca]] = update(w, 1, range, roots[fa[0][lca]], -1);
        continue;
    }
    dfs2(1);
    for (int i = 1; i <= n; i++)
        printf("%d\n", answer[i]);
    return 0;
}
