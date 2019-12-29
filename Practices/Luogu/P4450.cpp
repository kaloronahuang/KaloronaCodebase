// P4450.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int A, B, d, primes[MAX_N], tot, mu[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d%d%d", &A, &B, &d);
    mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
            mu[i * primes[j]] = -mu[i];
        }
    }
    long long ans = 0;
    for (int x = 1; x <= min(A / d, B / d); x++)
        ans += 1LL * mu[x] * (A / (d * x)) * (B / (d * x));
    printf("%lld\n", ans);
    return 0;
}