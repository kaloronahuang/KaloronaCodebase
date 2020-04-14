// P3466.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, m, nodes[MAX_N << 2], ai[MAX_N];
ll min_ans = 0x3f3f3f3f3f3f3f3f, ans_pos = n, nsum[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void update(int qx, int l, int r, int p, int val)
{
    nodes[p] += val, nsum[p] += val * qx;
    if (l == r)
        return;
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
}

int findK(int qk, int l, int r, int p)
{
    if (l == r)
        return l;
    if (qk <= nodes[lson])
        return findK(qk, l, mid, lson);
    else
        return findK(qk - nodes[lson], mid + 1, r, rson);
}

pair<ll, int> query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return make_pair(nsum[p], nodes[p]);
    int siz = 0;
    ll ret = 0;
    if (ql <= mid)
    {
        pair<ll, int> c = query(ql, qr, l, mid, lson);
        siz += c.second, ret += c.first;
    }
    if (mid < qr)
    {
        pair<ll, int> c = query(ql, qr, mid + 1, r, rson);
        siz += c.second, ret += c.first;
    }
    return make_pair(ret, siz);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    if (n == 1 && m == 1 && ai[1] == 0)
        puts("0"), exit(0);
    for (int i = 1; i <= m - 1; i++)
        update(ai[i], 1, 1e6, 1, 1);
    for (int i = m; i <= n; i++)
    {
        if (i - m != 0)
            update(ai[i - m], 1, 1e6, 1, -1);
        update(ai[i], 1, 1e6, 1, 1);
        int mid_val = findK((m + 1) >> 1, 1, 1e6, 1);
        pair<ll, int> lft = query(1, mid_val, 1, 1e6, 1), rig = query(mid_val + 1, 1e6, 1, 1e6, 1);
        ll cost = 1LL * mid_val * lft.second - lft.first + rig.first - 1LL * mid_val * rig.second;
        if (cost < min_ans)
            min_ans = cost, ans_pos = i;
    }
    printf("%lld\n", min_ans);
    return 0;
}