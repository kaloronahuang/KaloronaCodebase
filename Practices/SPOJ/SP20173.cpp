// SP20173.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e8 + 2;

typedef long long ull;

int T, primes[MAX_N >> 1], tot, BLOCK;
short mu[MAX_N];
ull sigma[MAX_N], ai[int(1e4) + 200];
bitset<MAX_N> vis;

void sieve()
{
    mu[1] = sigma[1] = 1, vis[1] = true;
    for (int i = 2; i <= BLOCK; i++)
    {
        if (!vis[i])
            primes[++tot] = i, sigma[i] = 2, mu[i] = -1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= BLOCK; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                sigma[i * primes[j]] = 2LL * sigma[i] - sigma[i / primes[j]];
                break;
            }
            mu[i * primes[j]] = -mu[i];
            sigma[i * primes[j]] = sigma[i] * sigma[primes[j]];
        }
    }
    for (int i = 1; i <= BLOCK; i++)
        sigma[i] += sigma[i - 1]; //, printf("%lld %d\n", sigma[i], mu[i]);
}

unordered_map<ull, ull> mp;

ull loadSigma(ull upper)
{
    if (upper <= BLOCK)
        return sigma[upper];
    if (mp.count(upper))
        return mp[upper];
    ull ret = 0;
    for (ull i = 1, gx; i <= upper; i = gx + 1)
    {
        gx = upper / (upper / i);
        ret += (gx - i + 1) * (upper / i);
    }
    return mp[upper] = ret;
}

ull g(ull upper)
{
    ull ret = 0, last = 0, curt = 0;
    for (ull i = 1, gx; i <= upper; i = gx + 1)
    {
        gx = upper / (upper / i);
        curt = loadSigma(gx);
        ret += (curt - last) * (upper / i);
        last = curt;
    }
    return ret;
}

int main()
{
    scanf("%d", &T);
    ull mx = 0;
    for (int i = 1; i <= T; i++)
        scanf("%lld", &ai[i]);
    mx = *max_element(ai + 1, ai + 1 + T);
    BLOCK = pow(mx, 2.0 / 3.0), sieve();
    for (int i = 1; i <= T; i++)
    {
        ull n = ai[i], ret = 0;
        for (ull i = 1; 1LL * i * i <= n; i++)
            ret += mu[i] * g(n / i / i);
        printf("%lld\n", ret);
    }
    return 0;
}