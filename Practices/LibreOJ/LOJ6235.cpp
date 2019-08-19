// LOJ6235.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

ll n, sqrt_n, w[MAX_N], id1[MAX_N], id2[MAX_N], g[MAX_N];
int primes[MAX_N], m;
bool vis[MAX_N];

int main()
{
    scanf("%lld", &n);
    sqrt_n = sqrt(n);
    for (int i = 2; i <= sqrt_n; i++)
    {
        if (!vis[i])
            primes[++primes[0]] = i;
        for (int j = 1; j <= primes[0] && 1LL * i * primes[j] <= sqrt_n; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    for (ll i = 1, j; i <= n; i = j + 1)
    {
        j = (n / (n / i)), w[++m] = n / i;
        if (w[m] <= sqrt_n)
            id1[w[m]] = m;
        else
            id2[n / w[m]] = m;
        g[m] = w[m] - 1;
    }
    for (int j = 1; j <= primes[0]; j++)
        for (int i = 1; i <= m && 1LL * primes[j] * primes[j] <= w[i]; i++)
        {
            int k = (w[i] / primes[j] <= sqrt_n) ? id1[w[i] / primes[j]] : id2[n / (w[i] / primes[j])];
            g[i] += -g[k] + j - 1;
        }
    printf("%lld", g[1]);
    return 0;
}
