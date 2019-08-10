// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

void solve(ll a, ll b, ll c, ll d, ll &x, ll &y)
{
    ll dot = a * c + b * d;
    if (dot < 0)
    {
        solve(a, b, -c, -d, x, y);
        y = -y;
        return;
    }
    ll lenA = a * a + b * b, lenB = c * c + d * d;
    if (lenA > lenB)
        return solve(c, d, a, b, y, x);
    if (((dot * dot) << 2) <= lenA * lenB)
    {
        x = 1, y = 0;
        return;
    }

    ll k = dot / lenA;

    if (dot + dot <= lenA * (k + k + 1))
    {
        solve(a, b, c - k * a, d - k * b, x, y);
        x -= k * y;
    }
    else
    {
        solve(a, b, c - (k + 1) * a, d - (k + 1) * b, x, y);
        x -= (k + 1) * y;
    }
}

ll pow2(ll bas) { return bas * bas; }

int main()
{
    int x1, y1, x2, y2;
    ll ans1, ans2;
    while (scanf("%d%d%d%d", &x1, &y1, &x2, &y2) != EOF)
        solve(x1, y1, x2, y2, ans1, ans2), printf("%lld\n", pow2(ans1 * x1 + ans2 * x2) + pow2(ans1 * y1 + ans2 * y2));
    return 0;
}