// P3180.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, m, q, roots[MAX_N], ptot, dep[MAX_N], fa[MAX_N], ai[MAX_N], upper;
vector<int> G[MAX_N], mp;

struct node
{
    int lson, rson, sum[2];
} nodes[MAX_N * 30];

void dfs(int u)
{
    dep[u] = dep[fa[u]] + 1;
    for (int v : G[u])
        if (v != fa[u])
        {
            if (dep[v] == 0)
                fa[v] = u, dfs(v);
            else if (dep[v] > dep[u])
                for (int cpt = v, tmp; cpt != u;)
                    tmp = fa[cpt], fa[cpt] = u, cpt = tmp;
        }
}

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].sum[1]++;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson);
    return p;
}

int merge(int x, int y)
{
    if (x == 0 || y == 0)
        return x + y;
    int p = ++ptot;
    if (nodes[x].lson == 0 && nodes[x].rson == 0)
    {
        int c = (nodes[x].sum[1] + nodes[y].sum[1]) % 2;
        nodes[p].sum[c]++;
        return p;
    }
    nodes[p].lson = merge(nodes[x].lson, nodes[y].lson);
    nodes[p].rson = merge(nodes[x].rson, nodes[y].rson);
    for (int i = 0; i <= 1; i++)
        nodes[p].sum[i] = nodes[nodes[p].lson].sum[i] + nodes[nodes[p].rson].sum[i];
    return p;
}

int query(int ql, int qr, int l, int r, int p, int oddity)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].sum[oddity];
    int ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson, oddity);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson, oddity);
    return ret;
}

#undef mid

void mergeDfs(int u)
{
    for (int v : G[u])
        mergeDfs(v), roots[u] = merge(roots[u], roots[v]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), mp.push_back(ai[i]);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    upper = mp.size();
    for (int i = 1; i <= n; i++)
        ai[i] = lower_bound(mp.begin(), mp.end(), ai[i]) - mp.begin() + 1;
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
    scanf("%d", &q), dfs(1);
    for (int i = 1; i <= n; i++)
        G[i].clear();
    for (int i = 1; i <= n; i++)
        if (fa[i] != 0)
            G[fa[i]].push_back(i);
    for (int i = 1; i <= n; i++)
        roots[i] = update(ai[i], 1, upper, roots[i]);
    mergeDfs(1);
    while (q--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        y = upper_bound(mp.begin(), mp.end(), y) - mp.begin();
        printf("%d\n", query(1, y, 1, upper, roots[x], opt));
    }
    return 0;
}