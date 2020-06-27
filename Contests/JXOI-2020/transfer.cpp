// transfer.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_M = 23, MAX_R = 1.4e6;

int n, m, cost, si[MAX_N], mp[MAX_M][MAX_M], trans[2][MAX_R][MAX_M], dp[1 << MAX_M], gcnt, stats[2][MAX_R];

void fileIO()
{
	freopen("transfer.in", "r", stdin);
	freopen("transfer.out", "w", stdout);
}

int handler()
{
	for (int i = 1; i < (1 << m); i++)
		dp[i] = 0x7fffffff;
	for (int i = 1; i < n; i++)
		if (si[i] != si[i + 1])
			mp[si[i]][si[i + 1]]++;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			trans[0][0][j] += mp[i][j] * cost - mp[j][i];
	int tot = 0, c = 0;
	for (int i = 1; i <= m; i++)
	{
		tot = -1, c ^= 1;
		for (int pre = 0; pre <= gcnt; pre++)
			for (int j = 0; j < m; j++)
				if (!(stats[!c][pre] >> j))
				{
					stats[c][++tot] = stats[!c][pre] | (1 << j);
					for (int k = 0; k < m; k++)
						trans[c][tot][k] = trans[!c][pre][k] + mp[j][k] * (1 - cost) + mp[k][j] * (1 + cost);
				}
		for (int j = 0; j <= gcnt; j++)
			for (int k = 0; k < m; k++)
				if (!(stats[!c][j] & (1 << k)))
					dp[stats[!c][j] | (1 << k)] = min(dp[stats[!c][j] | (1 << k)], dp[stats[!c][j]] + trans[!c][j][k] * i);
		gcnt = tot;
	}
	/*
	for (int i = 1; i < n; i++)
		if (si[i] != si[i + 1])
		{
			// preprocess the coefficient;
			// pos_{s_i} < pos_{s_{i + 1}};
			coeff[si[i]][si[i + 1]][0]--, coeff[si[i]][si[i + 1]][1]++;
			// pos_{s_{i + 1}} < pos_{s_i};
			coeff[si[i + 1]][si[i]][0] += cost, coeff[si[i + 1]][si[i]][1] += cost;
		}
	for (register int stat = 1; stat < (1 << m); stat++)
	{
		int pos = popcount[stat];
		for (register int i = 0; i < m; i++)
			if (stat & (1 << i))
			{
				register int pre_stat = stat ^ (1 << i), acc = dp[pre_stat];
				for (register int j = 0; j < m; j++)
					if (i != j)
					{
						if (pre_stat & (1 << j))
							// pos_j < pos_i;
							acc += coeff[j][i][1] * pos;
						else
							// pos_i < pos_j;
							acc += coeff[i][j][0] * pos;
					}
				dp[stat] = min(dp[stat], acc);
			}
	}
	*/
	printf("%d\n", dp[(1 << m) - 1]);
	return 0;
}

int main()
{
	// fileIO();
	scanf("%d%d%d", &n, &m, &cost);
	for (int i = 1; i <= n; i++)
		scanf("%d", &si[i]), si[i]--;
	return handler();
}
