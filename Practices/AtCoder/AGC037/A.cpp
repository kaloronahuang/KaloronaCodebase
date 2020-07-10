// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, dp[MAX_N][2];
char str[MAX_N];

int main()
{
	scanf("%s", str + 1), n = strlen(str + 1);
	for (int i = 1; i <= n; i++)
	{
		if (str[i] != str[i - 1])
			dp[i][0] = max(dp[i][0], dp[i - 1][0] + 1);
		if (i >= 2)
		{
			dp[i][0] = max(dp[i][0], dp[i - 1][1] + 1);
			dp[i][1] = dp[i - 2][0] + 1;
			if (i >= 4 && str[i] != str[i - 2] && str[i - 1] != str[i - 3])
				dp[i][1] = max(dp[i][1], dp[i - 2][1] + 1);
		}
	}
	printf("%d\n", max(dp[n][0], dp[n][1]));
	return 0;
}
