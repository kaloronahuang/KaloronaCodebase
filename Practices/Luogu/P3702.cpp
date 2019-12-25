// P3702.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, MAX_M = 2e7 + 200, mod = 20170408;

int primes[MAX_M], tot, n, m, p, table[MAX_N];
bool vis[MAX_M];

struct matrix
{
    int mat[MAX_N][MAX_N];

    matrix() { memset(mat, 0, sizeof(mat)); }

    int *operator[](const int &rhs) { return mat[rhs]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        for (int i = 0; i < p; i++)
            for (int j = 0; j < p; j++)
                for (int k = 0; k < p; k++)
                    ret[i][j] = (1LL * ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }

    matrix operator^(const int &rhs)
    {
        int tim = rhs;
        matrix ret, bas = *this;
        for (int i = 0; i < p; i++)
            ret[i][i] = 1;
        while (tim)
        {
            if (tim & 1)
                ret = ret * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
} dp, trans;

void sieve()
{
    for (int i = 2; i <= m; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= m; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    for (int i = 1; i <= tot; i++)
        table[primes[i] % p]++;
}

int main()
{
    scanf("%d%d%d", &n, &m, &p);
    sieve();
    for (int c = 0; c < p; c++)
        for (int b = 0; b < p; b++)
        {
            int delta = (c - b + p) % p;
            if (delta == 0)
                trans[b][c] = m / p;
            else if (delta < m)
                trans[b][c] = int((m - delta) / p) + 1;
            else if (delta == m)
                trans[b][c] = 1;
            else
                trans[b][c] = 0;
            trans[b][c] %= mod;
        }
    dp[0][0] = 1, dp = dp * (trans ^ n);
    int ans = dp[0][0];
    memset(dp.mat, 0, sizeof(dp.mat));
    memset(trans.mat, 0, sizeof(trans.mat));
    for (int c = 0; c < p; c++)
        for (int b = 0; b < p; b++)
        {
            int delta = (c - b + p) % p;
            if (delta == 0)
                trans[b][c] = m / p;
            else if (delta < m)
                trans[b][c] = int((m - delta) / p) + 1;
            else if (delta == m)
                trans[b][c] = 1;
            else
                trans[b][c] = 0;
            trans[b][c] = (trans[b][c] + mod - table[delta]) % mod;
        }
    dp[0][0] = 1, dp = dp * (trans ^ n);
    ans = (ans + mod - dp[0][0]) % mod;
    printf("%d\n", ans);
    return 0;
}