// BZ5017.cpp
#include <bits/stdc++.h>
#define ll long long
#define mid ((l + r) >> 1)

using namespace std;

const int MAX_N = 2000010, mod = 1e9 + 7;

ll xi[MAX_N], ri[MAX_N], mp[MAX_N], mp_tot, dp_l[MAX_N], dp_r[MAX_N];
int head[MAX_N], current, lson[MAX_N], rson[MAX_N], seg_tot, n, block_tot;
int dfn[MAX_N], low[MAX_N], dfn_tot, q[MAX_N], hd, aff[MAX_N], root;
bool instack[MAX_N], vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N * 20];

void addpath(int src, int dst)
{
    edges[current].nxt = head[src], edges[current].to = dst;
    head[src] = current++;
}

int build(int l, int r)
{
    if (l == r)
        return l;
    int p = ++seg_tot;
    lson[p] = build(l, mid), rson[p] = build(mid + 1, r);
    addpath(p, lson[p]), addpath(p, rson[p]);
    return p;
}

void connect(int ql, int qr, int qx, int l, int r, int p)
{
    if (ql > qr)
        return;
    if (ql <= l && r <= qr)
        return (void)addpath(qx, p);
    if (ql <= mid)
        connect(ql, qr, qx, l, mid, lson[p]);
    if (mid < qr)
        connect(ql, qr, qx, mid + 1, r, rson[p]);
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfn_tot, q[++hd] = u;
    instack[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (instack[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u] && ++block_tot)
        do
        {
            int v = q[hd];
            instack[v] = false, aff[v] = block_tot;
            if (v <= n)
                dp_l[block_tot] = min(dp_l[block_tot], xi[v] - ri[v]), dp_r[block_tot] = max(dp_r[block_tot], xi[v] + ri[v]);
        } while (q[hd--] != u);
}

void dfs(int u)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (!vis[edges[i].to])
            dfs(edges[i].to);
        dp_l[u] = min(dp_l[u], dp_l[edges[i].to]);
        dp_r[u] = max(dp_r[u], dp_r[edges[i].to]);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), block_tot = seg_tot = n;
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &xi[i], &ri[i]), mp[++mp_tot] = xi[i];
    sort(mp + 1, mp + 1 + mp_tot);
    mp_tot = unique(mp + 1, mp + 1 + mp_tot) - mp - 1;
    root = build(1, n), block_tot = seg_tot;
    for (int i = 1; i <= n; i++)
    {
        int l = lower_bound(mp + 1, mp + 1 + mp_tot, xi[i] - ri[i]) - mp;
        int r = lower_bound(mp + 1, mp + 1 + mp_tot, xi[i] + ri[i]) - mp;
        if (mp[r] != xi[i] + ri[i])
            r--;
        int m = lower_bound(mp + 1, mp + 1 + mp_tot, xi[i]) - mp;
        connect(l, m - 1, m, 1, n, root), connect(m + 1, r, m, 1, n, root);
    }
    for (int i = 1; i < MAX_N; i++)
        dp_l[i] = 0x3f3f3f3f3f3f3f, dp_r[i] = -0x3f3f3f3f3f3f3f;
    for (int i = 1; i <= seg_tot; i++)
        if (!dfn[i])
            tarjan(i);
    for (int u = 1; u <= seg_tot; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[u] != aff[edges[i].to])
                addpath(aff[u], aff[edges[i].to]);
    for (int i = 1; i <= block_tot; i++)
        if (!vis[edges[i].to])
            dfs(i);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int l = lower_bound(mp + 1, mp + 1 + mp_tot, dp_l[aff[i]]) - mp;
        int r = lower_bound(mp + 1, mp + 1 + mp_tot, dp_r[aff[i]]) - mp;
        if (mp[r] != dp_r[aff[i]])
            r--;
        ans = (1LL * ans + 1LL * (r - l + 1) * i % mod) % mod;
    }
    printf("%d", ans);
    return 0;
}