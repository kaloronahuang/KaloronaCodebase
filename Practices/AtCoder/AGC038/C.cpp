// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 998244353;

int n, upper, ai[MAX_N], bi[MAX_N], ci[MAX_N];

int fpow(int bas, int tim)
{
	int ret = 1;
	while (tim)
	{
		if (tim & 1)
			ret = 1LL * ret * bas % mod;
		bas = 1LL * bas * bas % mod;
		tim >>= 1;
	}
	return ret;
}

const int inv2 = fpow(2, mod - 2);

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &ai[i]), bi[ai[i]]++;
	upper = *max_element(ai + 1, ai + 1 + n);
	for (int i = 1; i <= upper; i++)
		ci[i] = fpow(i, mod - 2);
	for (int i = 1; i <= upper; i++)
		for (int j = (i << 1); j <= upper; j += i)
			ci[j] = (0LL + ci[j] + mod - ci[i]) % mod;
	int ans = 0;
	for (int d = 1; d <= upper; d++)
	{
		int p1 = 0, p2 = 0;
		for (int i = d; i <= upper; i += d)
			p1 = (0LL + p1 + 1LL * bi[i] * i % mod) % mod, p2 = (0LL + p2 + 1LL * bi[i] * i % mod * i % mod) % mod;
		int pans = (0LL + 1LL * p1 * p1 % mod + mod - p2) % mod * inv2 % mod;
		ans = (0LL + ans + 1LL * pans * ci[d] % mod) % mod;
	}
	printf("%d\n", ans);
	return 0;
}
