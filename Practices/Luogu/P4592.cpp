// P4592.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, LOG = 30;

int n, q, head[MAX_N], current, lft[MAX_N], rig[MAX_N], roots[MAX_N], ptot, val[MAX_N];
int top[MAX_N], dep[MAX_N], siz[MAX_N], son[MAX_N], dtot, up[MAX_N];

struct node
{
    int ch[2], val;
} nodes[MAX_N * LOG];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int insert(int num, int dep, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].val++;
    if (dep == -1)
        return p;
    int bit = (num >> dep) & 1;
    nodes[p].ch[bit] = insert(num, dep - 1, nodes[pre].ch[bit]);
    return p;
}

int queryTrie(int p, int pre, int x)
{
    int ret = 0;
    for (int i = 29; i >= 0; i--)
    {
        int bit = (x >> i) & 1;
        if (nodes[nodes[p].ch[bit ^ 1]].val - nodes[nodes[pre].ch[bit ^ 1]].val > 0)
            p = nodes[p].ch[bit ^ 1], pre = nodes[pre].ch[bit ^ 1], ret ^= (1 << i);
        else
            p = nodes[p].ch[bit], pre = nodes[pre].ch[bit];
    }
    return ret;
}

int query(int x, int y, int cval)
{
    int ret = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ret = max(ret, queryTrie(roots[lft[x]], roots[lft[top[x]] - 1], cval));
        x = up[top[x]];
    }
    if (lft[x] < lft[y])
        swap(x, y);
    ret = max(ret, queryTrie(roots[lft[x]], roots[lft[y] - 1], cval));
    return ret;
}

void dfs1(int u, int fa)
{
    siz[u] = 1, dep[u] = dep[fa] + 1, up[u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs1(edges[i].to, u), siz[u] += siz[edges[i].to];
            son[u] = (siz[son[u]] < siz[edges[i].to]) ? edges[i].to : son[u];
        }
}

void dfs2(int u, int fa, int org)
{
    lft[u] = ++dtot, top[u] = org, roots[dtot] = insert(val[u], 29, roots[dtot - 1]);
    if (son[u])
        dfs2(son[u], u, org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && edges[i].to != son[u])
            dfs2(edges[i].to, u, edges[i].to);
    rig[u] = dtot;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs1(1, 0), dfs2(1, 0, 1);
    while (q--)
    {
        int opt, x, y, val;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
            printf("%d\n", queryTrie(roots[rig[x]], roots[lft[x] - 1], y));
        else
            scanf("%d", &val), printf("%d\n", query(x, y, val));
    }
    return 0;
}