// BZ2671.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e6 + 200;

typedef long long ll;

int mu[MAX_N], primes[MAX_N], tot;
bool vis[MAX_N];

void sieve()
{
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
}

ll solve(ll n, ll m)
{
	ll ret = 0;
	for (ll i = 1; i <= m; i++)
	{
		ll tmp = n / i;
		for (ll j = i + 1, gx; j < (i << 1) && j <= tmp; j = gx + 1)
		{
			gx = min((i << 1) - 1, tmp / (tmp / j));
			ret += 1LL * (gx - j + 1) * (tmp / j);
		}
	}
	return ret;
}

int main()
{
	int n, m;
	scanf("%d", &n), m = sqrt(n), sieve();
	ll ans = 0;
	for (int i = 1; i <= m; i++)
		ans += 1LL * mu[i] * solve(n / i / i, m / i);
	printf("%lld\n", ans);
	return 0;
}
