// P3803.cpp
// NTT version;
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int mod = 998244353, G = 3, Gi = 332748118, MAX_N = 3e6 + 2000;

int n, m, rev[MAX_N], mx_bit, mx_pow;

ll ai[MAX_N], bi[MAX_N];

ll quick_pow(ll bas, ll tim)
{
    ll ans = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

void ntt_initialize()
{
    mx_pow = 2, mx_bit = 1;
    while (n + m >= mx_pow)
        mx_pow <<= 1, mx_bit++;
    for (int i = 0; i < mx_pow; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (mx_bit - 1));
}

inline void ntt(ll *arr, int dft)
{
    for (int i = 0; i < mx_pow; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < mx_pow; step <<= 1)
    {
        ll omega_n = quick_pow(dft == 1 ? G : Gi, (mod - 1) / (step << 1));
        for (int j = 0; j < mx_pow; j += (step << 1))
        {
            ll omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = (omega_nk * omega_n) % mod)
            {
                int x = arr[k], y = omega_nk * arr[k + step] % mod;
                arr[k] = (x + y) % mod;
                arr[k + step] = (x - y + mod) % mod;
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++)
        scanf("%lld", &ai[i]), ai[i] = (ai[i] + mod) % mod;
    for (int i = 0; i <= m; i++)
        scanf("%lld", &bi[i]), bi[i] = (bi[i] + mod) % mod;
    ntt_initialize();
    ntt(ai, 1), ntt(bi, 1);
    for (int i = 0; i < mx_pow; i++)
        ai[i] = (ai[i] * bi[i] % mod);
    ntt(ai, -1);
    // 748683265
    ll inv = quick_pow(mx_pow, mod - 2);
    for (int i = 0; i <= n + m; i++)
        printf("%d ", ai[i] * inv % mod);
    return 0;
}