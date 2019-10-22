// P4167.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int primes[MAX_N], f[MAX_N], tot, n, bucket[MAX_N];

void sieve()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (f[i] == 0)
            primes[++tot] = i, f[i] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            if (f[i] < primes[j])
                break;
            f[primes[j] * i] = primes[j];
        }
    }
}

int main()
{
    sieve();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = i; j != 1; j /= f[j])
            bucket[f[j]] = (bucket[f[j]] + 1) % mod;
    int ans = 1;
    for (int i = 1; i <= n; i++)
        ans = (1LL * ans * ((bucket[i] * 2 + 1) % mod) % mod) % mod;
    printf("%d", ans);
    return 0;
}