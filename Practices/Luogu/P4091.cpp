// P4091.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 200, mod = 998244353, mod_g = 3, mod_gi = 332748118;

int n, mx_pow, mx_bit, rev[MAX_N], fac[MAX_N], fac_inv[MAX_N], gx[MAX_N];
ll poly_A[MAX_N], poly_B[MAX_N];

int quick_pow(int bas, int tim)
{
    int ans = 1;
    bas %= mod;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * bas * ans % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

void ntt_initialize()
{
    mx_pow = 2, mx_bit = 1;
    while ((n << 1) >= mx_pow)
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
        ll omega_n = quick_pow(dft == 1 ? mod_g : mod_gi, (mod - 1) / (step << 1));
        for (int j = 0; j < mx_pow; j += (step << 1))
        {
            ll omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = (omega_nk * omega_n) % mod)
            {
                ll x = arr[k], y = omega_nk * arr[k + step] % mod;
                arr[k] = (x + y) % mod;
                arr[k + step] = (x - y + mod) % mod;
            }
        }
    }
    if (dft != 1)
    {
        ll inv = quick_pow(mx_pow, mod - 2);
        for (int i = 0; i < mx_pow; i++)
            arr[i] = arr[i] * inv % mod;
    }
}

int main()
{
    scanf("%d", &n);
    // process the factors;
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n] = quick_pow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;

    // process the poly;
    for (int i = 0, flag = 1; i <= n; i++, flag ^= 1)
        if (flag == 1)
            poly_A[i] = fac_inv[i];
        else
            poly_A[i] = (mod - fac_inv[i]) % mod;

    poly_B[0] = 1, poly_B[1] = n + 1;
    for (int i = 2; i <= n; i++)
        poly_B[i] = 1LL * fac_inv[i] * quick_pow(i - 1, mod - 2) % mod * ((1LL * quick_pow(i, n + 1) - 1 + mod) % mod) % mod;
    // the calculation;
    ntt_initialize();
    ntt(poly_A, 1), ntt(poly_B, 1);
    for (int i = 0; i < mx_pow; i++)
        poly_A[i] = 1LL * poly_A[i] * poly_B[i] % mod;
    ntt(poly_A, -1);
    // final calc;
    ll ans = 0, pow_2 = 1;
    for (int i = 0; i <= n; i++)
        ans = (ans + 1LL * pow_2 * fac[i] % mod * poly_A[i] % mod) % mod, pow_2 = (pow_2 << 1) % mod;
    printf("%lld", ans);
    return 0;
}

