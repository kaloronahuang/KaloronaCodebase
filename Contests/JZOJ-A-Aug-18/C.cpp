// C.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>
typedef long long ll;

using namespace std;

const int MAX_N = 2e7 + 200, mod = 998244353;

ll n, m, B;
int fi[MAX_N], prime[MAX_N], tot, pows[105], min_prime[MAX_N];
pr g[MAX_N];

int quick_pow(int bas, int tim)
{
    int ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

void sieve()
{
    for (int i = 2; i <= m; i++)
    {
        if (!min_prime[i])
            prime[++tot] = min_prime[i] = g[i].second = i, g[i].first = 1;
        for (int j = 1; j <= tot && 1LL * i * prime[j] <= m; j++)
        {
            int tmp = prime[j] * i;
            g[tmp].first = 1, g[tmp].second = min_prime[tmp] = prime[j];
            if (i % prime[j] == 0)
            {
                g[tmp].first += g[i].first, g[tmp].second *= g[i].second;
                break;
            }
        }
    }
}

int main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &B);
    sieve();
    for (int i = 0; i <= 100; i++)
        pows[i] = quick_pow(i, n % (mod - 1));
    fi[1] = 1;
    for (int i = 2; i <= m; i++)
        if (g[i].second == i)
        {
            for (int j = 0, tmp = 1; j <= g[i].first; j++)
            {
                fi[i] = (1LL * fi[i] + 1LL * tmp * (1LL * pows[g[i].first - j + 1] - 1LL * pows[g[i].first - j] + mod) % mod) % mod;
                if ((B / tmp) % min_prime[i] == 0)
                    tmp *= min_prime[i];
            }
        }
        else
            fi[i] = 1LL * fi[i / g[i].second] * fi[g[i].second] % mod;
    for (int i = 1; i <= m; i++)
        fi[i] = (1LL * fi[i] + 1LL * fi[i - 1]) % mod;
    printf("%d\n", fi[m]);
    return 0;
}