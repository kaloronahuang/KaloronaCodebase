// P4238.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 2000, mod = 998244353, G = 3, Gi = 332748118;

int n, rev[MAX_N], mx_pow, mx_bit;
ll ai[MAX_N], ans[MAX_N], tmp[MAX_N];

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
            for (int k = j; k < j + step; k++, omega_nk = (omega_n * omega_nk) % mod)
            {
                ll x = arr[k], y = omega_nk * arr[k + step] % mod;
                arr[k] = (x + y) % mod;
                arr[k + step] = (x - y + mod) % mod;
            }
        }
    }
    if (dft == -1)
    {
        ll inv = quick_pow(mx_pow, mod - 2);
        for (int i = 0; i < mx_pow; i++)
            arr[i] = (arr[i] * inv % mod);
    }
}

void solve(int deg, ll *a, ll *b)
{
    if (deg == 1)
        return (void)(b[0] = quick_pow(a[0], mod - 2));
    solve((deg + 1) >> 1, a, b);
    // NTT initialize;
    mx_pow = 2, mx_bit = 1;
    while ((deg << 1) > mx_pow)
        mx_pow <<= 1, mx_bit++;
    for (int i = 0; i < mx_pow; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (mx_bit - 1));

    for (int i = 0; i < deg; i++)
        tmp[i] = a[i];
    for (int i = deg; i < mx_pow; i++)
        tmp[i] = 0;
    ntt(tmp, 1), ntt(b, 1);
    for (int i = 0; i < mx_pow; i++)
        b[i] = 1LL * (2 - tmp[i] * b[i] % mod + mod) % mod * b[i] % mod;
    ntt(b, -1);
    for (int i = deg; i < mx_pow; i++)
        b[i] = 0;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i <= n - 1; i++)
        scanf("%lld", &ai[i]);
    solve(n, ai, ans);
    for (int i = 0; i < n; i++)
        printf("%lld ", ans[i]);
    return 0;
}