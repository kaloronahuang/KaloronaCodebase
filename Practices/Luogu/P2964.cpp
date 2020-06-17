// P2964.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, ci[MAX_N], dp[MAX_N][MAX_N];

int main()
{
	scanf("%d", &n);
	for (int i = n; i >= 1; i--)
		scanf("%d", &ci[i]);
	for (int i = 1; i <= n; i++)
		ci[i] += ci[i - 1];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			dp[i][j] = max(dp[i][j - 1], ci[i] - dp[i - j][min(i - j, j << 1)]);
	printf("%d\n", dp[n][2]);
	return 0;
}
