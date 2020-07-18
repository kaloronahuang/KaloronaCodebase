// pikachu.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e6 + 200, mod = 998244353;

int T, cT, q, nodes[MAX_N][2], ptot, fa[MAX_N], last_time[MAX_N];
int bin[MAX_N], coeff[2], cp[MAX_N][2], dep[MAX_N], ibin[MAX_N];
char str[MAX_N];

void clear(int u)
{
	if (u == 0)
		return;
	// todo - some other coeffs to be removed;
	coeff[0] = (0LL + coeff[0] + mod - cp[u][0]) % mod;
	coeff[1] = (0LL + coeff[1] + mod - cp[u][1]) % mod;
	cp[u][0] = cp[u][1] = 0;
	for (int i = 0; i < 2; i++)
		clear(nodes[u][i]), nodes[u][i] = 0;
}

int main()
{
	/*
	freopen("pikachu.in", "r", stdin);
	freopen("pikachu.out", "w", stdout);
	*/
	scanf("%d", &T);
	for (int i = bin[0] = 1; i < MAX_N; i++)
		bin[i] = 2LL * bin[i - 1] % mod;
	ibin[0] = 1, ibin[1] = (mod + 1) >> 1;
	for (int i = 2; i < MAX_N; i++)
		ibin[i] = 1LL * ibin[i - 1] * ibin[1] % mod;
	while (T--)
	{
		for (int i = 1; i <= ptot; i++)
		{
			nodes[i][0] = nodes[i][1] = fa[i] = last_time[i] = 0;
			cp[i][0] = cp[i][1] = dep[i] = 0;
		}
		ptot = 1, cT = 0, coeff[0] = mod - 1, coeff[1] = 2, dep[1] = 1;
		scanf("%d", &q);
		while (q--)
		{
			int x;
			scanf("%s", str + 1);
			if (str[1] == 'G')
			{
				scanf("%d", &x), cT += x;
				printf("%lld\n", (0LL + 1LL * bin[cT] * coeff[1] % mod + coeff[0]) % mod);
			}
			else
			{
				scanf("%s", str + 1);
				int p = 1, max_node = 1;
				for (int i = 1; str[i]; i++)
				{
					int b = (str[i] == 'R');
					if (last_time[p] > last_time[max_node])
						max_node = p;
					if (nodes[p][b] == 0)
						nodes[p][b] = ++ptot, fa[ptot] = p, dep[ptot] = dep[fa[ptot]] + 1;
					p = nodes[p][b];
				}
				clear(p);
				// remove;
				last_time[p] = cT;
				int seg = dep[p] - dep[max_node], idx = (/* cT */ -(last_time[max_node] + (last_time[max_node] != 0)) - seg + 1);
				int idx2 = /* cT' */ -cT;
				cp[p][1] = (0LL + mod - ((idx > 0) ? bin[idx] : ibin[-idx]) + ((idx2 > 0) ? bin[idx2] : ibin[-idx2])) % mod;
				cp[p][0] = 0;
				coeff[1] = (0LL + coeff[1] + cp[p][1]) % mod;
				coeff[0] = (0LL + coeff[0] + cp[p][0]) % mod;
				// add;
				printf("%lld\n", (0LL + 1LL * bin[cT] * coeff[1] % mod + coeff[0]) % mod);
			}
		}
	}
	return 0;
}