// card.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;

int n, ai[MAX_N];
ll pre[MAX_N], dp[MAX_N];

void fileIO()
{
	freopen("card.in", "r", stdin);
	freopen("card.out", "w", stdout);
}

int main()
{
	fileIO();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &ai[i]), pre[i] = pre[i - 1] + ai[i];
	ll dp_max = 0;
	for (int i = 2; i <= n; i++)
	{
		dp[i] = dp_max + pre[i];
		// cout << dp[i] << " " << pre[i] << " " << dp_max << endl;
		dp_max = max(dp_max, dp[i]);
	}
	printf("%lld\n", *max_element(dp, dp + 1 + n));
	return 0;
}
