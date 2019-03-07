// B.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define lowbit(x) (x & -x)
using namespace std;
const int MAX_N = 1e5 + 2000;
int n, t, dfn[MAX_N], st[20][MAX_N], tmpx, tmpy, tree[MAX_N << 2], lazy[MAX_N << 2], dtot, anti[MAX_N];
vector<int> G[MAX_N];
void addpath(int src, int dst) { G[src].push_back(dst); }
void pushdown(int p, int l, int r)
{
    if (lazy[p] && l != r)
    {
        tree[lson] = mid - l + 1, tree[rson] = r - mid;
        lazy[lson] = 1, lazy[rson] = 1;
    }
    lazy[p] = 0;
}
int update(int l, int r, int p, int c)
{
    if (c == 0)
        return -1;
    if (l == r)
    {
        tree[p] += c;
        return l;
    }
    int lft = (mid - l + 1) - tree[lson], rig = c - lft;
    int ans = 0;
    if (rig > 0)
    {
        tree[lson] = mid - l + 1, lazy[lson] = 1;
        ans = update(mid + 1, r, rson, rig);
    }
    else
        ans = update(l, mid, lson, c);
    tree[p] = tree[lson] + tree[rson];
    return ans;
}
void remove(int qx, int l, int r, int p)
{
    if (l == r && l == qx)
    {
        tree[p] = 0, lazy[p] = 0;
        return;
    }
    pushdown(p, l, r);
    if (qx <= mid)
        remove(qx, l, mid, lson);
    else
        remove(qx, mid + 1, r, rson);
    tree[p] = tree[lson] + tree[rson];
}
bool query(int qx, int l, int r, int p)
{
    if (l == r && l == qx)
        return tree[p];
    pushdown(p, l, r);
    if (qx <= mid)
        return query(qx, l, mid, lson);
    else
        return query(qx, mid + 1, r, rson);
}
void dfs(int u)
{
    sort(G[u].begin(), G[u].end());
    int siz = G[u].size();
    for (int i = 0; i < siz; i++)
    {
        int to = G[u][i];
        if (st[0][u] != to)
            st[0][to] = u, dfs(to);
    }
    dfn[u] = ++dtot, anti[dfn[u]] = u;
}
int main()
{
    scanf("%d%d", &n, &t);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs(1);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            st[i][j] = st[i - 1][st[i - 1][j]];
    while (t--)
    {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            printf("%d\n", anti[update(1, n, 1, x)]);
        else
        {
            int u = x, ans = 0;
            for (int i = 19; i >= 0; i--)
                if (st[i][u] != 0 && query(dfn[st[i][u]], 1, n, 1) == true)
                    u = st[i][u], ans += 1 << i;
            printf("%d\n", ans);
            remove(dfn[u], 1, n, 1);
        }
    }
    return 0;
}