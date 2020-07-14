// BZ4408.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 1e9;

int n, q, roots[MAX_N], ptot;

struct node
{
    int lson, rson, sum;
} nodes[MAX_N * 40];

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].sum += qx;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    return p;
}

int query(int qx, int l, int r, int p, int pre)
{
    if (l == r)
        return nodes[p].sum - nodes[pre].sum;
    if (qx <= mid)
        return query(qx, l, mid, nodes[p].lson, nodes[pre].lson);
    else
        return nodes[nodes[p].lson].sum - nodes[nodes[pre].lson].sum + query(qx, mid + 1, r, nodes[p].rson, nodes[pre].rson);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &val), roots[i] = update(val, 0, INF, roots[i - 1]);
    scanf("%d", &q);
    while (q--)
    {
        int l, r, ans = 1;
        scanf("%d%d", &l, &r);
        while (true)
        {
            int ret = query(ans, 0, INF, roots[r], roots[l - 1]);
            if (ret < ans)
                break;
            ans = ret + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}