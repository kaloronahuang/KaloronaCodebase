// AGC001E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e3 + 200, DOM = 2500, mod = 1e9 + 7;

int mp[MAX_N][MAX_N], n, xi[MAX_N * 100], yi[MAX_N * 100], fac[MAX_N * MAX_N];

int quick_pow(int bas, int tim)
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

int main()
{
    scanf("%d", &n);
    for (int i = fac[0] = 1; i < MAX_N * MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &xi[i], &yi[i]);
        mp[DOM - xi[i]][DOM - yi[i]]++;
    }
    for (int i = 1; i <= (DOM << 1); i++)
        for (int j = 1; j <= (DOM << 1); j++)
            mp[i][j] = (1LL * mp[i][j] + mp[i - 1][j] + mp[i][j - 1]) % mod;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int pans = mp[xi[i] + DOM][yi[i] + DOM];
        // get oneself outta here;
        int myself = 1LL * fac[(xi[i] << 1) + (yi[i] << 1)] * quick_pow(fac[xi[i] << 1], mod - 2) % mod * quick_pow(fac[yi[i] << 1], mod - 2) % mod;
        ans = (1LL * ans + (pans + mod - myself) % mod) % mod;
    }
    printf("%lld\n", 1LL * ans * quick_pow(2, mod - 2) % mod);
    return 0;
}