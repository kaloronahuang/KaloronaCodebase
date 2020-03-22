// UOJ62.cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAX_N = 1e5 + 200, mod = 998244353;

int n, c, d, q, bi[MAX_N], mu[MAX_N], primes[MAX_N], ptot, pc[MAX_N], pd[MAX_N], fd[MAX_N], h[MAX_N], xi[MAX_N];
bool vis[MAX_N];

int fpow(int bas, int tim)
{
    if (bas == 0 && tim == 0)
        return 0;
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

void sieve()
{
    mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++ptot] = i, mu[i] = mod - 1;
        for (int j = 1; j <= ptot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
            mu[i * primes[j]] = mod - mu[i];
        }
    }
    for (int i = 1; i < MAX_N; i++)
        pc[i] = fpow(i, c), pd[i] = fpow(i, d);
    for (int i = 1; i < MAX_N; i++)
    {
        int f = 1LL * pc[i] * fpow(pd[i], mod - 2) % mod;
        for (int j = 1; i * j < MAX_N; j++)
            fd[i * j] = (0LL + fd[i * j] + 1LL * mu[j] * f % mod) % mod;
    }
}

signed main()
{
    scanf("%lld%lld%lld%lld", &n, &c, &d, &q), sieve();
    while (q--)
    {
        for (int i = 1; i <= n; i++)
            scanf("%lld", &bi[i]), bi[i] = 1LL * bi[i] * fpow(pd[i], mod - 2) % mod;
        bool flag = true;
        for (int i = 1; i <= n; i++)
        {
            if (fd[i] == 0 && bi[i] != 0)
            {
                flag = false;
                break;
            }
            h[i] = 1LL * fpow(fd[i], mod - 2) * bi[i] % mod;
            for (int j = 2 * i; j <= n; j += i)
                bi[j] = (0LL + bi[j] + mod - bi[i]) % mod;
        }
        if (!flag)
        {
            puts("-1");
            continue;
        }
        for (int i = n; i; i--)
        {
            xi[i] = h[i];
            for (int j = 2 * i; j <= n; j += i)
                xi[i] = (0LL + xi[i] + mod - xi[j]) % mod;
        }
        for (int i = 1; i <= n; i++)
            printf("%lld ", 1LL * xi[i] * fpow(pd[i], mod - 2) % mod);
        puts("");
    }
    return 0;
}