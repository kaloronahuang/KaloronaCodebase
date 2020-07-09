// E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 440, mod = 998244353;

int n, ai[MAX_N], bi[MAX_N], sa, sb, inv[MAX_N], fac[MAX_N], dp[2][MAX_N][MAX_N];

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

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &ai[i], &bi[i]), sa += ai[i], sb += bi[i];
	inv[0] = inv[1] = 1;
	for (int i = 2; i < MAX_N; i++)
		inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
	for (int i = fac[0] = 1; i < MAX_N; i++)
		fac[i] = 1LL * fac[i - 1] * i % mod;
	for (int i = 1; i < MAX_N; i++)
		inv[i] = 1LL * inv[i] * inv[i - 1] %
	
	int b = 0;
	dp[0][0][0] = mod - 1;
	for (int i = 1; i <= n; i++)
	{
		b ^= 1;
		for (int s = 0; s <= sa; s++)
			for (int c = 0; c <= sb; c++)
			{
				dp[b][s][c] = dp[!b][s][c];
				if (s < ai[i])
					continue;
				for (int idx = 0, acc = 1; idx < bi[i] && idx <= c; idx++, acc = 1LL * acc * ai[i] % mod)
					dp[b][s][c] = (0LL + dp[b][s][c] + mod - 1LL * acc * inv[idx] % mod * dp[!b][s - ai[i]][c - idx] % mod) % mod;
			}
	}
	int ans = 0;
	for (int s = 0; s <= sa; s++)
	{
		int unit = fpow(s, mod - 2);
		for (int idx = 0, acc = unit; idx <= sb; idx++, acc = 1LL * acc * unit % mod)
			ans = (0LL + ans + 1LL * fac[idx] * acc % mod * dp[b][s][idx] % mod) % mod;
	}
	ans = 1LL * ans * sa % mod, printf("%d\n", ans);
	return 0;
}
