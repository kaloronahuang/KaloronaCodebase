// LOJ6181.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 200, mod = 998244353;

typedef long long ll;

int mu[MAX_N], ptot, idx[2][MAX_N], block, primes[MAX_N], tot;
ll n, weights[MAX_N], g[MAX_N];
bool vis[MAX_N];

struct locator
{
	int &operator[](const ll &rhs) { return rhs <= block ? idx[0][rhs] : idx[1][n / rhs]; }
} loc;

int main()
{
	scanf("%lld", &n), block = sqrt(n), mu[1] = 1;
	for (int i = 2; i < MAX_N; i++)
	{
		if (!vis[i])
			primes[++tot] = i, mu[i] = mod - 1;
		for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
		{
			vis[i * primes[j]] = true;
			if (i % primes[j] == 0)
			{
				mu[i * primes[j]] = 0;
				break;
			}
			mu[i * primes[j]] = (mod - mu[i]) % mod;
		}
	}
	for (ll i = 1, gx; i <= n; i = gx + 1)
	{
		gx = n / (n / i), weights[++ptot] = n / i;
		loc[weights[ptot]] = ptot;
		g[ptot] = (0LL + weights[ptot] - 1) % mod;
	}
	for (int i = 1; i <= tot; i++)
		for (int j = 1; j <= ptot && 1LL * primes[i] * primes[i] <= weights[j]; j++)
			g[j] = (0LL + g[j] + mod - g[loc[weights[j] / primes[i]]] + i - 1) % mod;
	int ans = 0;
	for (int i = 1; 1LL * i * i <= n; i++)
		ans = (0LL + ans + 1LL * (n / (1LL * i * i)) % mod * mu[i] % mod) % mod;
	ans = (0LL + ans + mod - 2LL * g[1] % mod) % mod;
	printf("%d\n", ans);
	return 0;
}
