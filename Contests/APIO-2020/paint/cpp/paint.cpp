// paint.cpp
#include <bits/stdc++.h>
#include "paint.h"

typedef unsigned long long ull;

using namespace std;

const int MAX_N = 1e5 + 200, bitnum = 134, mod1 = 998244353, mod2 = 1e9 + 7;

int f[MAX_N], dp[MAX_N], q[MAX_N];
bool vis[MAX_N];

int minimumInstructions(int n, int m, int k, vector<int> C, vector<int> A, vector<std::vector<int>> B)
{
	memset(dp, 0x3f, sizeof(dp)), dp[0] = 0;
	for (int x = 0; x < m; x++)
		for (int y = 0; y <= n - m; y++)
			if (!vis[y + m])
			{
				bool flag = true;
				for (int b = 0; b < m; b++)
					if (*lower_bound(B[(x + b) % m].begin(), B[(x + b) % m].end(), C[y + b]) != C[y + b])
					{
						flag = false;
						break;
					}
				// cerr << x << " " << y << " : " << flag << endl;
				if (flag)
					vis[y + m] = true; //, cerr << x << " " << y << " " << endl;
			}
	// cerr << n << endl;
	for (int i = 1; i <= n; i++)
		if (vis[i])
		{
			// cerr << i << endl;
			for (int j = i - m; j < i; j++)
				dp[i] = min(dp[i], dp[j] + 1);
		}
	return dp[n] == 0x3f3f3f3f ? -1 : dp[n];
}
