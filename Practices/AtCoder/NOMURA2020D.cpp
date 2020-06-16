// NOMURA2020D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 1e9 + 7;

int n, fa[MAX_N], siz[MAX_N], mem[MAX_N], f[MAX_N], m;

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

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
		scanf("%d", &fa[i]), mem[i] = i, siz[i] = 1;
	for (int i = 1; i <= n; i++)
		if (fa[i] > 0)
		{
			int fx = find(i), fy = find(fa[i]);
			if (fx != fy)
				siz[fy] += siz[fx], mem[fx] = fy;
		}
		else
			m++;
	int ans = 1LL * n * fpow(n - 1, m) % mod;
	f[0] = 1;
	for (int i = 1; i <= n; i++)
		if (i == find(i))
			if (fa[i] == -1)
				for (int j = n; j >= 1; j--)
					f[j] = (0LL + f[j] + 1LL * f[j - 1] * siz[i] % mod) % mod;
			else
				ans = (0LL + ans + mod - fpow(n - 1, m)) % mod;
	f[1] = (0LL + f[1] + mod - m) % mod;
	int acc = 1;
	for (int i = 1; i <= m; acc = 1LL * acc * i % mod, i++)
		ans = (0LL + ans + mod - 1LL * f[i] * fpow(n - 1, m - i) % mod * acc % mod) % mod;
	printf("%d\n", ans);
	return 0;
}
