// ARC096C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030;

int n, mod, binomial[MAX_N][MAX_N], stiring[MAX_N][MAX_N];

int fpow(int bas, int tim, int cmod)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % cmod;
        bas = 1LL * bas * bas % cmod;
        tim >>= 1;
    }
    return ret;
}

int main()
{
    scanf("%d%d", &n, &mod);
    binomial[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        binomial[i][0] = binomial[i][i] = 1;
        for (int j = 1; j < i; j++)
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
    }
    stiring[0][0] = 1;
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= i; j++)
            stiring[i][j] = (0LL + 1LL * j * stiring[i - 1][j] % mod + stiring[i - 1][j - 1]) % mod;
    int ans = 0;
    for (int i = 0, opt = 1; i <= n; i++, opt = mod - opt)
    {
        int pans = 0;
        for (int j = 0; j <= i; j++)
            pans = (0LL + pans + 1LL * fpow(fpow(2, n - i, mod), j, mod) * stiring[i + 1][j + 1] % mod) % mod;
        pans = 1LL * pans * fpow(2, fpow(2, n - i, mod - 1), mod) % mod * binomial[n][i] % mod;
        ans = (0LL + ans + 1LL * opt * pans % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}