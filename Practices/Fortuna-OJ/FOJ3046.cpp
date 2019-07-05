// FOJ3046.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int la, lb, seqA[MAX_N], seqB[MAX_N], dp[MAX_N][MAX_N];

int main()
{
	scanf("%d%d", &la, &lb);
	for(int i = 1;i<=la;i++)
		scanf("%d", &seqA[i]), seqA[i]--;
	for(int i = 1;i<=lb;i++)
		scanf("%d", &seqB[i]), seqB[i]--;
	memset(dp, 0x3f, sizeof(dp));
	dp[la+1][lb+1] = 0;
	
	for(int i = la;i>=1;i--)
		for(int j = lb;j>=1;j--)
			dp[i][j] = min(min(dp[i+1][j+1], dp[i+1][j]), dp[i][j+1])+seqA[i]*seqB[j];
	printf("%d", dp[1][1]);
	return 0;
}
