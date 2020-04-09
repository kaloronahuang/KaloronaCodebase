// LOJ6088.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, ptot, roots[MAX_N], cframe, ans[MAX_N];

struct node
{
    int dp, lson, rson;
} nodes[MAX_N * 30];

int build(int l, int r)
{
    int p = ++ptot;
    nodes[p].dp = 0x3f3f3f3f;
    if (l == r)
    {
        if (l == 0)
            nodes[p].dp = -0x3f3f3f3f;
        return p;
    }
    int mid = (l + r) >> 1;
    nodes[p].lson = build(l, mid), nodes[p].rson = build(mid + 1, r);
    nodes[p].dp = max(nodes[nodes[p].lson].dp, nodes[nodes[p].rson].dp);
    return p;
}

int update(int qx, int l, int r, int pre, int val)
{
    int p = ++ptot;
    nodes[p] = nodes[pre];
    if (l == r)
        return (nodes[p].dp = val, p);
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson, val);
    nodes[p].dp = max(nodes[nodes[p].lson].dp, nodes[nodes[p].rson].dp);
    return p;
}

int query(int qk, int l, int r, int p)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (nodes[nodes[p].lson].dp > qk)
        return query(qk, l, mid, nodes[p].lson);
    else
        return query(qk, mid + 1, r, nodes[p].rson);
}

int main()
{
    scanf("%d", &n), roots[0] = build(0, n);
    for (int i = 1, opt, x; i <= n; i++)
    {
        scanf("%d%d", &opt, &x);
        if (opt == 0)
        {
            cframe++, roots[cframe] = roots[cframe - 1];
            int verdict = query(x, 0, n, roots[cframe]);
            if (verdict)
                roots[cframe] = update(verdict, 0, n, roots[cframe - 1], x);
            printf("%d\n", ans[cframe] = max(ans[cframe - 1], verdict));
        }
        else
            printf("%d\n", ans[cframe = x]);
    }
    return 0;
}