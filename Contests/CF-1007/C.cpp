// C.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int query(ll x, ll y)
{
    int ret;
    printf("%lld %lld\n", x, y), fflush(stdout);
    return scanf("%d", &ret), ret;
}

int main()
{
    ll n;
    scanf("%lld", &n);
    ll ya = n, yb = n, yc = 1, xa = n, xb = n, xc = 1;
    while (true)
    {
        if (yc > yb)
            yb = ya, xa = xb;
        if (xc > xb)
            xb = xa, ya = yb;
        ll midy = (yc + yb) >> 1, midx = (xc + xb) >> 1;
        if ((long double)(ya - yb) * (xb - xc) > (long double)(yb - yc) * (xa - xc))
            midy = yb;
        else if ((long double)(ya - yc) * (xb - xc) > (long double)(yb - yc) * (xa - xb))
            midx = xb;
        int verdict = query(midx, midy);
        if (verdict == 0)
            break;
        else if (verdict == 1)
            xc = midx + 1;
        else if (verdict == 2)
            yc = midy + 1;
        else
            xb = midx - 1, yb = midy - 1;
        if (yc > yb)
            yb = ya, xa = xb;
        if (xc > xb)
            xb = xa, ya = yb;
        if (ya == yb && yb == yc)
        {
            xb = xc;
            while (xa > xb)
            {
                ll mid = (xa + xb) >> 1;
                verdict = query(mid, ya);
                if (verdict == 0)
                    return 0;
                else if (verdict == 1)
                    xb = mid + 1;
                else
                    xa = mid - 1;
            }
        }
        else if (xa == xb && xb == xc)
        {
            yb = yc;
            while (ya > yb)
            {
                ll mid = (ya + yb) >> 1;
                verdict = query(xa, mid);
                if (verdict == 0)
                    return 0;
                else if (verdict == 2)
                    yb = mid + 1;
                else
                    ya = mid - 1;
            }
        }
    }
    return 0;
}