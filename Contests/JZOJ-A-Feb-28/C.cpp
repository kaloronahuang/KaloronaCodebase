// C.cpp
#include <bits/stdc++.h>
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)
using namespace std;
const int MAX_N = 30200;
int treeSum[MAX_N << 2], treeX[MAX_N << 2], m, treeY[MAX_N << 2], xi[MAX_N], yi[MAX_N], x_1, x_2, y_1, y_2, T, n;
bool in(int x, int y)
{
    return (x <= x_2 && x >= x_1 && y >= y_1 && y <= y_2);
}
void build(int l, int r, int p)
{
    if (l == r)
    {
        treeX[p] = xi[l], treeY[p] = yi[l];
        if (in(xi[l], yi[r]))
            treeSum[p] = 1;
        else
            treeSum[p] = 0;
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    treeSum[p] = treeSum[lson] + treeSum[rson];
}
void update(int ql, int qr, int l, int r, int p, int c, int d)
{
    if (l == r)
    {
        if (c == 1)
            treeX[p] += d;
        else
            treeY[p] += d;
        if (in(treeX[p], treeY[p]))
            treeSum[p] = 1;
        else
            treeSum[p] = 0;
        return;
    }
    if (ql <= mid)
        update(ql, qr, l, mid, lson, c, d);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, c, d);
    treeSum[p] = treeSum[lson] + treeSum[rson];
}
int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return treeSum[p];
    int ans = 0;
    if (ql <= mid)
        ans += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ans += query(ql, qr, mid + 1, r, rson);
    return ans;
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d%d", &n, &x_1, &y_1, &x_2, &y_2);
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &xi[i], &yi[i]);
        build(1, n, 1);
        scanf("%d", &m);
        while (m--)
        {
            int c, l, r, d;
            scanf("%d%d%d", &c, &l, &r);
            if (c == 3)
                printf("%d\n", query(l, r, 1, n, 1));
            else
                scanf("%d", &d), update(l, r, 1, n, 1, c, d);
        }
    }
    return 0;
}