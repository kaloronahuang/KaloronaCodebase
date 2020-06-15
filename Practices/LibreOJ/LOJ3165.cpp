// LOJ3165.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 19, MAX_M = (MAX_N - 1) * MAX_N >> 1, mod = 998244353;

int n, m, ui[MAX_M], vi[MAX_M], f[1 << MAX_N];
bool valid[1 << MAX_N];

int sgn(int x) { return (x & 1) ? mod - 1 : 1; }

int main()
{
	memset(valid, true, sizeof(valid));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &ui[i], &vi[i]), ui[i]--, vi[i]--;
	for (int stat = 0; stat < (1 << n); stat++)
		for (int i = 1; i <= m; i++)
			if ((stat & (1 << ui[i])) && (stat & (1 << vi[i])))
			{
				valid[stat] = false;
				break;
			}
	f[0] = 1;
	for (int stat = 1; stat < (1 << n); stat++)
		for (int sub = stat; sub; sub = (sub - 1) & stat)
			if (valid[sub])
				f[stat] = (0LL + f[stat] + 1LL * sgn(__builtin_popcount(sub) + 1) * f[stat ^ sub] % mod) % mod;
	printf("%lld\n", 1LL * f[(1 << n) - 1] * m % mod * ((mod + 1) >> 1) % mod);
	return 0;
}
