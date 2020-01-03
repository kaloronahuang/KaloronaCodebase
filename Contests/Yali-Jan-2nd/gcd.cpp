// gcd.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 2000, mod = 1e9 + 7;

int phi[MAX_N], mu[MAX_N], primes[MAX_N], tot, f[MAX_N], n, ai[MAX_N], bucket[MAX_N];
bool vis[MAX_N];
vector<int> fac[MAX_N], tmp;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    mu[1] = 1, phi[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = -1, phi[i] = i - 1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= n; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                mu[i * primes[j]] = 0;
                break;
            }
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
            mu[i * primes[j]] = -mu[i];
        }
    }
    // \Theta(n \log n);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i)
            fac[j].push_back(i);
    // process the f(x), by enumerating size d;
    for (int d = 1; d <= n; d++)
    {
        for (int i = d; i <= n; i += d)
            for (vector<int>::iterator it = fac[ai[i]].begin(); it != fac[ai[i]].end(); it++)
                bucket[*it]++, tmp.push_back(*it);
        for (vector<int>::iterator it = tmp.begin(); it != tmp.end(); it++)
            if (bucket[*it])
                f[d] = (1LL * f[d] + 1LL * bucket[*it] * bucket[*it] % mod * phi[*it] % mod) % mod, bucket[*it] = 0;
        tmp.clear();
    }
    int ans = 0;
    for (int d = 1; d <= n; d++)
        for (int x = 1; x <= (n / d); x++)
            ans = (1LL * ans + 1LL * d * mu[x] % mod * f[d * x] % mod + mod) % mod;
    printf("%d\n", ans);
    return 0;
}