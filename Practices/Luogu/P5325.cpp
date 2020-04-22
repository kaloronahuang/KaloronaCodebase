// P5325.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

typedef long long ll;

int primes[MAX_N], tot, ppre[MAX_N], ppre2[MAX_N], idx1[MAX_N], idx2[MAX_N], g1[MAX_N], g2[MAX_N], gtot;
ll n, weight[MAX_N];
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

const int inv2 = fpow(2, mod - 2), inv3 = fpow(3, mod - 2);

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, ppre[tot] = (0LL + ppre[tot - 1] + i) % mod, ppre2[tot] = (0LL + ppre2[tot - 1] + 1LL * i * i % mod) % mod;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int sieve(ll x, int y)
{
    if (primes[y] >= x)
        return 0;
    int location = x < MAX_N ? idx1[x] : idx2[n / x], ret_prime = (0LL + g2[location] + mod - g1[location] + mod - (0LL + ppre2[y] + mod - ppre[y]) % mod) % mod;
    int ret_nprime = 0;
    for (int i = y + 1; i <= tot && 1LL * primes[i] * primes[i] <= x; i++)
        for (ll j = 1, acc = primes[i]; acc <= x; j++, acc *= primes[i])
            ret_nprime = (0LL + ret_nprime + 1LL * acc % mod * ((acc - 1) % mod) % mod * ((0LL + sieve(x / acc, i) + (j != 1)) % mod) % mod) % mod;
    return (0LL + ret_prime + ret_nprime) % mod;
}

int main()
{
    scanf("%lld", &n), sieve();
    for (ll i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i);
        // process the prefix p and p^2;
        weight[++gtot] = n / i;
        g1[gtot] = 1LL * weight[gtot] % mod;
        // g2[gtot] = \sum_{i = 1}^weight[gtot] i^2;
        g2[gtot] = (1LL * g1[gtot] * (g1[gtot] + 1) % mod * inv2 % mod * (2LL * g1[gtot] + 1) % mod * inv3 % mod + mod - 1) % mod;
        g1[gtot] = (1LL * g1[gtot] * (g1[gtot] + 1) % mod * inv2 % mod + mod - 1) % mod;
        if (n / i < MAX_N)
            idx1[n / i] = gtot;
        else
            idx2[n / (n / i)] = gtot;
    }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= gtot && 1LL * primes[i] * primes[i] <= weight[j]; j++)
        {
            ll location = weight[j] / primes[i] < MAX_N ? idx1[weight[j] / primes[i]] : idx2[n / (weight[j] / primes[i])];
            g1[j] = (0LL + g1[j] + mod - 1LL * primes[i] * ((g1[location] + mod - ppre[i - 1]) % mod) % mod) % mod;
            g2[j] = (0LL + g2[j] + mod - 1LL * primes[i] * primes[i] % mod * ((g2[location] + mod - ppre2[i - 1]) % mod) % mod) % mod;
        }
    printf("%lld\n", (1LL + sieve(n, 0)) % mod);
    return 0;
}