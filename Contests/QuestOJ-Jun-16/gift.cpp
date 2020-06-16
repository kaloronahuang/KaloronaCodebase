// gift.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 1e9 + 7;

int cnt[MAX_N], n, k, upper, stiring[MAX_N][MAX_N];

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

/*
int prefixPow(int bas, int idx)
{
	int ret = 0;
	for (int i = 0; i <= idx; i++)
	{
		int pans = 1;
		for (int j = 0; j <= i; j++)
			pans = 1LL * pans * (bas + 1 - j) % mod;
		if (bas < i)
			pans = 0;
		ret = (0LL + ret + 1LL * stiring[idx][i] * fpow(i + 1, mod - 2) % mod * pans % mod) % mod;
	}
	return ret;
}
*/

int main()
{
	scanf("%d%d", &n, &k);
	/*
	stiring[0][0] = 1;
	for (int i = 1; i <= k; i++)
	{
		for (int j = 1; j <= i; j++)
			stiring[i][j] = (0LL + 1LL * stiring[i - 1][j] * j % mod + stiring[i - 1][j - 1]) % mod;
	}
	int pre = prefixPow(n - 1, k), ans = (0LL + fpow(n, k) + 1LL * fpow(2, n) * pre % mod + 1LL * fpow(2, mod - 2) * pre % mod) % mod;
	for (int i = 1; i <= n - 1; i++)
		ans = (0LL + ans + 1LL * fpow(i, k) * fpow((mod + 1) >> 1, i) % mod) % mod;
	printf("%d\n", ans);
	*/
	int ans = fpow(n, k);
	for (int i = 1; i <= n - 1; i++)
		ans = (0LL + ans + 1LL * fpow(2, n - i - 1) * fpow(i, k) % mod) % mod;
	printf("%d\n", ans);
	return 0;
}
