// ARC085F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, INF = 0x3f3f3f3f;

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

int n, q, nodes[MAX_N << 2], dp[MAX_N], bi[MAX_N];
vector<int> pset[MAX_N];

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = INF);
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = min(nodes[lson], nodes[rson]);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    int ret = INF;
    if (ql <= mid)
        ret = min(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = min(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
        return (void)(nodes[p] = min(nodes[p], val));
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    nodes[p] = min(nodes[lson], nodes[rson]);
}

int main()
{
    int zeros = 0;
    scanf("%d", &n), build(1, n, 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]), zeros += (1 - bi[i]);
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        pset[l].push_back(r);
    }
    memset(dp, 0x3f, sizeof(dp)), dp[0] = 0;
    for (int l = 1; l <= n; l++)
    {
        for (int r : pset[l])
        {
            int ret = dp[l - 1];
            ret = min(ret, query(max(l - 1, 1), r, 1, n, 1));
            if (ret < dp[r])
                dp[r] = ret, update(r, 1, n, 1, ret);
        }
        dp[l] = min(dp[l], dp[l - 1] + (bi[l] == 1 ? 1 : -1));
    }
    printf("%d\n", dp[n] + zeros);
    return 0;
}