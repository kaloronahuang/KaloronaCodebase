// three_squirrels.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 800100, mod = 1e9 + 7;

int head[MAX_N], current, n, dp[MAX_N];

struct edge
{
	int to, nxt;
} edges[MAX_N * 20];

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

int dfs(int u)
{
	if (dp[u] != -1)
		return dp[u];
	dp[u] = (u == 0) ? 1 : 0;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		dp[u] = (1LL * dp[u] + 1LL * dfs(edges[i].to)) % mod;
	return dp[u];
}

int main()
{
	memset(dp, -1, sizeof(dp));

	freopen("three_squirrels.in", "r", stdin);
	freopen("three_squirrels.out", "w", stdout);

	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1, tmp; i <= n; i++)
	{
		int ki;
		scanf("%d", &ki);
		while (ki--)
			scanf("%d", &tmp), addpath(i, tmp);
	}
	printf("%d", dfs(n));
	return 0;
}
