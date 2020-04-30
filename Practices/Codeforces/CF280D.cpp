// CF280D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_K = 21;

int n, ai[MAX_N], q;

struct node
{
    int dp[MAX_K][2][2];
    void clear() { memset(dp, -0x3f, sizeof(dp)), dp[0][0][0] = 0; }
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

node pushup(node ls, node rs)
{
    node ret;
    ret.clear();
    for (int i = 0; i <= 20; i++)
        for (int j = 0; i + j <= 20; j++)
        {
            ret.dp[i + j][0][0] = max({ret.dp[i + j][0][0], ls.dp[i][0][0] + rs.dp[j][0][0], ls.dp[i][0][1] + rs.dp[j][0][0], ls.dp[i][0][0] + rs.dp[j][1][0]});
            ret.dp[i + j][1][0] = max({ret.dp[i + j][1][0], ls.dp[i][1][0] + rs.dp[j][0][0], ls.dp[i][1][1] + rs.dp[j][0][0], ls.dp[i][1][0] + rs.dp[j][1][0]});
            ret.dp[i + j][0][1] = max({ret.dp[i + j][0][1], ls.dp[i][0][0] + rs.dp[j][0][1], ls.dp[i][0][1] + rs.dp[j][0][1], ls.dp[i][0][0] + rs.dp[j][1][1]});
            ret.dp[i + j][1][1] = max({ret.dp[i + j][1][1], ls.dp[i][1][0] + rs.dp[j][0][1], ls.dp[i][1][1] + rs.dp[j][0][1], ls.dp[i][1][0] + rs.dp[j][1][1]});
        }
    for (int i = 0; i <= 20; i++)
        for (int j = 0; j <= 20 && i + j - 1 <= 20; j++)
            if (i + j - 1 >= 0)
            {
                ret.dp[i + j - 1][0][0] = max({ret.dp[i + j - 1][0][0], ls.dp[i][0][1] + rs.dp[j][1][0]});
                ret.dp[i + j - 1][1][0] = max({ret.dp[i + j - 1][1][0], ls.dp[i][1][1] + rs.dp[j][1][0]});
                ret.dp[i + j - 1][0][1] = max({ret.dp[i + j - 1][0][1], ls.dp[i][0][1] + rs.dp[j][1][1]});
                ret.dp[i + j - 1][1][1] = max({ret.dp[i + j - 1][1][1], ls.dp[i][1][1] + rs.dp[j][1][1]});
            }
    return ret;
}

void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p].clear(), nodes[p].dp[1][1][1] = ai[l];
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = pushup(nodes[lson], nodes[rson]);
}

void update(int qx, int l, int r, int p)
{
    if (l == r)
    {
        nodes[p].dp[1][1][1] = ai[l];
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson);
    else
        update(qx, mid + 1, r, rson);
    nodes[p] = pushup(nodes[lson], nodes[rson]);
}

node query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    bool flag1 = ql <= mid, flag2 = mid < qr;
    if (flag1 && flag2)
        return pushup(query(ql, qr, l, mid, lson), query(ql, qr, mid + 1, r, rson));
    if (flag1)
        return query(ql, qr, l, mid, lson);
    else
        return query(ql, qr, mid + 1, r, rson);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    build(1, n, 1), scanf("%d", &q);
    while (q--)
    {
        int opt, l, r, k;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 0)
            ai[l] = r, update(l, 1, n, 1);
        else
        {
            scanf("%d", &k);
            node ret = query(l, r, 1, n, 1);
            int ans = 0;
            for (int i = 0; i <= k; i++)
                ans = max({ans, ret.dp[i][0][0], ret.dp[i][0][1], ret.dp[i][1][0], ret.dp[i][1][1]});
            printf("%d\n", ans);
        }
    }
    return 0;
}