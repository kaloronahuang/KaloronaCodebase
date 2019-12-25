// P5221.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 5, mod = 104857601;

int primes[MAX_N >> 1], tot, phi[MAX_N], n;
bitset<MAX_N> vis;

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
    scanf("%d", &n), phi[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            primes[++tot] = i, phi[i] = (i - 1);
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= n; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
    for (int i = 1; i <= n; i++)
        phi[i] = (2LL * phi[i] + phi[i - 1]) % (mod - 1);
    int ans = 1, tmp = 1;
    for (int i = 1; i <= n; i++)
        ans = 1LL * ans * i % mod;
    ans = quick_pow(ans, n << 1);
    for (int d = 2; d <= n; d++)
        tmp = 1LL * tmp * quick_pow(d, phi[n / d] - 1) % mod;
    printf("%lld\n", 1LL * ans * quick_pow(1LL * tmp * tmp % mod, mod - 2) % mod);
    return 0;
}