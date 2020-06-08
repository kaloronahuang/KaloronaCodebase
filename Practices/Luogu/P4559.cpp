// P4559.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, RANGE = 1e6;

typedef long long ll;

int n, m, ai[MAX_N], roots[MAX_N], ptot;

struct node
{
    int val, lson, rson;
    ll sum;
} nodes[MAX_N * 30];

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].val++, nodes[p].sum += qx;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    return p;
}

ll query(int l, int r, int p, int pre, int cur, int k)
{
    if (nodes[p].val - nodes[pre].val == 0)
        return 0;
    int siz = nodes[p].val - nodes[pre].val;
    ll sum = nodes[p].sum - nodes[pre].sum;
    if (k + cur <= l)
        return sum - 1LL * ((k + cur) + (k + cur + siz - 1)) * siz / 2;
    else if (r <= k + cur + siz - 1)
        return 1LL * ((k + cur) + (k + cur + siz - 1)) * siz / 2 - sum;
    int lsiz = nodes[nodes[p].lson].val - nodes[nodes[pre].lson].val;
    return query(l, mid, nodes[p].lson, nodes[pre].lson, cur, k) +
           query(mid + 1, r, nodes[p].rson, nodes[pre].rson, cur + lsiz, k);
}

#undef mid

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), roots[i] = update(ai[i], 1, RANGE, roots[i - 1]);
    while (m--)
    {
        int L, R, k;
        scanf("%d%d%d", &L, &R, &k);
        printf("%lld\n", query(1, RANGE, roots[R], roots[L - 1], 0, k));
    }
    return 0;
}