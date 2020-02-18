// F2.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e4 + 200;

int log2_arr[MAX_N], n, m, k, mp[55][MAX_N], dp[55][MAX_N], pre[55][MAX_N];
int nodes[MAX_N << 2], tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p)
{
    if (tag[p] != 0)
    {
        nodes[lson] += tag[p], nodes[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void pushup(int p) { nodes[p] = max(nodes[lson], nodes[rson]); }

void build(int l, int r, int p, int *src)
{
    tag[p] = 0;
    if (l == r)
        return (void)(nodes[p] = src[l], tag[p] = 0);
    build(l, mid, lson, src), build(mid + 1, r, rson, src);
    pushup(p);
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] += val, tag[p] += val);
    pushdown(p);
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
    pushdown(p);
    int ret = -2e9;
    if (ql <= mid)
        ret = max(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = max(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &mp[i][j]), pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + mp[i][j];
    for (int i = 1; i <= m; i++)
        pre[n + 1][i] = pre[n][i];
    for (int i = 1; i <= n; i++)
    {
        build(1, m - k + 1, 1, dp[i - 1]);
        for (int j = 1; j <= k; j++)
            update(max(1, j - k + 1), j, 1, m - k + 1, 1, -mp[i][j]);
        for (int j = 1; j <= m - k + 1; j++)
        {
            // the interval is [j, min(j + k - 1, m)]
            int rig = j + k - 1, block = pre[i + 1][rig] - pre[i + 1][j - 1] - pre[i - 1][rig] + pre[i - 1][j - 1];
            dp[i][j] = block + (i == 1 ? 0 : nodes[1]);
            update(max(1, j - k + 1), j, 1, m - k + 1, 1, mp[i][j]);
            if (rig != m)
                update(max(1, rig - k + 2), min(rig + 1, m - k + 1), 1, m - k + 1, 1, -mp[i][rig + 1]);
        }
    }
    int ans = 0;
    for (int i = 1; i + k - 1 <= m; i++)
        ans = max(ans, dp[n][i]);
    printf("%d\n", ans);
    return 0;
}