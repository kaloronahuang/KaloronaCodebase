// D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 550;
const ll INF = 1e18;

int n, ai[MAX_N][MAX_N];
ll pre[MAX_N][MAX_N], dp[MAX_N][MAX_N], cost[MAX_N][MAX_N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j)
				scanf("%d", &ai[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			pre[i][j] = ai[i][j] + pre[i][j - 1];
	for (int i = 0; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			dp[i][j] = INF;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			for (int k = i; k <= j; k++)
				cost[i][j] += pre[k][j] - pre[k][k];
	for (int i = 1; i <= n; i++)
		dp[0][i] = cost[1][i];
	for (int i = 0; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
		{
			ll acc = dp[i][j];
			for (int k = j + 1; k <= n; k++)
				acc += pre[k][i], dp[j][k] = min(dp[j][k], acc + cost[j + 1][k]);
		}
	ll ans = INF;
	for (int i = 0; i <= n - 1; i++)
		ans = min(ans, dp[i][n]);
	printf("%lld\n", ans);
	return 0;
}
