// LOJ572.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef unsigned uint;

int n, pk, tot, block, idx[2][MAX_N], ptot;
uint primes[MAX_N], primes_k[MAX_N], weights[MAX_N], g[MAX_N];
bool vis[MAX_N];
map<uint, uint> mp;

struct locator
{
	int &operator[](const int &rhs) { return rhs <= block ? idx[0][rhs] : idx[1][n / rhs]; }
} loc;

uint fpow(uint bas, uint tim)
{
	uint ret = 1;
	while (tim)
	{
		if (tim & 1)
			ret *= bas;
		bas *= bas;
		tim >>= 1;
	}
	return ret;
}

void sieve()
{
	for (int i = 2; i < MAX_N; i++)
	{
		if (!vis[i])
			primes[++tot] = i, primes_k[tot] = fpow(i, pk);
		for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
		{
			vis[i * primes[j]] = true;
			if (i % primes[j] == 0)
				break;
		}
	}
}

uint calc(uint upper, int nid)
{
	if (primes[nid] >= upper)
		return 0;
	uint ret = (g[loc[upper]] - nid) * primes_k[nid];
	for (int i = nid + 1; i <= tot && 1LL * primes[i] * primes[i] <= upper; i++)
		for (uint acc = primes[i], j = 1; 1LL * acc * primes[i] <= upper; acc *= primes[i], j++)
			ret += calc(upper / acc, i) + primes_k[i];	
	return ret;
}

uint S(uint upper)
{
	if (mp.count(upper))
		return mp[upper];
	uint ret = calc(upper, 0) + g[loc[upper]];
	for (uint i = 2, gx; i <= upper; i = gx + 1)
	{
		gx = upper / (upper / i);
		ret -= S(upper / i) * (gx - i + 1);
	}
	return mp[upper] = ret;
}

int main()
{
	scanf("%d%d", &n, &pk), sieve(), block = sqrt(n);
	for (int i = 1, gx; i <= n; i = gx + 1)
	{
		gx = n / (n / i);
		weights[++ptot] = n / i;
		loc[n / i] = ptot, g[ptot] = weights[ptot] - 1;
	}
	for (int i = 1; i <= tot; i++)
		for (int j = 1; j <= ptot && 1LL * primes[i] * primes[i] <= weights[j]; j++)
			g[j] -= g[loc[weights[j] / primes[i]]] - (i - 1);
	uint ans = 0, last_prod = 0;
	for (uint i = 1, gx; i <= n; i = gx + 1)
	{
		gx = n / (n / i);
		uint prod = S(gx), pans = prod - last_prod;
		ans += pans * uint(n / i) * uint(n / i);
		last_prod = prod;
	}
	printf("%u\n", ans);
	return 0;
}
