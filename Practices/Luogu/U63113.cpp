// U63113.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 5050, mod = 998244353;
ll f[MAX_N][MAX_N], prefix[MAX_N], level[MAX_N], inv[MAX_N], n, m;
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
        inv[i - 1] = inv[i] * i;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            f[i][j] = (prefix[j - 1] ? prefix[j - 1] : 1) * level[i - 1] * mod;
            prefix[j] = (prefix[j] + f[i][j] * inv[i] % mod) % mod;
        }
    }
    printf("%lld", f[n][m]);
    return 0;
}