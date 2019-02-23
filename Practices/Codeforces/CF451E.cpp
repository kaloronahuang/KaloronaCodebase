// CF451E.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9 + 7, MAX_N = 25;
ll arr[MAX_N], n, inv[MAX_N], m;
ll quick_power(ll bas, ll tim)
{
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}
ll C(ll a, ll b)
{
    if (a < 0 || b < 0 || a < b)
        return 0;
    a %= mod;
    if (a == 0 || b == 0)
        return 1;
    ll ans = 1;
    for (int i = 0; i < b; i++)
        ans = ans * (a - i) % mod;
    for (int i = 1; i <= b; i++)
        ans = ans * inv[i] % mod;
    return ans;
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    inv[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        inv[i] = quick_power(i, mod - 2);
    ll ans = 0;
    for (int stat = 0; stat < (1 << n); stat++)
        if (stat == 0)
            ans = (ans + C(n + m - 1, n - 1)) % mod;
        else
        {
            ll t = n + m, p = 0;
            for (int i = 0; i < n; i++)
                if ((stat >> i) & 1)
                    p++, t -= arr[i + 1];
            t -= (p + 1);
            if (p & 1)
                ans = (ans - C(t, n - 1)) % mod;
            else
                ans = (ans + C(t, n - 1)) % mod;
        }
    ans = (ans + mod) % mod;
    printf("%lld", ans);
    return 0;
}