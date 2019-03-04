// C.cpp
#include <bits/stdc++.h>
#define ls nodes[p].lson
#define rs nodes[p].rson
using namespace std;
const int MAX_N = 1e5 + 2000;
int tot, n, m, tmpx, tmpy;
struct node
{
    int l, r, mid, lson, rson;
} nodes[MAX_N << 2];
int init(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p].l = l, nodes[p].r = r, nodes[p].lson = nodes[p].rson = 0;
        return p;
    }
    scanf("%d", &nodes[p].mid);
    nodes[p].l = l, nodes[p].r = r;
    nodes[p].lson = init(l, nodes[p].mid, ++tot), nodes[p].rson = init(nodes[p].mid + 1, r, ++tot);
    return p;
}
long long query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return 1;
    long long ans = 0, mid = nodes[p].mid;
    if (ql <= mid)
        ans += query(ql, qr, nodes[ls].l, nodes[ls].r, ls);
    if (mid < qr)
        ans += query(ql, qr, nodes[rs].l, nodes[rs].r, rs);
    return ans;
}
int main()
{
    tot++;
    scanf("%d%d", &n, &m);
    init(1, n, 1);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &tmpx, &tmpy), printf("%lld\n", query(tmpx, tmpy, 1, n, 1));
    return 0;
}