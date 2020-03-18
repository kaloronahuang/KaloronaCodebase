// P4921.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 998244353;

int T, binomial[MAX_N][MAX_N], fac[MAX_N << 1], binaryPow[MAX_N << 1], f[MAX_N];

int sum(int n, int k) { return 1LL * binomial[n][k] * binomial[n][k] % mod * fac[k] % mod * binaryPow[k] % mod * f[n - k] % mod; }

int main()
{
    binomial[0][0] = f[0] = 1;
    for (int i = 1; i < MAX_N; i++)
    {
        binomial[i][0] = binomial[i][i] = 1;
        for (int j = 1; j < i; j++)
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
    }
    for (int i = fac[0] = binaryPow[0] = 1; i < MAX_N << 1; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod, binaryPow[i] = 2LL * binaryPow[i - 1] % mod;
    for (int i = 1; i < MAX_N; i++)
    {
        int cnt = 0;
        for (int j = 1; j <= i; j++)
            cnt = (0LL + cnt + sum(i, j)) % mod;
        f[i] = (0LL + fac[i << 1] + mod - cnt) % mod;
    }
    scanf("%d", &T);
    while (T--)
    {
        int x;
        scanf("%d", &x);
        for (int i = 0; i <= x; i++)
            printf("%d\n", sum(x, i));
    }
    return 0;
}