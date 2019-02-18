// BZ1257.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, k;
int main()
{
    scanf("%lld%lld", &n, &k);
    ll ans = n * k, gx;
    for (int x = 1; x <= n; x = gx + 1)
    {
        gx = (k / x) ? min(k / (k / x), n) : n;
        // x ~ gx same;
        ans -= (k / x) * (gx - x + 1) * (gx + x) / 2;
    }
    printf("%lld", ans);
    return 0;
}