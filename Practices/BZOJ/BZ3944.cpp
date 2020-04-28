// BZ3944.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 2e5 + 200;

int T, primes[MAX_N], tot, idx[2][MAX_N];
ll g[2][MAX_N], pre[2][MAX_N], n, facts[MAX_N], ftot;
bool vis[MAX_N];

struct locator
{
    int &operator[](const ll &x) { return x < MAX_N ? idx[0][x] : idx[1][n / x]; }
} loc;

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, pre[0][tot] = pre[0][tot - 1] + i, pre[1][tot] = -tot;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

ll sieve_phi(ll nbound, int nid)
{
    if (primes[nid] >= nbound || nbound <= 1)
        return 0;
    int id = loc[nbound];
    ll ret = g[0][id] - g[1][id] - pre[0][nid] + nid;
    for (int i = nid + 1; i <= tot && 1LL * primes[i] * primes[i] <= nbound; i++)
        for (ll acc = primes[i] * primes[i], phi_acc = primes[i] - 1; acc <= nbound;)
        {
            ret += 1LL * phi_acc * sieve_phi(nbound / (acc / primes[i]), i) + phi_acc * primes[i];
            acc *= primes[i], phi_acc *= primes[i];
        }
    return ret;
}

ll sieve_mu(ll nbound, int nid)
{
    if (primes[nid] >= nbound || nbound <= 1)
        return 0;
    int id = loc[nbound];
    ll ret = -(g[1][id] - nid);
    for (int i = nid + 1; i <= tot && 1LL * primes[i] * primes[i] <= nbound; i++)
        ret -= sieve_mu(nbound / primes[i], i);
    return ret;
}

void solve()
{
    ftot = 0;
    for (ll i = 1, gx; i <= n; i = gx + 1)
    {
        gx = n / (n / i);
        int id = ++ftot;
        facts[id] = n / i;
        // prime sum & number;
        g[0][ftot] = (facts[id] + 2) * (facts[id] - 1) / 2, g[1][ftot] = facts[id] - 1;
        // prime num;
        loc[facts[id]] = id;
    }
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= ftot && 1LL * primes[i] * primes[i] <= facts[j]; j++)
        {
            int pos = loc[facts[j] / primes[i]];
            g[0][j] -= 1LL * primes[i] * (0LL + g[0][pos] - pre[0][i - 1]);
            g[1][j] -= g[1][pos] - i + 1;
        }
    if (n == 0)
        puts("0 0");
    else
        printf("%lld %lld\n", sieve_phi(n, 0) + 1, sieve_mu(n, 0) + 1);
}

int main()
{
    scanf("%d", &T), sieve();
    while (T--)
        scanf("%lld", &n), solve();
    return 0;
}