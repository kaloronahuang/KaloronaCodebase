// P1313.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 10007;

int C[MAX_N][MAX_N];

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
    for (int i = 1; i < MAX_N; i++)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    int a, b, k, n, m;
    scanf("%d%d%d%d%d", &a, &b, &k, &n, &m);
    printf("%lld\n", 1LL * quick_pow(a, n) * quick_pow(b, m) % mod * C[n + m][n] % mod);
    return 0;
}