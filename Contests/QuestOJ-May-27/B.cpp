// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 1004535809;

int T, n, m, c, S[MAX_N][MAX_N];

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

int degradePower(int n_, int k_)
{
    int ret = 1;
    for (int i = n_ - k_ + 1; i <= n_; i++)
        ret = 1LL * ret * ((0LL + i + mod) % mod) % mod;
    return ret;
}

int main()
{
    for (int i = 1; i < MAX_N; i++)
    {
        S[i][0] = 0, S[i][i] = 1;
        for (int j = 1; j < i; j++)
            S[i][j] = (0LL + S[i - 1][j - 1] + 1LL * (i - 1) * S[i - 1][j] % mod) % mod;
    }
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &m, &c);
        int ans = 0;
        for (int i = 0, opt = (m & 1) ? mod - 1 : 1; i <= m; i++, opt = mod - opt)
            ans = (0LL + ans + 1LL * opt * S[m][i] % mod * degradePower(fpow(c, i), n) % mod) % mod;
        printf("%d\n", ans);
    }
    return 0;
}