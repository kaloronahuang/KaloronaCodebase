// CF1151F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, mod = 1e9 + 7;

int n, k, seq[MAX_N], c;

struct matrix
{
    int mat[101][101];

    void clear() { memset(mat, 0, sizeof(mat)); }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                for (int k = 0; k <= n; k++)
                    ret.mat[i][j] = (1LL * ret.mat[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const int &ti)
    {
        int tim = ti;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 0; i <= n; i++)
            ret.mat[i][i] = 1;
        while (tim)
        {
            if (tim & 1)
                ret = ret * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
} A, B;

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
    const int inv2 = quick_pow(2, mod - 2);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), c += (seq[i] == 0);
    // dp[i][j] = dp[i - 1][j] * (j * (c - j) + (c - j) * (n - 2 * c + j) + (c * (c - 1) >> 1) + ((n - c) * (n - c - 1) >> 1))
    //         += dp[i - 1][j - 1] * (c - j + 1) * (c - j + 1)
    //         += dp[i - 1][j + 1] * (j + 1)* (n - 2 * c + j + 1);
    int preZero = 0;
    for (int i = 1; i <= c; i++)
        preZero += (seq[i] == 0);
    for (int j = 0; j <= c; j++)
    {
        if (j != 0)
            B.mat[j - 1][j] = 1LL * (c - j + 1) * (c - j + 1) % mod;
        B.mat[j][j] = (1LL * j * (c - j) % mod + 1LL * (c - j) * (n - 2 * c + j) % mod + 1LL * (1LL * c * (c - 1) % mod * inv2 % mod) + (1LL * (n - c) * (n - c - 1) % mod * inv2 % mod)) % mod;
        if (j != c)
            B.mat[j + 1][j] = 1LL * (j + 1) * (n - 2 * c + j + 1) % mod;
    }
    A.mat[0][preZero] = 1;
    B = B ^ k, A = A * B;
    int ans = A.mat[0][c], tot = 0;
    for (int i = 0; i <= c; i++)
        tot = (1LL * tot + A.mat[0][i]) % mod;
    printf("%lld\n", 1LL * ans * quick_pow(tot, mod - 2) % mod);
    return 0;
}