// U63113.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 5050, mod = 998244353;
ll f[MAX_N], prefix[MAX_N], level[MAX_N], inv[MAX_N], n, m;
ll quick_pow(ll bas, ll tim)
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
int main()
{
    scanf("%lld%lld", &n, &m);
    level[0] = 1, inv[0] = 1;
    for (int i = 1; i <= n; i++)
        level[i] = level[i - 1] * i % mod;
    inv[n] = quick_pow(level[n], mod - 2);
    for (int i = n; i >= 1; i--)
        inv[i - 1] = inv[i] * i % mod;
    for (int i = 0; i <= n; i++)
        prefix[i] = 1;
    for (int j = 1; j <= m; j++)
    {
        for (int i = j; i <= n; i++)
            f[i] = prefix[i - 1] * level[i - 1] % mod;
        for (int i = j; i <= n; i++)
            prefix[i] = f[i] * inv[i] % mod;
        for (int i = j + 1; i <= n; i++)
            prefix[i] = (prefix[i] + prefix[i - 1]) % mod;
    }
    printf("%lld", f[n]);
    return 0;
}