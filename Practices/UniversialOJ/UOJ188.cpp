// UOJ188.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e6 + 200;

ll weights[MAX_N], g[MAX_N], n;
int ptot, primes[MAX_N], tot, idx[2][MAX_N], block;
bool vis[MAX_N];

struct locator
{
    int &operator[](const ll &rhs) { return rhs <= block ? idx[0][rhs] : idx[1][n / rhs]; }
} loc;

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

ll solve(ll upper, int nid)
{
    if (upper <= 1)
        return 0;
    ll ans = 0;
    for (int i = nid + 1; i <= tot && 1LL * primes[i] * primes[i] <= upper; i++)
        for (ll acc = primes[i]; 1LL * acc * primes[i] <= upper; acc *= primes[i])
            ans += solve(upper / acc, i) + primes[i] * (g[loc[upper / acc]] - (i - 1));
    return ans;
}

ll solve(ll upper)
{
    n = upper;
    memset(idx, 0, sizeof(idx));
    memset(weights, 0, sizeof(weights));
    memset(g, 0, sizeof(g));
    block = sqrt(n), ptot = 0;
    for (ll i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i);
        weights[++ptot] = n / i;
        loc[weights[ptot]] = ptot;
        g[ptot] = weights[ptot] - 1;
    }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= ptot && 1LL * primes[i] * primes[i] <= weights[j]; j++)
            g[j] -= g[loc[weights[j] / primes[i]]] - (i - 1);
    return solve(upper, 0);
}

int main()
{
    ll l, r;
    scanf("%lld%lld", &l, &r), sieve();
    printf("%lld\n", solve(r) - solve(l - 1));
    return 0;
}