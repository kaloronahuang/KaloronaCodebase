// CF1139D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int n, mu[MAX_N], primes[MAX_N], tot, inv[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d", &n), mu[1] = 1, inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = mod - 1;
        for (int j = 1; 1LL * i * primes[j] <= n && j <= tot; j++)
        {
            vis[i * primes[j]] = true, mu[i * primes[j]] = mod - mu[i];
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
        }
    }
    int ans = 1;
    for (int i = 2; i <= n; i++)
        ans = (0LL + ans + mod - 1LL * mu[i] * (n / i) % mod * inv[n - (n / i)] % mod) % mod;
    printf("%d\n", ans);
    return 0;
}