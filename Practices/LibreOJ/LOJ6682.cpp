// LOJ6682.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e7 + 200, mod = 998244353;

typedef long long ll;

ll n, weights[MAX_N], block;
int primes[MAX_N], tot, idx[2][MAX_N], ptot, g[MAX_N];
bool vis[MAX_N];

struct locator
{
    int &operator[](const ll &rhs) { return (rhs <= block) ? idx[0][rhs] : idx[1][n / rhs]; }
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
    for (int i = 2; i <= block; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= block; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int sieve(ll upper, int nid)
{
    if (primes[nid] >= upper || upper <= 1)
        return 0;
    int id = loc[upper], ret = 4LL * (0LL + g[id] + mod - nid) % mod;
    for (int i = nid + 1; i <= tot && 1LL * primes[i] * primes[i] <= upper; i++)
        for (ll j = 1, acc = primes[i]; acc <= upper; j++, acc *= primes[i])
            ret = (0LL + ret + 1LL * (j + 1) * (j + 1) % mod * (0LL + sieve(upper / acc, i) + (j > 1)) % mod) % mod;
    // printf("sieve at %d\n", ret);
    return ret;
}

int main()
{
    int ans = 0;
    scanf("%lld", &n), block = sqrt(n) + 1, sieve();
    for (ll i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i), weights[++ptot] = n / i;
        g[ptot] = (0LL + weights[ptot] % mod + mod - 1) % mod;
        loc[weights[ptot]] = ptot;
        ans = (0LL + ans + 1LL * ((gx - i + 1) % mod) * ((n / i) % mod) % mod) % mod;
    }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= ptot && 1LL * primes[i] * primes[i] <= weights[j]; j++)
        {
            int pos = loc[weights[j] / primes[i]];
            g[j] = (0LL + g[j] + mod - g[pos] + i - 1) % mod;
        }
    int ans2 = sieve(n, 0);
    ans = 1LL * ((0LL + ans2 + 1 + mod - ans) % mod) % mod * inv2 % mod;
    printf("%d\n", ans);
    return 0;
}