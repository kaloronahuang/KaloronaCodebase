// CF559C.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, ll>
using namespace std;
const int MOD = 1e9 + 7, MAX_N = 2020, LEVEL_RG = 200000;
ll level[200010], inv[200010], n, h, w, F[MAX_N];
pr pts[MAX_N];
ll quick_power(ll bas, ll tim, ll mod)
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
ll C(ll n, ll m) { return level[n] * inv[n - m] % MOD * inv[m] % MOD; }
int main()
{
    scanf("%d%d%d", &h, &w, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].first, &pts[i].second);
    sort(pts + 1, pts + 1 + n);
    pts[n + 1].first = h, pts[n + 1].second = w;
    level[0] = inv[0] = 1;
    for (int i = 1; i <= LEVEL_RG; i++)
        level[i] = level[i - 1] * i % MOD;
    ll inv_bas = quick_power(level[LEVEL_RG], MOD - 2, MOD);
    for (int i = LEVEL_RG; i >= 1; i--)
        inv[i] = inv_bas, inv_bas = inv_bas * i % MOD;
    for (int i = 1; i <= n + 1; i++)
    {
        F[i] = C(pts[i].first + pts[i].second - 2, pts[i].first - 1) % MOD;
        for (int j = 1; j < i; j++)
            if (pts[j].first <= pts[i].first && pts[j].second <= pts[i].second)
                F[i] = (F[i] - F[j] * C(pts[i].first + pts[i].second - pts[j].first - pts[j].second, pts[i].first - pts[j].first)) % MOD;
    }
    printf("%lld", (F[n + 1] + MOD) % MOD);
    return 0;
}