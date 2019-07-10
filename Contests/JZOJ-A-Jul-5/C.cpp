// C.cpp
#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int mod = 1004535809, G = 3, MAX_N = 1 << 18;

int n, rev[MAX_N], Gi;
ll tmp[MAX_N], level[MAX_N], level_inv[MAX_N], gx[MAX_N], CX[MAX_N], GX[MAX_N], invG[MAX_N];

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

inline void ntt(ll *arr, int limit, int dft)
{
    for (int i = 0; i < limit; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < limit; step <<= 1)
    {
        ll omega_n = quick_pow(dft == 1 ? G : Gi, (mod - 1) / (step << 1));
        for (int j = 0; j < limit; j += (step << 1))
        {
            ll omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = (omega_nk * omega_n % mod))
            {
                ll x = arr[k], y = omega_nk * arr[k + step] % mod;
                arr[k] = (x + y) % mod, arr[k + step] = (x - y + mod) % mod;
            }
        }
    }
    if (dft != 1)
    {
        ll inv = quick_pow(limit, mod - 2);
        for (int i = 0; i < limit; i++)
            arr[i] = (arr[i] * inv % mod);
    }
}

void poly_inverse(int deg, ll *a, ll *b)
{
    if (deg == 1)
        return (void)(b[0] = quick_pow(a[0], mod - 2));
    poly_inverse((deg + 1) >> 1, a, b);

    ll limit = 2, mx_bit = 1;
    while ((deg << 1) > limit)
        limit <<= 1, mx_bit++;
    for (int i = 1; i < limit; i++)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (mx_bit - 1)));

    for (int i = 0; i < deg; i++)
        tmp[i] = a[i];
    for (int i = deg; i < limit; i++)
        tmp[i] = 0;
    ntt(tmp, limit, 1), ntt(b, limit, 1);

    for (int i = 0; i < limit; i++)
        b[i] = 1LL * ((2LL - tmp[i] * b[i] % mod + mod) % mod) * b[i] % mod;

    ntt(b, limit, -1);
    for (int i = deg; i < limit; i++)
        b[i] = 0;
}

int main()
{
    Gi = quick_pow(G, mod - 2);
    scanf("%d", &n);

    level[1] = level[0] = 1, level_inv[0] = 1;
    for (int i = 2; i <= n; i++)
        level[i] = 1LL * level[i - 1] * i % mod;
    level_inv[n] = quick_pow(level[n], mod - 2);
    for (int i = n - 1; i >= 1; i--)
        level_inv[i] = 1LL * level_inv[i + 1] * (i + 1) % mod;

    gx[1] = gx[0] = 1;
    for (int i = 2; i <= n; i++)
        gx[i] = quick_pow(2, ((1LL * i * (i - 1)) >> 1) % (mod - 1));

    for (int i = 0; i <= n; i++)
        GX[i] = 1LL * gx[i] * level_inv[i] % mod;
    for (int i = 1; i <= n; i++)
        CX[i] = 1LL * gx[i] * level_inv[i - 1] % mod;

    poly_inverse(n + 1, GX, invG);

    ll limit = 2, mx_bit = 1;
    while (((n + 1) << 1) > limit)
        limit <<= 1, mx_bit++;
    for (int i = 1; i < limit; i++)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (mx_bit - 1)));

    ntt(invG, limit, 1), ntt(CX, limit, 1);
    for (int i = 0; i < limit; i++)
        invG[i] = (invG[i] * CX[i]) % mod;
    ntt(invG, limit, -1);
    ll ans = invG[n] * quick_pow(level_inv[n - 1], mod - 2) % mod;
    while (ans < 0)
        ans += mod;
    ans %= mod;
    printf("%lld", ans);
    return 0;
}