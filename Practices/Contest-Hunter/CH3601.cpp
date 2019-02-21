// CH3601.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1020, mod = 10007;
ll level[MAX_N], inv[MAX_N];
ll quick_power(ll bas, ll tim)
{
    bas %= mod;
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
ll C(ll a, ll b) { return level[a] * inv[b] % mod * inv[a - b] % mod; }
int main()
{
    level[0] = 1, inv[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        level[i] = level[i - 1] * i % mod;
    inv[MAX_N - 1] = quick_power(level[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 1; i >= 2; i--)
        inv[i - 1] = inv[i] * i % mod;
    ll a, b, k, n, m;
    scanf("%lld%lld%lld%lld%lld", &a, &b, &k, &n, &m);
    ll ans = quick_power(a, n) * quick_power(b, m) % mod;
    ans = C(k, n) * ans % mod;
    printf("%lld", ans);
    return 0;
}