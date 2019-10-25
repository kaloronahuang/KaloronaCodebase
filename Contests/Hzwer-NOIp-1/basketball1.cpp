// basketball1.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1030, mod = 1e9 + 7;

int prefix_xor[MAX_N][MAX_N], suffix_and[MAX_N][MAX_N];
int n, seq[MAX_N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &seq[i]);
	for (int i = 1; i <= n; i++)
	{
		prefix_xor[i][seq[i]] = 1;
		for (int j = 0; j < 1024; j++)
			prefix_xor[i][j] = (1LL * prefix_xor[i][j] + 1LL * prefix_xor[i - 1][j ^ seq[i]]) % mod;
		for (int j = 0; j < 1024; j++)
			prefix_xor[i][j] = (1LL * prefix_xor[i - 1][j] + 1LL * prefix_xor[i][j]) % mod;
	}
	for (int i = n; i >= 1; i--)
	{
		suffix_and[i][seq[i]] = 1; 
		for (int j = 0; j < 1024; j++)
			suffix_and[i][j & seq[i]] = (1LL * suffix_and[i][j & seq[i]] + 1LL * suffix_and[i + 1][j]) % mod;
		for (int j = 0; j < 1024; j++)
			suffix_and[i][j] = (1LL * suffix_and[i + 1][j] + 1LL * suffix_and[i][j]) % mod;
	}
	int ans = 0;
	for (int i = 2; i <= n; i++)
		for (int j = 0; j < 1024; j++)
			ans = (1LL * ans + 1LL * prefix_xor[i - 1][j] * (suffix_and[i][j] - suffix_and[i + 1][j]) % mod) % mod;
	printf("%d", ans); 
	return 0;
}
