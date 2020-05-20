// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, LOG = 21, mod = 1073741824;

// sigma[i] = \prod_{i = 1}^m (1 + c_i);
// sigma2[i] = \prod_{i = 1}^m (1 + 2c_i);

int T, sigma[MAX_N], primes[MAX_N], tot, sigma2[MAX_N], mu[MAX_N], nxt[MAX_N], *sum[MAX_N];
int prod[LOG][LOG][MAX_N];
bool vis[MAX_N];

void sieve()
{
    sigma[1] = sigma2[1] = mu[1] = nxt[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, sigma[i] = 2, sigma2[i] = 3, mu[i] = -1, nxt[i] = 1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                nxt[i * primes[j]] = nxt[i], mu[i * primes[j]] = 0;
                if (nxt[i * primes[j]] > 1)
                {
                    sigma[i * primes[j]] = sigma[i * primes[j] / nxt[i]] * sigma[nxt[i]];
                    sigma2[i * primes[j]] = sigma2[i * primes[j] / nxt[i]] * sigma2[nxt[i]];
                }
                else
                    // p^d;
                    sigma[i * primes[j]] = sigma[i] + 1, sigma2[i * primes[j]] = sigma2[i] + 2;
                break;
            }
            sigma[i * primes[j]] = 1LL * sigma[i] * sigma[primes[j]];
            sigma2[i * primes[j]] = 1LL * sigma2[i] * sigma2[primes[j]];
            nxt[i * primes[j]] = i, mu[i * primes[j]] = -mu[i];
        }
    }
}

int main()
{
    sieve();
    sum[0] = (int *)malloc(MAX_N * sizeof(int));
    for (int d = 1; d < MAX_N; d++)
    {
        int len = (MAX_N + d - 1) / d;
        sum[d] = (int *)malloc(len * sizeof(int));
        for (int i = 1; i < len; i++)
            sum[d][i] = (0LL + sum[d][i - 1] + 1LL * sigma[i] * sigma2[i * d] % mod) % mod;
    }
    for (int n_ = 1; n_ < LOG; n_++)
        for (int m_ = n_; m_ < LOG; m_++)
            for (int d = 1; d < MAX_N; d++)
                prod[n_][m_][d] = (0LL + prod[n_][m_][d - 1] + mod + 1LL * mu[d] * sum[d][n_] % mod * sum[d][m_] % mod) % mod;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        int ret = 0;
        if (n > m)
            swap(n, m);
        for (int d = 1, gx; d <= n; d = gx + 1)
        {
            gx = min(n / (n / d), m / (m / d));
            int nd = n / d, md = m / d;
            if (md < LOG)
                ret = (0LL + ret + prod[nd][md][gx] + mod - prod[nd][md][d - 1]) % mod;
            else
                for (int i = d; i <= gx; i++)
                    ret = (0LL + ret + mod + 1LL * mu[i] * sum[i][nd] % mod * sum[i][md] % mod) % mod;
        }
        printf("%d\n", ret);
    }
    return 0;
}