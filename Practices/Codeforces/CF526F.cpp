// CF526F.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 3e5 + 200;

int n, pi[MAX_N], nodes[MAX_N << 2][2], tags[MAX_N << 2], stmax[MAX_N], stmin[MAX_N], t1, t2;
ll ans;

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    nodes[p][1] = r - l + 1;
    if (l == r)
        return;
    build(l, mid, lson), build(mid + 1, r, rson);
}

void modify(int p, int x) { nodes[p][0] += x, tags[p] += x; }

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(modify(p, val));
    if (tags[p])
        modify(lson, tags[p]), modify(rson, tags[p]), tags[p] = 0;
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    nodes[p][0] = min(nodes[lson][0], nodes[rson][0]);
    nodes[p][1] = (nodes[lson][0] == nodes[p][0] ? nodes[lson][1] : 0) + (nodes[rson][0] == nodes[p][0] ? nodes[rson][1] : 0);
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d", &n);
    for (int i = 1, x, y; i <= n; i++)
        scanf("%d%d", &x, &y), pi[x] = y;
    build(1, n, 1);
    for (int i = 1; i <= n; i++)
    {
        while (t1 > 0 && pi[stmax[t1]] < pi[i])
            update(stmax[t1 - 1] + 1, stmax[t1], 1, n, 1, -pi[stmax[t1]]), t1--;
        while (t2 > 0 && pi[stmin[t2]] > pi[i])
            update(stmin[t2 - 1] + 1, stmin[t2], 1, n, 1, pi[stmin[t2]]), t2--;
        update(1, i, 1, n, 1, -1), stmax[++t1] = stmin[++t2] = i;
        update(stmax[t1 - 1] + 1, stmax[t1], 1, n, 1, pi[i]);
        update(stmin[t2 - 1] + 1, stmin[t2], 1, n, 1, -pi[i]);
        ans += nodes[1][1];
    }
    printf("%lld\n", ans);
    return 0;
}