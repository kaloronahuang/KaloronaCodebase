// A.cpp
// More comments on this problem at https://kaloronahuang.com
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int mod = 998244353, MAX_N = 1e7 + 10;

ll n, m, k, inv[MAX_N];
int fac[MAX_N], fac_inv[MAX_N];

ll comb(ll n_, ll k_)
{
    if (n_ < k_)
        return 0;
    if (n_ < MAX_N && k_ < MAX_N)
        return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod;
    ll ans = 1;
    for (ll i = 1; i <= k_; i++)
        ans = 1LL * ans * inv[i] % mod * ((n_ - k_ + i) % mod) % mod;
    return ans;
}

int main()
{
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    inv[1] = 1;
    for (ll i = 2; i < MAX_N; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    fac[0] = fac_inv[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod, fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
    ll ans = 0;
    for (ll A = n % m; A <= 1LL * k * (m - 1); A += m)
    {
        ll opt = 1, res = 0;
        for (ll i = 0; i <= k && 1LL * i * (m - 1) <= A; i++)
        {
            res = (res + opt * comb(A - i * (m - 1) - 1, k - 1) % mod * comb(k, i) % mod + mod) % mod;
            opt = -opt;
        }
        ans = (ans + res * comb(k + (n - A) / m - 1, k - 1) % mod + mod) % mod;
    }
    printf("%lld", ans);
    return 0;
}