// 51Nod1584.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int primes[MAX_N], tot, sigma[MAX_N], sfac[MAX_N], sfacpow[MAX_N], powsum[MAX_N], mu[MAX_N];
int dsigma[MAX_N], dfac[MAX_N], dfacpow[MAX_N], dpowsum[MAX_N], presig[MAX_N], f[MAX_N], pre[MAX_N];
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
    mu[1] = 1, sigma[1] = dsigma[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
        {
            mu[i] = mod - 1, primes[++tot] = i;
            sigma[i] = i + 1, sfac[i] = i, powsum[i] = i + 1;
            dsigma[i] = dpowsum[i] = (0LL + 1 + i + 1LL * i * i % mod) % mod, dfac[i] = 1LL * i * i % mod;
        }
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            int v = 1LL * i * primes[j];
            vis[v] = true;
            if (i % primes[j])
            {
                mu[v] = mod - mu[i];
                sigma[v] = 1LL * sigma[i] * sigma[primes[j]] % mod;
                sfac[v] = primes[j], powsum[v] = (0LL + primes[j] + 1) % mod;

                dsigma[v] = 1LL * dsigma[i] * dsigma[primes[j]] % mod;
                dfac[v] = dfac[primes[j]], dpowsum[v] = dpowsum[primes[j]];
            }
            else
            {
                mu[v] = 0;
                powsum[v] = (0LL + powsum[i] + 1LL * sfac[i] * primes[j] % mod) % mod;
                sigma[v] = 1LL * sigma[i] * fpow(powsum[i], mod - 2) % mod * powsum[v] % mod;
                sfac[v] = 1LL * sfac[i] * primes[j] % mod;

                dpowsum[v] = (0LL + dpowsum[i] + 1LL * dfac[i] * primes[j] % mod + 1LL * dfac[i] * primes[j] % mod * primes[j] % mod) % mod;
                dsigma[v] = 1LL * dsigma[i] * fpow(dpowsum[i], mod - 2) % mod * dpowsum[v] % mod;
                dfac[v] = 1LL * dfac[i] * primes[j] % mod * primes[j] % mod;

                break;
            }
        }
    }
    for (int i = 1; i < MAX_N; i++)
        dsigma[i] = 1LL * i * dsigma[i] % mod;
    for (int i = 1; i < MAX_N; i++)
        presig[i] = (0LL + presig[i - 1] + sigma[i]) % mod;
    for (int i = 1; i < MAX_N; i++)
    {
        if (mu[i])
            for (int j = i; j < MAX_N; j += i)
                f[j] = (0LL + f[j] + 1LL * mu[i] * i % mod * sigma[j / i] % mod * presig[j / i] % mod) % mod;
        f[i] = 1LL * i * f[i] % mod, pre[i] = (0LL + pre[i - 1] + 2LL * f[i] % mod + mod - dsigma[i]) % mod;
    }
}

int main()
{
    sieve();
    int T, n, caseTot = 0;
    scanf("%d", &T);
    while (T--)
        caseTot++, scanf("%d", &n), printf("Case #%d: %d\n", caseTot, pre[n]);
    return 0;
}