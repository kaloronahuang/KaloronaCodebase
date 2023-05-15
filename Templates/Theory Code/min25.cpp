// min25.cpp
// This code file is a template of min25 sieve with rich comments for easier understanding;
// This code is based on the solution of problem https://www.luogu.com.cn/problem/P5325;

// Mathematical background:
// The goal is to get {\sum_{i = 1}^n f(i), i \in [1, 10^10]}, which f(p^k) = p^k(p^k - 1).
// Of course, the function f is multiplicative function.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

// primes[] : used by linear sieve;
// primePre[] : \sum_{i = 0} [i \in prime] i;
// primePre[] : \sum_{i = 0} [i \in prime] i^2;
// idx[2][] : locations;
// facts[] & ftot : factor stored;
// g[2][] : the original g[][] with space saved;

int primes[MAX_N], tot, primePre[MAX_N], primePre2[MAX_N], idx[2][MAX_N], ftot, g[2][MAX_N];
ll facts[MAX_N];
bool vis[MAX_N];
ll n;

// helper function to locate the factor address;

struct locator
{
    int &operator[](const ll &x) { return x < MAX_N ? idx[0][x] : idx[1][n / x]; }
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

const int inv2 = fpow(2, mod - 2), inv3 = fpow(3, mod - 2);

// preprocess;

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, primePre[tot] = (0LL + primePre[tot - 1] + i) % mod,
            primePre2[tot] = (0LL + primePre2[tot - 1] + 1LL * i * i % mod) % mod;
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
    if (primes[nid] >= nbound)
        return 0;
    // answer would be splited into 2 parts;
    // the \sum_{i = 1} f(i) [i \in primes] part, and the rest part;
    int id = loc[nbound], nppart = 0, ppart = (0LL + g[1][id] + mod - g[0][id] + mod - (0LL + primePre2[nid] + mod - primePre[nid]) % mod) % mod;
    for (int i = nid + 1; i <= tot && 1LL * primes[i] * primes[i] <= nbound; i++)
        for (ll j = 1, acc = primes[i]; acc <= nbound; j++, acc *= primes[i])
            nppart = (0LL + nppart + 1LL * acc % mod * ((acc - 1) % mod) % mod * ((0LL + sieve(nbound / acc, i) + (j != 1)) % mod) % mod) % mod;
    return (0LL + nppart + ppart) % mod;
}

int main()
{
    scanf("%lld", &n), sieve();
    for (ll i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i);
        int id = ++ftot;
        facts[id] = n / i;
        // x^1;
        g[0][ftot] = (1LL * facts[id] % mod * ((facts[id] + 1) % mod) % mod * inv2 % mod + mod - 1) % mod;
        // x^2;
        g[1][ftot] = (1LL * facts[id] % mod * ((facts[id] + 1) % mod) % mod * inv2 % mod * (2LL * facts[id] % mod + 1) % mod * inv3 % mod + mod - 1) % mod;
        loc[facts[id]] = id;
    }
    // do dp;
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= ftot && 1LL * primes[i] * primes[i] <= facts[j]; j++)
        {
            int pos = loc[facts[j] / primes[i]];
            g[0][j] = (0LL + g[0][j] + mod - 1LL * primes[i] * ((0LL + g[0][pos] + mod - primePre[i - 1]) % mod) % mod) % mod;
            g[1][j] = (0LL + g[1][j] + mod - 1LL * primes[i] * primes[i] % mod * ((0LL + g[1][pos] + mod - primePre2[i - 1]) % mod) % mod) % mod;
        }
    printf("%lld\n", (1LL + sieve(n, 0)) % mod);
    return 0;
}