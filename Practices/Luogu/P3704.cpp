// P3704.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int T, n, m, mu[MAX_N], primes[MAX_N], tot, f[MAX_N], g[MAX_N];
bool vis[MAX_N];

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

void init()
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
    for (int i = 1; i < MAX_N; i++)
        f[i] = 1, g[i] = 1;
    int A = 1, B = 0;
    for (int i = 1; i < MAX_N; i++)
    {
        B = (A + B) % mod, A = (B - A + mod) % mod;
        int bucket[3] = {quick_pow(B, mod - 2), 1, B};
        for (int j = i, cnt = 1; j < MAX_N; j += i, cnt++)
        {
            f[j] = 1LL * f[j] * bucket[1 + mu[cnt]] % mod;
            g[j] = 1LL * g[j] * bucket[1 - mu[cnt]] % mod;
        }
    }
    f[0] = g[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        f[i] = (1LL * f[i] * f[i - 1]) % mod, g[i] = (1LL * g[i] * g[i - 1]) % mod;
}

int main()
{
    scanf("%d", &T), init();
    while (T--)
    {
        scanf("%d%d", &n, &m);
        if (n > m)
            swap(n, m);
        int ans = 1;
        for (int x = 1, gx; x <= n; x = gx + 1)
        {
            gx = min(n / (n / x), m / (m / x));
            ans = 1LL * ans * quick_pow(1LL * f[gx] * g[x - 1] % mod, 1LL * (n / x) * (m / x) % (mod - 1)) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}