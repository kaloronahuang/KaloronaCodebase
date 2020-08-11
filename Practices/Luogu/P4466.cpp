// P4466.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1 << 20;

int n, m, mu[MAX_N], primes[MAX_N], tot;
bool vis[MAX_N];

ll calc(int x, int upper)
{
    ll ret = 0;
    int sum = (x << 1);
    if (upper == 0)
        return 0;
    for (int i = x + 1, gx; i < sum; i = gx + 1)
    {
        if ((upper / i) == 0)
            return ret;
        gx = min(upper / (upper / i), sum - 1);
        ret += (gx - i + 1) * (upper / i);
    }
    return ret;
}

int main()
{
    scanf("%d", &n), mu[1] = 1, m = sqrt(n);
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            mu[i * primes[j]] = -mu[i];
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
        }
    }
    ll ans = 0;
    for (int k = 1; k <= m; k++)
        if (mu[k] != 0)
            for (int x = 1; 1LL * x * k <= m; x++)
                ans += mu[k] * calc(x, n / (1LL * x * k * k));
    printf("%lld\n", ans);
    return 0;
}