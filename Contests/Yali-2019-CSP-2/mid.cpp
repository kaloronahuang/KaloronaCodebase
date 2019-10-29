// mid.cpp
#include <bits/stdc++.h>
#define ll __int128_t 

using namespace std;

const int MAX_N = 2e5 + 2000;

int seq[MAX_N], n;
ll dp[MAX_N];

int main()
{
	freopen("mid.in", "r", stdin);
	freopen("mid.out", "w", stdout); 
	int mx = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &seq[i]), mx += seq[i];
	ll std_val = 1;
	std_val <<= n;
	std_val--; 
	std_val >>= 1;
	dp[0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = mx; j >= seq[i]; j--)
			dp[j] += dp[j - seq[i]];
	ll prefix = 0;
	for (int i = 1; i <= mx; i++)
	{
		prefix += dp[i];
		if (prefix > std_val)
			printf("%d", i), exit(0);
	}
	return 0;
}
