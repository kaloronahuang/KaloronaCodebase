// BZ4571.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, roots[MAX_N], ptot;

struct node
{
    int lson, rson, sum;
} nodes[MAX_N * 30];

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].sum++;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    return p;
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql > qr || p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    int ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &val), roots[i] = update(val, 0, 1e5, roots[i - 1]);
    while (m--)
    {
        int b, x, l, r, ans = 0;
        scanf("%d%d%d%d", &b, &x, &l, &r);
        for (int i = 20; i >= 0; i--)
            if (b & (1 << i))
            {
                int resR = query(max(0, ans - x), max(0, ans + (1 << i) - x - 1), 0, 1e5, roots[r]);
                int resL = query(max(0, ans - x), max(0, ans + (1 << i) - x - 1), 0, 1e5, roots[l - 1]);
                if (resR - resL == 0)
                    ans ^= (1 << i);
            }
            else
            {
                int resR = query(max(0, ans + (1 << i) - x), max(0, ans + (1 << (i + 1)) - x - 1), 0, 1e5, roots[r]);
                int resL = query(max(0, ans + (1 << i) - x), max(0, ans + (1 << (i + 1)) - x - 1), 0, 1e5, roots[l - 1]);
                if (resR - resL > 0)
                    ans ^= (1 << i);
            }
        printf("%d\n", ans ^ b);
    }
    return 0;
}