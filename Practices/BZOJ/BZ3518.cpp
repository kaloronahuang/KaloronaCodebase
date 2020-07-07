// BZ3518.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200, mod = 1e9 + 7;

int n, m, primes[MAX_N], phi[MAX_N], tot, upper;
bool vis[MAX_N];

int fpow(int bas, int tim)
{
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

const int inv6 = fpow(6, mod - 2);

int S(int n_) { return 1LL * n_ * (n_ + 1) / 2 % mod; }

int f(int n_, int d_) { return (1LL * n_ * int(n_ / d_) % mod + mod - 1LL * d_ * S(n_ / d_) % mod) % mod; }

int main()
{
    scanf("%d%d", &n, &m), upper = min(n, m), phi[1] = 1;
    for (int i = 2; i <= upper; i++)
    {
        if (!vis[i])
            primes[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= upper; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                phi[i * primes[j]] = 1LL * phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = 1LL * phi[i] * phi[primes[j]];
        }
    }
    int ans = 1LL * n * m % mod * (m - 1) % mod * (m - 2) % mod * inv6 % mod;
    ans = (0LL + ans + 1LL * m * n % mod * (n - 1) % mod * (n - 2) % mod * inv6 % mod) % mod;
    int pans = (0LL + mod - 1LL * S(n - 1) * S(m - 1) % mod) % mod;
    for (int i = 1; i <= upper; i++)
        pans = (0LL + pans + 1LL * phi[i] * f(n, i) % mod * f(m, i) % mod) % mod; //, printf("%d ", phi[i]);
    // puts("");
    // printf("%d %d %lld\n", ans, pans, (2LL * pans + ans) % mod);
    printf("%lld\n", (2LL * pans + ans) % mod);
    return 0;
}