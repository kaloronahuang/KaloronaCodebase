// LOJ6025.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

typedef long long ll;

int n, m, current_dimension;
ll A, B, C;

struct point
{
    int d[2], max_val[2], min_val[2], val, lson, rson;
    ll sum;
    int &operator[](const int &rhs) { return d[rhs]; }
    bool operator<(const point &rhs) const { return d[current_dimension] < rhs.d[current_dimension]; }
} nodes[MAX_N], org[MAX_N];

int check(int x, int y) { return 1LL * A * x + 1LL * B * y < C; }

int check(const point &p) { return check(p.min_val[0], p.min_val[1]) + check(p.max_val[0], p.max_val[1]) + check(p.max_val[0], p.min_val[1]) + check(p.min_val[0], p.max_val[1]); }

void pushup(int p)
{
    int lson = nodes[p].lson, rson = nodes[p].rson;
    for (int i = 0; i < 2; i++)
    {
        nodes[p].max_val[i] = nodes[p].min_val[i] = nodes[p][i];
        if (lson)
        {
            nodes[p].max_val[i] = max(nodes[p].max_val[i], nodes[lson].max_val[i]);
            nodes[p].min_val[i] = min(nodes[p].min_val[i], nodes[lson].min_val[i]);
        }
        if (rson)
        {
            nodes[p].max_val[i] = max(nodes[p].max_val[i], nodes[rson].max_val[i]);
            nodes[p].min_val[i] = min(nodes[p].min_val[i], nodes[rson].min_val[i]);
        }
    }
    nodes[p].sum = nodes[p].val + nodes[lson].sum + nodes[rson].sum;
}

int build(int l, int r, int dep)
{
    current_dimension = dep & 1;
    int mid = (l + r) >> 1;
    nth_element(org + l, org + mid, org + r + 1);
    nodes[mid] = org[mid];
    if (l < mid)
        nodes[mid].lson = build(l, mid - 1, dep + 1);
    if (mid < r)
        nodes[mid].rson = build(mid + 1, r, dep + 1);
    return (pushup(mid), mid);
}

ll query(int p)
{
    int lson = nodes[p].lson, rson = nodes[p].rson;
    ll ret = 0;
    int verdict = check(nodes[p][0], nodes[p][1]);
    if (verdict == 4)
        ret += nodes[p].val;
    else if (verdict == 0)
        return 0;
    if (lson && check(nodes[lson]))
        ret += nodes[lson].sum;
    else if (lson)
        ret += query(lson);
    if (rson && check(nodes[rson]))
        ret += nodes[rson].sum;
    else if (rson)
        ret += query(rson);
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &org[i].d[0], &org[i].d[1], &org[i].val);
    int groot = build(1, n, 1);
    while (m--)
        scanf("%lld%lld%lld", &A, &B, &C), printf("%lld\n", query(groot));
    return 0;
}