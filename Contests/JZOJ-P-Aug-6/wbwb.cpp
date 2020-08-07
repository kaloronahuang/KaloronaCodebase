// wbwb.cpp
#include <bits/stdc++.h>

using namespace std;

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}

const int MAX_N = 3e7 + 200, mod = 998244353;

int T, n, m, sA, sB, otot, fac[MAX_N], fac_inv[MAX_N];

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

int binomial(int n_, int k_) { return k_ > n_ ? 0 : 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int main()
{
    /*
    inv[0] = inv[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    */
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_N - 1] = fpow(fac[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 2; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    /*
    freopen("wbwb.in", "r", stdin);
    freopen("wbwb.out", "w", stdout);
    */
    // fileIO("wbwb");
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &n, &m, &sA, &sB);
        int ans = 1LL * binomial(n * (m + 1) + sA + sB, n) * fpow(n * (m + 1) + sA + sB, mod - 2) % mod * (0LL + sA + sB) % mod;
        printf("%d\n", ans);
    }
    return 0;
}