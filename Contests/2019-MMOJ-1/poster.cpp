// poster.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2030, mod = 1e6 + 7;

int dp[MAX_N][MAX_N][5], n, m;
char mp[MAX_N][MAX_N];

int getDigit(char ch) 
{
	if (ch == 'N')
		return 1;
	if (ch == 'O')
		return 2;
	if (ch == 'I')
		return 3;
	if (ch == 'P')
		return 4;
}

int main()
{
	freopen("poster.in", "r", stdin);
	freopen("poster.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", mp[i] + 1);
	dp[1][1][0] = 1;
	if (mp[1][1] == 'N')
		dp[1][1][1] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			if (i == 1 && j == 1)
				continue;
			dp[i][j][0] = (dp[i - 1][j][0] + dp[i][j - 1][0] + mod - dp[i - 1][j - 1][0]) % mod;
			for (int k = 1; k <= 4; k++)
			{
				dp[i][j][k] = (dp[i - 1][j][k] + dp[i][j - 1][k] + mod - dp[i - 1][j - 1][k]) % mod;
				if (k == getDigit(mp[i][j]))
					dp[i][j][k] = (dp[i][j][k] + dp[i][j - 1][k - 1] + dp[i - 1][j][k - 1] + mod - dp[i - 1][j - 1][k - 1]) % mod;
			}
		}
	printf("%d", dp[n][m][4]);
	return 0;
}
