// BZ2721.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

typedef long long ll;

int n, primes[MAX_N], tot;
bool vis[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
            primes[++tot] = i;
        for (int j = 1; j <= tot && 1LL * i * primes[j] <= n; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    int ans = 1;
    for (int i = 1; i <= tot; i++)
    {
        int res = 0, base = n;
        while (base)
            res += base /= primes[i];
        ans = 1LL * ans * ((2LL * res % mod + 1) % mod) % mod;
    }
    printf("%d\n", ans);
    return 0;
}