// gcd.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 5500;

int n, m;
ll seq[MAX_N], prefix[MAX_N], int_gcd[MAX_N][MAX_N], int_ans[MAX_N][MAX_N];

inline ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
	freopen("gcd.in", "r", stdin);
	freopen("gcd.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &seq[i]), prefix[i] = prefix[i - 1] + seq[i];
		int_gcd[i][i] = seq[i], int_ans[i][i] = seq[i] * seq[i];
	}
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
		{
			int_gcd[i][j] = gcd(int_gcd[i][j - 1], seq[j]);
			int_ans[i][j] = max(int_ans[i][j - 1], (prefix[j] - prefix[i - 1]) * int_gcd[i][j]);
		}
	while (m--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		ll ans = 0;
		for (int i = l; i <= r; i++)
			ans = max(ans, int_ans[i][r]);
		printf("%lld\n", ans);
	}
	return 0;
}
