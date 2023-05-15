// DirichletSieve.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e7 + 200;

ll phi[MAX_N], mu[MAX_N];
int primes[MAX_N], tot;
bool vis[MAX_N];

void sieve()
{
    phi[1] = mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = -1, phi[i] = i - 1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0, phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            mu[i * primes[j]] = -mu[i];
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
    for (int i = 2; i < MAX_N; i++)
        mu[i] += mu[i - 1], phi[i] += phi[i - 1];
}

unordered_map<int, ll> vphi, vmu;

ll solveMu(int upper)
{
    if (upper < MAX_N)
        return mu[upper];
    if (vmu.count(upper))
        return vmu[upper];
    ll ret = 1;
    for (int i = 2, gx; i <= upper; i = gx + 1)
    {
        gx = upper / (upper / i);
        ret -= 1LL * (gx - i + 1) * solveMu(upper / i);
    }
    return vmu[upper] = ret;
}

ll solvePhi(int upper)
{
    if (upper < MAX_N)
        return phi[upper];
    if (vphi.count(upper))
        return vphi[upper];
    ll ret = 1LL * upper * (upper + 1) / 2;
    for (int i = 2, gx; i <= upper; i = gx + 1)
    {
        gx = upper / (upper / i);
        ret -= 1LL * (gx - i + 1) * solvePhi(upper / i);
    }
    return vphi[upper] = ret;
}

int main()
{
    int T, n;
    scanf("%d", &T), sieve();
    while (T--)
        scanf("%d", &n), printf("%lld %lld\n", solvePhi(n), solveMu(n));
    return 0;
}