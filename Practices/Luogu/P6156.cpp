// P6156.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e7 + 200, mod = 998244353;

int n, primes[MAX_N], g[4][MAX_N], tot, mu[MAX_N], pw[MAX_N];
ll kidx;
bool vis[MAX_N];

int fpow(int bas, ll tim)
{
    int ret = 1;
    tim %= (mod - 1), bas %= mod;
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
    mu[1] = 1, pw[1] = fpow(1, kidx);
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = mod - 1, pw[i] = fpow(i, kidx);
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            pw[i * primes[j]] = 1LL * pw[i] * pw[primes[j]] % mod;
            mu[i * primes[j]] = (0LL + mod - mu[i]) % mod, vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
        }
    }
}

int main()
{
    scanf("%d%lld", &n, &kidx), sieve();
    for (int i = 1; i <= n; i++)
    {
        g[0][i] = (0LL + g[0][i - 1] + 1LL * mu[i] * mu[i] % mod * pw[i] % mod * i % mod) % mod;
        g[1][i] = (0LL + g[1][i - 1] + 1LL * mu[i] * pw[i] % mod) % mod;
    }
    n <<= 1;
    for (int i = 1; i <= n; i++)
        pw[i] = (0LL + pw[i] + pw[i - 1]) % mod;
    n >>= 1;
    for (int i = 1; i <= n; i++)
        g[2][i] = (0LL + g[2][i - 1] + pw[i << 1] + mod - pw[i] + pw[(i << 1) - 1] + mod - pw[i]) % mod;
    int ans = 0;
    for (int i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i);
        int pans = 0;
        for (int j = 1, gy, upper = n / i; j <= upper; j = gy + 1)
        {
            gy = upper / (upper / j);
            pans = (0LL + pans + 1LL * (g[1][gy] + mod - g[1][j - 1]) % mod * g[2][upper / j] % mod) % mod;
        }
        ans = (0LL + ans + 1LL * (g[0][gx] + mod - g[0][i - 1]) % mod * pans % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}