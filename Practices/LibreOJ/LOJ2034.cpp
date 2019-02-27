// LOJ2034.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1000100, mod = 1e9 + 7;
ll level[MAX_N], inv[MAX_N], D[MAX_N];
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
ll C(ll n, ll m) { return level[n] * inv[m] % mod * inv[n - m] % mod; }
int main()
{
    level[0] = inv[0] = 1, D[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        level[i] = level[i - 1] * i % mod, D[i] = (i * D[i - 1] + ((i & 1 == 1) ? -1 : 1)) % mod;
    inv[MAX_N - 1] = quick_pow(level[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 1; i >= 2; i--)
        inv[i - 1] = inv[i] * i % mod;
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ll n, m;
        scanf("%lld%lld", &n, &m), printf("%lld\n", C(n, m) * D[n - m] % mod);
    }
    return 0;
}