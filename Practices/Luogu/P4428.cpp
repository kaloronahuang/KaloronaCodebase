// P4428.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;

int n, q, bits, str[MAX_N];

struct node
{
    ll clft[2][2], crig[2][2], fl[3], fr[3], ans, lftzero, rigzero;
    int sum[2];

    void clear()
    {
        memset(clft, 0, sizeof(clft)), memset(crig, 0, sizeof(crig));
        memset(fl, 0, sizeof(fl)), memset(fr, 0, sizeof(fr));
        lftzero = rigzero = false;
        sum[0] = sum[1] = ans = 0;
    }

    void load(int x)
    {
        clear();
        if (x)
            clft[0][1] = crig[0][1] = sum[1] = ans = fl[0] = fr[0] = 1;
        else
            clft[1][0] = crig[1][0] = sum[0] = lftzero = rigzero = 1;
    }
} nodes[MAX_N << 2];

node pushup(node ls, node rs)
{
    node ret;
    ret.clear();
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            ret.clft[i][j] += ls.clft[i][j];
            ret.crig[i][j] += rs.crig[i][j];
            if (i >= ls.sum[0])
                ret.clft[i][j] += rs.clft[i - ls.sum[0]][j ^ (ls.sum[1] & 1)];
            if (i >= rs.sum[0])
                ret.crig[i][j] += ls.crig[i - rs.sum[0]][j ^ (rs.sum[1] & 1)];
        }
    for (int i = 0; i < 3; i++)
    {
        ret.fl[i] += ls.fl[i], ret.fr[i] += rs.fr[i];
        if (ls.sum[1] == 0)
            ret.fl[min(2, i + ls.sum[0])] += rs.fl[i];
        if (rs.sum[1] == 0)
            ret.fr[min(2, i + rs.sum[0])] += ls.fr[i];
    }
    if (ls.sum[1] == 1 && rs.lftzero)
        ret.fl[min(2LL, ls.sum[0] + rs.lftzero)]++, ret.fl[2] += rs.lftzero - 1;
    if (rs.sum[1] == 1 && ls.rigzero)
        ret.fr[min(2LL, rs.sum[0] + ls.rigzero)]++, ret.fr[2] += ls.rigzero - 1;
    ret.lftzero = ls.lftzero + ((ls.sum[1] == 0) ? rs.lftzero : 0);
    ret.rigzero = rs.rigzero + ((rs.sum[1] == 0) ? ls.rigzero : 0);
    ret.sum[0] = ls.sum[0] + rs.sum[0], ret.sum[1] = ls.sum[1] + rs.sum[1];
    ret.ans = ls.ans + rs.ans;
    ret.ans += ls.crig[0][0] * (rs.clft[0][1] + rs.clft[1][1]);
    ret.ans += ls.crig[0][1] * (rs.clft[0][0] + rs.clft[1][0]);
    ret.ans += ls.crig[1][0] * rs.clft[0][1];
    ret.ans += ls.crig[1][1] * rs.clft[0][0];
    if (rs.lftzero)
        ret.ans += rs.lftzero * (ls.fr[0] + ls.fr[1] + ls.fr[2]) - ls.fr[0];
    if (ls.rigzero)
        ret.ans += ls.rigzero * (rs.fl[0] + rs.fl[1] + rs.fl[2]) - rs.fl[0];
    return ret;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p].load(str[l]));
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = pushup(nodes[lson], nodes[rson]);
}

void update(int qx, int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p].load(str[l]));
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
    bool lft = (ql <= mid), rig = (mid < qr);
    if (lft && rig)
        return pushup(query(ql, qr, l, mid, lson), query(ql, qr, mid + 1, r, rson));
    if (lft)
        return query(ql, qr, l, mid, lson);
    else
        return query(ql, qr, mid + 1, r, rson);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &str[i]);
    build(1, n, 1), scanf("%d", &q);
    while (q--)
    {
        int opt, l, r;
        scanf("%d%d", &opt, &l);
        if (opt == 1)
            str[l] ^= 1, update(l, 1, n, 1);
        else
            scanf("%d", &r), printf("%lld\n", 1LL * (r - l + 1) * (r - l + 2) / 2 - query(l, r, 1, n, 1).ans);
    }
    return 0;
}