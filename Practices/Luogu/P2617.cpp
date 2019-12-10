// P2617.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

struct query
{
    int typ, l, r, k, id;
} queries[MAX_N], q1[MAX_N], q2[MAX_N];

int seq[MAX_N], nodes[MAX_N], n, m, ans[MAX_N], qcnt;
char opt[20];

int lowbit(int x) { return x & (-x); }

void update(int qx, int d)
{
    for (; qx <= n; qx += lowbit(qx))
        nodes[qx] += d;
}

int querySum(int qx, int ret = 0)
{
    for (; qx != 0; qx -= lowbit(qx))
        ret += nodes[qx];
    return ret;
}

void solve(int l, int r, int ql, int qr)
{
    if (ql > qr)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; i++)
            if (queries[i].typ == 2)
                ans[queries[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1, lcnt = 0, rcnt = 0;
    for (int i = ql; i <= qr; i++)
        if (queries[i].typ == 1)
            if (queries[i].k <= mid)
                update(queries[i].l, queries[i].r), q1[++lcnt] = queries[i];
            else
                q2[++rcnt] = queries[i];
        else
        {
            int ref = querySum(queries[i].r) - querySum(queries[i].l - 1);
            if (queries[i].k <= ref)
                q1[++lcnt] = queries[i];
            else
                q2[++rcnt] = queries[i], q2[rcnt].k -= ref;
        }
    for (int i = 1; i <= lcnt; i++)
        if (q1[i].typ == 1)
            update(q1[i].l, -q1[i].r);
    for (int i = 1; i <= lcnt; i++)
        queries[ql + i - 1] = q1[i];
    for (int i = 1; i <= rcnt; i++)
        queries[ql + lcnt + i - 1] = q2[i];
    solve(l, mid, ql, ql + lcnt - 1), solve(mid + 1, r, ql + lcnt, qr);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &seq[i]);
        queries[++qcnt] = query{1, i, 1, seq[i], 0};
    }
    for (int i = 1; i <= m; i++)
    {
        int x, y, k;
        scanf("%s%d", opt + 1, &x);
        if (opt[1] == 'C')
        {
            scanf("%d", &y);
            queries[++qcnt] = query{1, x, -1, seq[x], 0};
            seq[x] = y;
            queries[++qcnt] = query{1, x, 1, seq[x], 0};
        }
        else
            scanf("%d%d", &y, &k), queries[++qcnt] = query{2, x, y, k, i};
    }
    memset(ans, -1, sizeof(ans));
    solve(0, 1e9, 1, qcnt);
    for (int i = 1; i <= m; i++)
        if (ans[i] != -1)
            printf("%d\n", ans[i]);
    return 0;
}