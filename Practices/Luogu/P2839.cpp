// P2839.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int n, q, ai[MAX_N], ptot, roots[MAX_N], idx[MAX_N], lans;

struct node
{
    int sum, lson, rson, lmx, rmx;
    void negset() { lmx = rmx = -INF, sum = 0; }
} nodes[MAX_N * 20];

#define mid ((l + r) >> 1)

node pushup(node ls, node rs)
{
    node ret;
    ret.sum = ret.lson = ret.rson = ret.lmx = ret.rmx = 0;
    ret.sum = ls.sum + rs.sum;
    ret.lmx = max(ls.lmx, ls.sum + rs.lmx);
    ret.rmx = max(rs.rmx, rs.sum + ls.rmx);
    return ret;
}

int build(int l, int r)
{
    int p = ++ptot;
    nodes[p].lmx = nodes[p].rmx = nodes[p].sum = r - l + 1;
    if (l == r)
        return p;
    nodes[p].lson = build(l, mid), nodes[p].rson = build(mid + 1, r);
    return p;
}

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre];
    if (l == r)
        return (nodes[p].lmx = nodes[p].rmx = nodes[p].sum = -1), p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    int ls = nodes[p].lson, rs = nodes[p].rson;
    nodes[p] = pushup(nodes[nodes[p].lson], nodes[nodes[p].rson]);
    nodes[p].lson = ls, nodes[p].rson = rs;
    return p;
}

void query(int ql, int qr, int l, int r, int p, node &ans)
{
    if (ql <= l && r <= qr)
        return (void)(ans = pushup(ans, nodes[p]));
    if (ql <= mid)
        query(ql, qr, l, mid, nodes[p].lson, ans);
    if (mid < qr)
        query(ql, qr, mid + 1, r, nodes[p].rson, ans);
}

#undef mid

bool check(int mid, int l, int a, int b, int r)
{
    int ret = 0;
    node rnd;
    rnd.negset();
    if (a + 1 <= b - 1)
        query(a + 1, b - 1, 1, n, roots[mid], rnd), ret += rnd.sum;
    rnd.negset(), query(l, a, 1, n, roots[mid], rnd), ret += rnd.rmx;
    rnd.negset(), query(b, r, 1, n, roots[mid], rnd), ret += rnd.lmx;
    return ret >= 0;
}

int main()
{
    scanf("%d", &n), roots[1] = build(1, n), nodes[0].negset();
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), idx[i] = i;
    sort(idx + 1, idx + 1 + n, [](const int &rhs1, const int &rhs2) { return ai[rhs1] < ai[rhs2]; });
    for (int i = 2; i <= n; i++)
        roots[i] = update(idx[i - 1], 1, n, roots[i - 1]);
    scanf("%d", &q);
    while (q--)
    {
        int q[4];
        for (int i = 0; i < 4; i++)
            scanf("%d", &q[i]);
        for (int i = 0; i < 4; i++)
            q[i] = (q[i] + lans) % n + 1;
        sort(q, q + 4);
        int l = 1, r = n, res = 0;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (check(mid, q[0], q[1], q[2], q[3]))
                res = ai[idx[mid]], l = mid + 1;
            else
                r = mid - 1;
        }
        printf("%d\n", lans = res);
    }
    return 0;
}