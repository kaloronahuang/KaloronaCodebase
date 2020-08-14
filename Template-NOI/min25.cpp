// min25.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

int primes[MAX_N], pre[2][MAX_N], tot, ptot, block, idx[2][MAX_N];
ll g[2][MAX_N], weights[MAX_N], n;
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
            primes[++tot] = i, pre[0][tot] = i, pre[1][tot] = 1LL * i * i % mod;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    for (int i = 1; i <= tot; i++)
    {
        pre[0][i] = (0LL + pre[0][i - 1] + pre[0][i]) % mod;
        pre[1][i] = (0LL + pre[1][i - 1] + pre[1][i]) % mod;
    }
}

int S1(int upper) { return 1LL * upper * (upper + 1) % mod * inv2 % mod; }

int S2(int upper) { return 1LL * upper * (upper + 1) % mod * (2LL * upper % mod + 1) % mod * inv6 % mod; }

int solve(ll upper, int nid)
{
    if (primes[nid] >= upper)
        return 0;
    int ret = ((0LL + g[1][loc[upper]] + mod - pre[1][nid]) % mod + mod - (0LL + g[0][loc[upper]] + mod - pre[0][nid]) % mod) % mod;
    for (int i = nid + 1; i <= tot && 1LL * primes[i] * primes[i] <= upper; i++)
        for (ll eid = 1, acc = primes[i]; 1LL * acc * primes[i] <= upper; eid++, acc *= primes[i])
            ret = (0LL + ret + (1LL * acc * acc % mod + mod - acc) % mod * solve(upper / acc, i) + 1LL * acc * primes[i] % mod * ((1LL * acc * primes[i] % mod + mod - 1) % mod) % mod) % mod;
    return ret;
}

int main()
{
    scanf("%lld", &n), block = sqrt(n), sieve();
    for (ll i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i);
        weights[++ptot] = n / i, loc[weights[ptot]] = ptot;
        g[0][ptot] = (0LL + S1(weights[ptot] % mod) + mod - 1) % mod;
        g[1][ptot] = (0LL + S2(weights[ptot] % mod) + mod - 1) % mod;
    }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= ptot && 1LL * primes[i] * primes[i] <= weights[j]; j++)
        {
            g[0][j] = (0LL + g[0][j] + mod - 1LL * primes[i] * ((0LL + g[0][loc[weights[j] / primes[i]]] + mod - pre[0][i - 1]) % mod) % mod) % mod;
            g[1][j] = (0LL + g[1][j] + mod - 1LL * primes[i] * primes[i] % mod * ((0LL + g[1][loc[weights[j] / primes[i]]] + mod - pre[1][i - 1]) % mod) % mod) % mod;
        }
    printf("%d\n", (solve(n, 0) + 1) % mod);
    return 0;
}