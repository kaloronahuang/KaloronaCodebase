// BZ1568.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)
using namespace std;
const int MAX_Q = 100020, MAX_N = 50010, ENDPOINT = 50000;
int n, tmpx;
char opt[10];
double lnk[MAX_N << 2], lnb[MAX_N << 2], tmpw, tmpz;
bool tag[MAX_N << 2];
double intersect(double k1, double b1, double k2, double b2) { return 1.0 * (b2 - b1) / (k1 - k2); }
void update(double k, double b, int l, int r, int p)
{
    if (tag[p])
    {
        double ff = k * l + b, gf = lnk[p] * l + lnb[p], fb = k * r + b, gb = lnk[p] * r + lnb[p];
        if (ff <= gf && fb <= gb)
            return;
        else if (ff >= gf && fb >= gb)
        {
            lnk[p] = k, lnb[p] = b;
            return;
        }
        double intx = intersect(k, b, lnk[p], lnb[p]);
        if (ff >= gf)
            if (intx <= mid)
                update(k, b, l, mid, lson);
            else
                update(lnk[p], lnb[p], mid + 1, r, rson), lnk[p] = k, lnb[p] = b;
        else if (intx > mid)
            update(k, b, mid + 1, r, rson);
        else
            update(lnk[p], lnb[p], l, mid, lson), lnk[p] = k, lnb[p] = b;
    }
    else
        lnk[p] = k, lnb[p] = b, tag[p] = true;
}
double query(int qx, int l, int r, int p)
{
    double ans = 0;
    if (tag[p])
        ans = max(ans, 1.0 * qx * lnk[p] + lnb[p]);
    if (l == r)
        return ans;
    if (qx <= mid)
        ans = max(ans, query(qx, l, mid, lson));
    else
        ans = max(ans, query(qx, mid + 1, r, rson));
    return ans;
}
int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", opt + 1);
        if (opt[1] == 'Q')
            scanf("%d", &tmpx), printf("%d\n", (int)(query(tmpx, 1, ENDPOINT, 1) / 100.0));
        else
            scanf("%lf%lf", &tmpw, &tmpz), update(tmpz, tmpw - tmpz, 1, ENDPOINT, 1);
    }
    return 0;
}