// function.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 500;

typedef long long ll;

int T, n, primes[MAX_N], tot;
ll sigma[MAX_N], mu[MAX_N], pmu[MAX_N];
bool vis[MAX_N];
unordered_map<ll, ll> ump;

ll getSigma(ll upper)
{
    if (upper < MAX_N)
        return sigma[upper];
    ll ret = 0;
    for (ll i = 1, gx; i <= upper; i = gx + 1)
    {
        gx = upper / (upper / i);
        ret += 1LL * (upper / i) * (gx - i + 1);
    }
    return ret;
}

ll getMu2(ll upper)
{
    if (upper < MAX_N)
        return pmu[upper];
    ll ret = 0;
    for (int i = 1; 1LL * i * i <= upper; i++)
        ret += 1LL * mu[i] * (upper / (1LL * i * i));
    return ret;
}

int main()
{
    sigma[1] = mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = -1, sigma[i] = 2;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                sigma[i * primes[j]] = 2LL * sigma[i] - sigma[i / primes[j]];
            }
            else
            {
                mu[i * primes[j]] = -mu[i];
                sigma[i * primes[j]] = sigma[i] * sigma[primes[j]];
            }
        }
    }
    for (int i = 1; i < MAX_N; i++)
        pmu[i] = pmu[i - 1] + mu[i] * mu[i], sigma[i] += sigma[i - 1];
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        ll ret = 0;
        for (int i = 1, gx; i <= n; i = gx + 1)
        {
            gx = n / (n / i);
            ret += getSigma(n / i) * (getMu2(gx) - getMu2(i - 1));
        }
        printf("%lld\n", ret);
    }
    return 0;
}