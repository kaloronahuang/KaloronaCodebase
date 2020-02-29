// BZ3772.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 2;

typedef pair<int, int> pii;
typedef long long ll;

int n, m, head[MAX_N], current, lft[MAX_N], rig[MAX_N], dtot, ptot;
int roots[MAX_N], up[18][MAX_N], dep[MAX_N];
pii routes[MAX_N];
vector<int> routeDst[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    int lson, rson, val;
} nodes[MAX_N * 39];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    lft[u] = ++dtot, dep[u] = dep[fa] + 1, up[0][u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    rig[u] = ++dtot;
}

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int pre, int val)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].val += val;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson, val);
    return p;
}

int query(int ql, int qr, int l, int r, int pre1, int pre2, int p1, int p2)
{
    if (ql <= l && r <= qr)
        return nodes[p1].val + nodes[p2].val - nodes[pre1].val - nodes[pre2].val;
    int ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[pre1].lson, nodes[pre2].lson, nodes[p1].lson, nodes[p2].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[pre1].rson, nodes[pre2].rson, nodes[p1].rson, nodes[p2].rson);
    return ret;
}

#undef mid

void build(int u, int fa)
{
    roots[u] = roots[fa];
    for (int i = 0, siz = routeDst[u].size(); i < siz; i++)
    {
        roots[u] = update(lft[routeDst[u][i]], 1, dtot, roots[u], 1);
        roots[u] = update(rig[routeDst[u][i]], 1, dtot, roots[u], -1);
    }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            build(edges[i].to, u);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 17; i >= 0; i--)
        if (dep[up[i][x]] >= dep[y])
            x = up[i][x];
    if (x == y)
        return x;
    for (int i = 17; i >= 0; i--)
        if (up[i][x] != up[i][y])
            x = up[i][x], y = up[i][y];
    return up[0][x];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 1; i < 18; i++)
        for (int j = 1; j <= n; j++)
            up[i][j] = up[i - 1][up[i - 1][j]];
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &routes[i].first, &routes[i].second), routeDst[routes[i].first].push_back(routes[i].second);
    build(1, 0);
    ll ans = 0;
    for (int i = 1; i <= m; i++)
    {
        int u = routes[i].first, v = routes[i].second, lca = getLCA(u, v);
        ans += query(lft[lca], lft[u], 1, dtot, roots[lca], roots[up[0][lca]], roots[u], roots[v]);
        ans += query(lft[lca], lft[v], 1, dtot, roots[lca], roots[up[0][lca]], roots[u], roots[v]);
        ans -= query(lft[lca], lft[lca], 1, dtot, roots[lca], roots[up[0][lca]], roots[u], roots[v]) + 1;
        continue;
    }
    ll d = gcd(ans, 1LL * m * (m - 1) / 2);
    printf("%lld/%lld\n", ans / d, (1LL * m * (m - 1) / 2) / d);
    return 0;
}