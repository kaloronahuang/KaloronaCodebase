// min25.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

typedef long long ll;

int idx[2][MAX_N], block, pre[MAX_N], pre2[MAX_N], primes[MAX_N], tot, gtot;
int g[2][MAX_N];
ll n, weights[MAX_N];
bool vis[MAX_N];

struct locator
{
    int &operator[](const ll &rhs) { return rhs <= block ? idx[0][rhs] : idx[1][n / rhs]; }
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

const int inv2 = fpow(2, mod - 2), inv6 = fpow(6, mod - 2);

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, pre[tot] = (0LL + pre[tot - 1] + i) % mod, pre2[tot] = (0LL + pre2[tot - 1] + 1LL * i * i % mod) % mod;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int sieve(ll upper, int nid)
{
    if (primes[nid] >= upper)
        return 0;
    int ret = ((0LL + g[1][loc[upper]] + mod - pre2[nid]) % mod + mod - (0LL + g[0][loc[upper]] + mod - pre[nid]) % mod) % mod;
    for (int i = nid + 1; i <= tot && 1LL * primes[i] * primes[i] <= upper; i++)
        for (ll j = 1, acc = primes[i]; acc <= upper; acc *= primes[i], j++)
            ret = (0LL + ret + 1LL * acc % mod * ((0LL + acc - 1) % mod) % mod * (0LL + sieve(upper / acc, i) + (j != 1)) % mod) % mod;
    return ret;
}

int main()
{
    scanf("%lld", &n), block = sqrt(n), sieve();
    for (ll i = 1, gx; i <= n; i = gx + 1)
    {
        gx = (n / (n / i));
        weights[++gtot] = n / i, loc[n / i] = gtot;
        int part = weights[gtot] % mod;
        g[0][gtot] = (1LL * part * (part + 1) % mod * inv2 % mod + mod - 1) % mod;
        g[1][gtot] = ((1LL * part * (0LL + part + 1) % mod * (2LL * part % mod + 1) % mod * inv6 % mod) + mod - 1) % mod;
    }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= gtot && 1LL * primes[i] * primes[i] <= weights[j]; j++)
        {
            g[0][j] = (0LL + g[0][j] + mod - 1LL * primes[i] * ((1LL * g[0][loc[weights[j] / primes[i]]] + mod - pre[i - 1]) % mod) % mod) % mod;
            g[1][j] = (0LL + g[1][j] + mod - 1LL * primes[i] * primes[i] % mod * ((1LL * g[1][loc[weights[j] / primes[i]]] + mod - pre2[i - 1]) % mod) % mod) % mod;
        }
    printf("%d\n", (sieve(n, 0) + 1) % mod);
    return 0;
}