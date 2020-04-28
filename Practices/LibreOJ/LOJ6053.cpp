// LOJ6053.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

typedef long long ll;

int primes[MAX_N], tot, pre[MAX_N], idx[2][MAX_N], wtot, g[2][MAX_N], cnt[MAX_N];
ll weights[MAX_N], n;
bool vis[MAX_N];

struct locator
{
    int &operator[](const ll &rhs) const { return rhs < MAX_N ? idx[0][rhs] : idx[1][n / rhs]; }
} loc;

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

const int inv2 = fpow(2, mod - 2);

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, pre[tot] = (0LL + pre[tot - 1] + i) % mod;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int sieve(ll nbound, int nid)
{
    if (nbound <= 1 || nbound <= primes[nid])
        return 0;
    int pos = loc[nbound], ret = ((0LL + g[0][pos] + mod - g[1][pos]) % mod + mod - (0LL + pre[nid] + mod - nid) % mod) % mod;
    if (nid == 0)
        ret = (0LL + ret + 2) % mod;
    for (int i = nid + 1; i <= tot && 1LL * primes[i] * primes[i] <= nbound; i++)
        for (ll j = 1, acc = primes[i]; acc * primes[i] <= nbound; j++, acc *= primes[i])
            ret = (0LL + ret + 1LL * (primes[i] ^ j) * sieve(nbound / acc, i) % mod + (primes[i] ^ (j + 1))) % mod;
    return ret;
}

int main()
{
    scanf("%lld", &n), sieve();
    for (ll i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i);
        weights[++wtot] = n / i;
        g[0][wtot] = 1LL * (weights[wtot] % mod + 2) * ((weights[wtot] % mod + mod - 1) % mod) % mod * inv2 % mod;
        g[1][wtot] = (weights[wtot] % mod + mod - 1) % mod;
        loc[n / i] = wtot;
    }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= wtot && 1LL * primes[i] * primes[i] <= weights[j]; j++)
        {
            int id = loc[weights[j] / primes[i]];
            g[0][j] = (0LL + g[0][j] + mod - 1LL * primes[i] * ((0LL + g[0][id] + mod - pre[i - 1]) % mod) % mod) % mod;
            g[1][j] = (0LL + g[1][j] + mod - 1LL * g[1][id] + (i - 1)) % mod;
        }
    printf("%lld\n", (1LL + sieve(n, 0)) % mod);
    return 0;
}