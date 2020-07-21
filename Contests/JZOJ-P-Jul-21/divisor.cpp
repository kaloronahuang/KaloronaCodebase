// divisor.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7, inv2 = (mod + 1) >> 1;

typedef long long ll;

int n, primes[MAX_N], pid[MAX_N], fcnt[MAX_N], tot, upper, ans, suffix[MAX_N];
bool vis[MAX_N];
ll m;

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}

void sieve()
{
    upper = max(1LL * n, m);
    for (int i = 2; i <= upper; i++)
    {
        if (!vis[i])
            primes[++tot] = i, pid[i] = tot;
        for (int j = 1; 1LL * i * primes[j] <= upper; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

int calc(int x) { return 1LL * x * (x + 1) % mod * inv2 % mod; }

void dfs(int pos, int idx, int prod)
{
    if (pos == tot + 1 || 1LL * idx * primes[pos] > m)
        return (void)(ans = (0LL + ans + 1LL * prod * suffix[pos] % mod) % mod);
    int pidx = 0;
    ll acc = 1;
    while (1LL * idx * acc <= m)
    {
        int nxt_prod = 1LL * prod * ((1LL * (1LL + fcnt[pos]) * (1LL + pidx) % mod + calc(fcnt[pos])) % mod) % mod;
        dfs(pos + 1, idx * acc, nxt_prod);
        acc = 1LL * acc * primes[pos], pidx++;
    }
}

int main()
{
    // fileIO("divisor");
    scanf("%d%lld", &n, &m), sieve(), suffix[tot + 1] = 1;
    for (int x = 2; x <= n; x++)
    {
        int acc = x;
        for (int i = 1; i <= tot && 1LL * primes[i] * primes[i] <= acc; i++)
            while (acc % primes[i] == 0)
                fcnt[i]++, acc /= primes[i];
        if (acc > 1)
            fcnt[pid[acc]]++;
    }
    for (int i = tot; i >= 1; i--)
        suffix[i] = 1LL * suffix[i + 1] * (((1LL + fcnt[i]) + calc(fcnt[i])) % mod) % mod;
    dfs(1, 1, 1), printf("%d\n", ans);
    return 0;
}