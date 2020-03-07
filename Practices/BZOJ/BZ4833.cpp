// BZ4833.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int T, n, mod, primes[MAX_N], tot, mu[MAX_N], f[MAX_N], finv[MAX_N], units[MAX_N];
bool vis[MAX_N];

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

void sieve()
{
    mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
            mu[i * primes[j]] = -mu[i];
        }
    }
}

int main()
{
    scanf("%d", &T), sieve();
    while (T--)
    {
        scanf("%d%d", &n, &mod);
        f[1] = 1, finv[1] = 1;
        for (int i = 2; i <= n; i++)
            f[i] = (2LL * f[i - 1] + f[i - 2]) % mod, finv[i] = fpow(f[i], mod - 2);
        for (int i = 1; i <= n; i++)
            units[i] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j += i)
                if (mu[j / i] < 0)
                    units[j] = 1LL * units[j] * finv[i] % mod;
                else if (mu[j / i] > 0)
                    units[j] = 1LL * units[j] * f[i] % mod;
        for (int i = 2; i <= n; i++)
            units[i] = 1LL * units[i - 1] * units[i] % mod;
        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans = (0LL + ans + 1LL * units[i] * i % mod) % mod;
        printf("%d\n", ans);
    }
    return 0;
}