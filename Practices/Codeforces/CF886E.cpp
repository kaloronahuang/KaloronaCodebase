// CF886E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int n, m, dp[MAX_N], fac[MAX_N], fac_inv[MAX_N];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = fac[0] = 1; i <= n; i++)
		fac[i] = 1LL * fac[i - 1] * i % mod;
	fac_inv[0] = fac_inv[1] = 1;
	for (int i = 2; i <= n; i++)
		fac_inv[i] = 1LL * (mod - mod / i) * fac_inv[mod % i] % mod;
	for (int i = 2; i <= n; i++)
		fac_inv[i] = 1LL * fac_inv[i - 1] * fac_inv[i] % mod;
	int pre = 0;
	for (int i = m + 2; i <= n; i++)
	{
		if (i - m - 1 >= 1)
			pre = (0LL + pre + mod - 1LL * dp[i - m - 1] * fac_inv[i - m - 2] % mod) % mod;
		dp[i] = (1LL * fac[i - 2] * (i - m - 1) % mod + 1LL * pre * fac[i - 2] % mod) % mod;
		pre = (0LL + pre + 1LL * dp[i] * fac_inv[i - 1] % mod) % mod;
	}
	int ans = 0;
	for (int i = m + 1; i <= n; i++)
		ans = (0LL + ans + 1LL * fac[n - 1] * dp[i] % mod * fac_inv[i - 1] % mod) % mod;
	printf("%d\n", ans);
	return 0;
}
