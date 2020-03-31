// P5439.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, mod = 998244353;

int n, m, ai[MAX_N], fa[MAX_N], dfn[MAX_N], dep[MAX_N], top[MAX_N], siz[MAX_N], son[MAX_N], ptot;
int nodes[MAX_N << 2], tag[MAX_N << 2], ans;
vector<int> G[MAX_N], Trie[MAX_N];

void dfs1(int u, int fat)
{
    fa[u] = fat, siz[u] = 1, dep[u] = dep[fat] + 1;
    for (auto x : Trie[u])
        dfs1(x, u), siz[u] += siz[x], son[u] = siz[x] > siz[son[u]] ? x : son[u];
}

void dfs2(int u, int org)
{
    dfn[u] = ++ptot, top[u] = org;
    if (son[u])
        dfs2(son[u], org);
    for (auto x : Trie[u])
        if (x != son[u])
            dfs2(x, x);
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

// SegmentTree;

void pushup(int p) { nodes[p] = (0LL + nodes[lson] + nodes[rson]) % mod; }

void pushdown(int p, int l, int r)
{
    if (tag[p])
    {
        nodes[lson] = (0LL + nodes[lson] + 1LL * (mid - l + 1) * tag[p] % mod) % mod;
        nodes[rson] = (0LL + nodes[rson] + 1LL * (r - mid) * tag[p] % mod) % mod;
        tag[lson] = (0LL + tag[lson] + tag[p]) % mod, tag[rson] = (0LL + tag[rson] + tag[p]) % mod;
        tag[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] = (0LL + nodes[p] + 1LL * (r - l + 1) * val % mod) % mod, tag[p] = (0LL + tag[p] + val) % mod);
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pushdown(p, l, r);
    int ret = 0;
    if (ql <= mid)
        ret = query(ql, qr, l, mid, lson);
    if (mid < qr)
        ret = (0LL + ret + query(ql, qr, mid + 1, r, rson)) % mod;
    return ret;
}

void updateRoot(int u, int val)
{
    while (u)
        update(dfn[top[u]], dfn[u], 1, m, 1, val), u = fa[top[u]];
}

int queryRoot(int u)
{
    int ret = 0;
    while (u)
        ret = (0LL + ret + query(dfn[top[u]], dfn[u], 1, m, 1)) % mod, u = fa[top[u]];
    return ret;
}

#undef mid
#undef rson
#undef lson

void prep(int u)
{
    siz[u] = 1;
    for (auto x : G[u])
        prep(x), siz[u] += siz[x];
}

void dfs(int u)
{
    ans = (0LL + ans + 1LL * siz[u] * queryRoot(ai[u]) % mod) % mod;
    updateRoot(ai[u], mod - siz[u]);
    for (auto x : G[u])
        updateRoot(ai[u], n - siz[x]), dfs(x), updateRoot(ai[u], mod - (n - siz[x]));
    updateRoot(ai[u], siz[u]);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, fa; i <= n; i++)
        scanf("%d", &fa), G[fa].push_back(i);
    for (int i = 1, fa; i <= m; i++)
        scanf("%d", &fa), Trie[fa].push_back(i);
    scanf("%*s");
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (auto x : Trie[1])
        dfs1(x, 0), dfs2(x, x);
    prep(G[0][0]);
    for (int i = 1; i <= n; i++)
        ans = (0LL + ans + 1LL * siz[i] * queryRoot(ai[i]) % mod) % mod, updateRoot(ai[i], siz[i]);
    for (int i = 1; i <= n; i++)
        updateRoot(ai[i], mod - siz[i]);
    dfs(G[0][0]), printf("%d\n", ans);
    return 0;
}