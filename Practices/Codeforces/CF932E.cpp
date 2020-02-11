// CF932E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 1e9 + 7;

int n, k, S[MAX_N][MAX_N];

int quick_pow(int bas, int tim)
{
    if (tim < 0)
        return quick_pow(quick_pow(bas, mod - 2), -tim);
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
    scanf("%d%d", &n, &k);
    S[0][0] = 1;
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= i; j++)
            S[i][j] = (0LL + S[i - 1][j - 1] + 1LL * j * S[i - 1][j] % mod) % mod;
    int ret = 0, binomial = 1;
    for (int i = 0; i <= k; i++)
    {
        int tmp = 1LL * S[k][i] * quick_pow(2, n - i) % mod * binomial % mod;
        ret = (0LL + ret + 1LL * tmp % mod) % mod, binomial = 1LL * binomial * (n - i) % mod;
    }
    if (k == 0)
        ret--;
    printf("%d\n", ret);
    return 0;
}