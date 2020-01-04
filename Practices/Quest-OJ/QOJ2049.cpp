// QOJ2049.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 2e9;
typedef long long ll;

int ai[MAX_N], bi[MAX_N], n, q;
ll ans;

struct node
{
    int lson, rson, sum;
    ll cnt;
} nodes[MAX_N * 90];

int roots_a[MAX_N], roots_b[MAX_N], ptot;

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].sum++;
    nodes[p].cnt += qx;
    if (l == r)
        return p;
    int mid = (0LL + l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    return p;
}

int query(int l, int r, int p, int pre, int k)
{
    if (l == r)
        return l;
    int mid = (0LL + l + r) >> 1;
    int ret = 0, lval = nodes[nodes[p].lson].sum - nodes[nodes[pre].lson].sum;
    if (lval >= k)
    {
        ans += nodes[nodes[p].rson].cnt - nodes[nodes[pre].rson].cnt;
        ret = query(l, mid, nodes[p].lson, nodes[pre].lson, k);
        ans -= 1LL * ret * (nodes[nodes[p].rson].sum - nodes[nodes[pre].rson].sum);
    }
    else
    {
        ans -= nodes[nodes[p].lson].cnt - nodes[nodes[pre].lson].cnt;
        ret = query(mid + 1, r, nodes[p].rson, nodes[pre].rson, k - lval);
        ans += 1LL * ret * (nodes[nodes[p].lson].sum - nodes[nodes[pre].lson].sum);
    }
    return ret;
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]);
    for (int i = 1; i <= n; i++)
        roots_a[i] = update(ai[i] + bi[i], -INF, INF, roots_a[i - 1]),
        roots_b[i] = update(ai[i] - bi[i], -INF, INF, roots_b[i - 1]);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        ans = 0;
        query(-INF, INF, roots_a[r], roots_a[l - 1], ((r - l) >> 1) + 1);
        query(-INF, INF, roots_b[r], roots_b[l - 1], ((r - l) >> 1) + 1);
        printf("%.2lf\n", double(ans) / 2.0);
    }
    return 0;
}