// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 200, mod = 998244353;

int fac[MAX_N], fac_inv[MAX_N], T;
ll n, A, B, x;

int quick_pow(int bas, int tim)
{
    int ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int combinator(int n_, int k_)
{
    if (n_ < k_ || n_ < 0 || k_ < 0)
        return 0;
    return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod;
}

int main()
{
    scanf("%d", &T);
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_N - 1] = quick_pow(fac[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 2; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    while (T--)
    {
        scanf("%lld%lld%lld%lld", &n, &A, &B, &x);
        ll res = 0, ans = 0;
        for (int i = 0; i <= n; i++)
        {
            ll tmp = x - 1LL * i * A;
            if (tmp > 0 && (tmp % B == 0))
                ans = (1LL * ans + 1LL * combinator(n, i) * combinator(n, tmp / B) % mod) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}