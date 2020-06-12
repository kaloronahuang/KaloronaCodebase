// SP20174.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef unsigned long long ll;

int T, tot, primes[MAX_N], pre[MAX_N], block, ptot, idx[2][MAX_N];
bool vis[MAX_N];
ll n, weights[MAX_N], g[MAX_N];

struct locator
{
	int &operator[](const ll &rhs) { return rhs <= block ? idx[0][rhs] : idx[1][n / rhs]; }
} loc;

void sieve()
{
	for (int i = 2; i < MAX_N; i++)
	{
		if (!vis[i])
			primes[++tot] = i, pre[tot] = pre[tot - 1] + 4;
		for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
		{
			vis[i * primes[j]] = true;
			if (i % primes[j] == 0)
				break;
		}
	}
}

ll calc(ll upper, int nid)
{
	if (primes[nid] > upper)
		return 0;
	ll ret = g[loc[upper]] - pre[nid];
	for (int i = nid + 1; i <= tot && 1LL * primes[i] * primes[i] <= upper; i++)
		for (ll j = 1, acc = primes[i]; acc <= upper; j++, acc *= primes[i])
			ret += (calc(upper / acc, i) + (j != 1)) * (3LL * j + 1);
	return ret;
}

ll solve()
{
	ptot = 0, block = sqrt(n);
	for (ll i = 1, gx; i <= n; i = gx + 1)
	{
		gx = n / (n / i);
		weights[++ptot] = n / i, loc[n / i] = ptot;
		g[ptot] = 4LL * (weights[ptot] - 1);
	}
	for (int i = 1; i <= tot; i++)
		for (int j = 1; j <= ptot && 1LL * primes[i] * primes[i] <= weights[j]; j++)
			g[j] -= g[loc[weights[j] / primes[i]]] - pre[i - 1];
	return calc(n, 0);
}

int main()
{
	scanf("%d", &T), sieve();
	while (T--)
		scanf("%lld", &n), printf("%llu\n", solve() + 1);
	return 0;
}
