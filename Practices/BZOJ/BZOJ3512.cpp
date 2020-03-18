// BZOJ3512.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int primes[MAX_N], phi[MAX_N], low[MAX_N], tot, pre[MAX_N];
bool vis[MAX_N];
map<int, int> phi_mp;
map<pair<int, int>, int> ans_mp;

void sieve()
{
    phi[1] = low[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            phi[i] = i - 1, low[i] = primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                low[i * primes[j]] = low[i], phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            low[i * primes[j]] = low[i] * primes[j], phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
    for (int i = 1; i < MAX_N; i++)
        pre[i] = (0LL + pre[i - 1] + phi[i]) % mod;
}

int sieve_phi(int n)
{
    if (phi_mp.count(n))
        return phi_mp[n];
    if (n < MAX_N)
        return pre[n];
    int ret = 1LL * n * (n + 1) / 2 % mod;
    for (int i = 2, gx; i <= n; i = gx + 1)
    {
        gx = (n / (n / i));
        ret = (0LL + ret + mod - 1LL * (gx - i + 1) * sieve_phi(n / i) % mod) % mod;
    }
    return phi_mp[n] = ret;
}

int sieve(int n, int k)
{
    if (n == 0 || k == 0)
        return 0;
    if (n == 1)
        return sieve_phi(k);
    if (k == 1)
        return phi[n];
    if (ans_mp.count(make_pair(n, k)))
        return ans_mp[make_pair(n, k)];
    int min_fac = low[n], outer = n / min_fac, ret = 0;
    for (int i = 1; 1LL * i * i <= min_fac; i++)
        if (min_fac % i == 0)
        {
            ret = (0LL + ret + 1LL * phi[min_fac / i] * sieve(i, k / i) % mod) % mod;
            if (1LL * i * i != min_fac)
                ret = (0LL + ret + 1LL * phi[i] * sieve((min_fac / i), k / (min_fac / i)) % mod) % mod;
        }
    ret = 1LL * ret * outer % mod;
    return ans_mp[make_pair(n, k)] = ret;
}

int main()
{
    int n, m, ans = 0;
    scanf("%d%d", &n, &m), sieve();
    if (n > m)
        swap(n, m);
    for (int i = 1; i <= n; i++)
        ans = (0LL + ans + sieve(i, m)) % mod;
    printf("%d\n", ans);
    return 0;
}