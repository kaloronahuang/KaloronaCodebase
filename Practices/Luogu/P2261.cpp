// P2261.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, k;
int main()
{
    scanf("%lld%lld", &n, &k);
    ll ans = n * k;
    for (ll x = 1, gx = 0; x <= n; x = gx + 1)
    {
        if ((k / x) != 0)
            gx = min((k / (k / x)), n);
        else
            gx = n;
        ans -= (k / x) * (gx - x + 1) * (gx + x) / 2;
    }
    printf("%lld", ans);
    return 0;
}