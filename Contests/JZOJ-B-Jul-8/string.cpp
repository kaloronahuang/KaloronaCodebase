// string.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 2000, mod = 1e9 + 7;

ll n, k, level[MAX_N], level_inv[MAX_N], ans;
char S[MAX_N], T[MAX_N];

ll quick_pow(ll bas, ll tim)
{
    if (tim < 0)
        return 0;
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

ll comb(ll n_, ll k_) { return level[n_] * level_inv[n_ - k_] % mod * level_inv[k_] % mod; }

int main()
{
    scanf("%lld%lld", &n, &k), level[0] = 1;
    for (int i = 1; i <= n; i++)
        level[i] = level[i - 1] * i % mod;
    level_inv[n] = quick_pow(level[n], mod - 2);
    for (int i = n - 1; i >= 1; i--)
        level_inv[i] = level_inv[i + 1] * (i + 1) % mod;
    level_inv[0] = 1;
    scanf("%s", S + 1), scanf("%s", T + 1);

    for (int i = 1; i <= n; i++)
    {
        for (int ch = 0; ch < T[i] - 'a'; ch++)
        {
            if (ch + 'a' == S[i])
                (ans += comb(n - i, k) * quick_pow(25, k) % mod) %= mod;
            else
                (ans += comb(n - i, k - 1) * quick_pow(25, k - 1) % mod) %= mod;
        }
        if (S[i] != T[i])
            k--;
    }
    printf("%lld", (ans + 1) % mod);
    return 0;
}