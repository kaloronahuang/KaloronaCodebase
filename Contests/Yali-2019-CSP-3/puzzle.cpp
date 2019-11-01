// puzzle.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e3 + 200, mod = 998244353;

int C[MAX_N][MAX_N], n, q;

int main()
{
	freopen("puzzle.in", "r", stdin);
	freopen("puzzle.out", "w", stdout);
	C[1][0] = C[1][1] = 1;
	for (int i = 2; i < MAX_N; i++)
	{
		C[i][i] = C[i][0] = 1;
		for (int j = 1; j < i; j++)
			C[i][j] = (1LL * C[i - 1][j - 1] + 1LL * C[i - 1][j]) % mod;
	}
	for (int i = 1; i < MAX_N; i++)
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i][j] + C[i][j - 1]) % mod;
	scanf("%d", &q);
	while (q--)
	{
		int ans = 0;
		scanf("%d", &n);
		for (int i = 1; i <= (n >> 1); i++)
			ans = (1LL * ans + (C[n - i][n - i] - C[n - i][i - 1] + mod) % mod) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
