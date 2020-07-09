// CF653G.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, mod = 1e9 + 7;

int n, ai[MAX_N], ptot, pid[MAX_N], fac[MAX_N], fac_inv[MAX_N], inv[MAX_N], pre[MAX_N];
vector<int> pidx[MAX_N];

void initialize()
{
	for (int i = fac[0] = 1; i < MAX_N; i++)
		fac[i] = 1LL * fac[i - 1] * i % mod;
	inv[0] = inv[1] = fac_inv[0] = 1;
	for (int i = 2; i < MAX_N; i++)
		inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 1; i < MAX_N; i++)
		fac_inv[i] = 1LL * fac_inv[i - 1] * inv[i] % mod;
}

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

void factorize(int x)
{
	int acc = x;
	for (int i = 2; 1LL * i * i <= acc; i++)
		if (acc % i == 0)
		{
			if (pid[i] == 0)
				pid[i] = ++ptot;
			int idxcnt = 0;
			while (acc % i == 0)
				idxcnt++, acc /= i;
			pidx[pid[i]].push_back(idxcnt);
		}
	if (acc > 1)
	{
		if (pid[acc] == 0)
			pid[acc] = ++ptot;
		pidx[pid[acc]].push_back(1);
	}
}

int main()
{
	initialize(), scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &ai[i]), factorize(ai[i]);
	pre[0] = binomial(n - 1, 0);
	for (int i = 1; i <= n - 1; i++)
		pre[i] = (0LL + pre[i - 1] + binomial(n - 1, i)) % mod;
	int ans = 0;
	for (int ptr = 1; ptr <= ptot; ptr++)
	{
		sort(pidx[ptr].begin(), pidx[ptr].end());
		int rest0 = n - pidx[ptr].size();
		for (int i = 0, siz = pidx[ptr].size(); i < siz; i++)
		{
			rest0++, ans = (0LL + ans + 1LL * pidx[ptr][i] * ((0LL + (rest0 == 1 ? 0 : pre[rest0 - 2])	+ pre[rest0 - 1] + mod - pre[n - 1]) % mod) % mod) % mod;
		}
	}
	printf("%d\n", ans);
	return 0;
}
