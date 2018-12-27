// P3899.cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define ll long long
#define mid ((l + r) >> 1)
using namespace std;
const ll MX_N = 3e5 + 1000;
ll ncnt, dfn[MX_N], low[MX_N], antiDFN[MX_N], ndfn, dep[MX_N], fa[MX_N], n, q, tmpx, tmpy;
ll subtree[MX_N], roots[MX_N];
vector<ll> G[MX_N];
struct node
{
    ll sum, ls, rs;
} nodes[MX_N * (2 << 5)];
ll build(ll l, ll r)
{
    ll p = ++ncnt;
    if (l == r)
        return p;
    nodes[p].ls = build(l, mid), nodes[p].rs = build(mid + 1, r);
    nodes[p].sum = 0;
    return p;
}
ll update(ll l, ll r, ll previous, ll depth, ll ad)
{
    ll curt = ++ncnt;
    nodes[curt].ls = nodes[previous].ls, nodes[curt].rs = nodes[previous].rs;
    nodes[curt].sum = nodes[previous].sum + ad;
    if (l == r && l == depth)
        return curt;
    if (depth <= mid)
        nodes[curt].ls = update(l, mid, nodes[previous].ls, depth, ad);
    else
        nodes[curt].rs = update(mid + 1, r, nodes[previous].rs, depth, ad);
    return curt;
}
ll query(ll ql, ll qr, ll l, ll r, ll p)
{
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    if (mid >= qr)
        return query(ql, qr, l, mid, nodes[p].ls);
    if (mid < ql)
        return query(ql, qr, mid + 1, r, nodes[p].rs);
    return query(ql, qr, l, mid, nodes[p].ls) + query(ql, qr, mid + 1, r, nodes[p].rs);
}
void dfs(ll u)
{
    dfn[u] = ++ndfn, subtree[u]++;
    antiDFN[ndfn] = u, dep[u] = dep[fa[u]] + 1;
    ll siz = G[u].size();
    for (ll i = 0; i < siz; i++)
        if (G[u][i] != fa[u])
            fa[G[u][i]] = u, dfs(G[u][i]), subtree[u] += subtree[G[u][i]];
    low[u] = ndfn;
}
int main()
{
    scanf("%lld%lld", &n, &q);
    for (int i = 0; i < n - 1; i++)
        scanf("%lld%lld", &tmpx, &tmpy), G[tmpx].push_back(tmpy), G[tmpy].push_back(tmpx);
    dfs(1), roots[0] = build(1, n);
    for (int i = 1; i <= n; i++)
        roots[i] = update(1, n, roots[i - 1], dep[antiDFN[i]], subtree[antiDFN[i]] - 1);
    while (q--)
    {
        scanf("%lld%lld", &tmpx, &tmpy);
        ll ret = min(dep[tmpx] - 1, tmpy) * (subtree[tmpx] - 1);
        ll another = query(dep[tmpx], dep[tmpx] + tmpy, 1, n, roots[low[tmpx]]) -
                     query(dep[tmpx], dep[tmpx] + tmpy, 1, n, roots[dfn[tmpx]]);
        printf("%lld\n", ret + another);
    }
    return 0;
}