// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e6 + 200, mod = 998244353;

int fac[MAX_N], fac_inv[MAX_N], inv[MAX_N];

void preprocess()
{
	for (int i = fac[0] = 1; i < MAX_N; i++)
		fac[i] = 1LL * fac[i - 1] * i % mod;
	inv[0] = inv[1] = fac_inv[0] = 1;
	for (int i = 2; i < MAX_N; i++)
		inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 1; i < MAX_N; i++)
		fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
}

int binomial(int n_, int k_) { return (n_ < k_) ? 0 : 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int calc(int n, int m, int o)
{
	int ret = 0;
	for (int i = 0; i <= o; i++)
		if (i % 2 == m % 2)
			ret = (0LL + ret + 1LL * binomial((m - i) / 2 + n - 1, n - 1) * binomial(n, i) % mod) % mod;
	return ret;
}

int main()
{
	int n, m;
	preprocess(), scanf("%d%d", &n, &m);
	printf("%lld\n", (0LL + calc(n, 3 * m, m) + mod - 1LL * n * calc(n, m - 1, m) % mod) % mod);
	return 0;
}
