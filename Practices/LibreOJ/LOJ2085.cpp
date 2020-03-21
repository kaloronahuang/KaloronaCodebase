// LOJ2085.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 300, MAX_K = 2020;

typedef long long ll;

int n, m, k, f[MAX_K], g[MAX_N], mu[MAX_N], tot, primes[MAX_N], pre_mu[MAX_N];
bool vis[MAX_N];
map<pair<ll, ll>, ll> ump;

void preprocess()
{
    mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true, mu[i * primes[j]] = -mu[i];
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
        }
    }
    for (int i = 1; i < MAX_N; i++)
        pre_mu[i] = pre_mu[i - 1] + mu[i];
    for (int i = 1; i <= k; i++)
        f[i] = f[i - 1] + (__gcd(i, k) == 1);
}

ll F(int x) { return 1LL * (x / k) * f[k - 1] + f[x % k]; }

ll G(int x, int y)
{
    if (x == 0 || (y == 1 && x < MAX_N))
        return pre_mu[x];
    if (ump.count(make_pair(x, y)))
        return ump[make_pair(x, y)];
    ll ret = 0;
    if (y == 1)
    {
        ret = 1;
        for (ll i = 2, gx; i <= x; i = gx + 1)
        {
            gx = x / (x / i);
            ret -= (gx - i + 1) * G(x / i, y);
        }
    }
    else
    {
        for (int i = 1; 1LL * i * i <= y; i++)
            if (y % i == 0)
            {
                if (mu[i])
                    ret += G(x / i, i);
                if (1LL * i * i != y && mu[y / i])
                    ret += G(x / (y / i), y / i);
            }
    }
    return ump[make_pair(x, y)] = ret;
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    preprocess();
    ll ans = 0, last = 0;
    for (int i = 1, gx; i <= min(n, m); i = gx + 1)
    {
        gx = min(n / (n / i), m / (m / i));
        ll curt = G(gx, k);
        ans += (curt - last) * (n / i) * F(m / i);
        last = curt;
    }
    printf("%lld\n", ans);
    return 0;
}