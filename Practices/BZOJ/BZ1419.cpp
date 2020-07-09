// BZ1419.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int rt, bt;
double dp[2][MAX_N];

int main()
{
	scanf("%d%d", &rt, &bt);
	for (int i = 1; i <= rt; i++)
		dp[0][i] = i;
	for (int i = 1; i <= bt; i++)
		for (int j = 1; j <= rt; j++)
		{
			dp[i & 1][j] = max(0.0, 1.0 * j / (i + j) * (dp[i & 1][j - 1] + 1.0) + 1.0 * i / (i + j) * (dp[!(i & 1)][j] - 1.0));
		}
	double ans = dp[bt & 1][rt];
	printf("%d.", int(ans));
	ans -= int(ans);
	for (int i = 1; i <= 6; i++)
		ans *= 10, printf("%d", int(ans)), ans -= int(ans);
	puts("");
	return 0;
}
