// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, suf[MAX_N];
char S[MAX_N];

int main()
{
	scanf("%s", S + 1), n = strlen(S + 1);
	long long ans = 0;
	for (int i = n - 1; i >= 1; i--)
	{
		if (i <= n - 2 && S[i] == 'A' && S[i + 1] == 'B' && S[i + 2] == 'C')
			suf[i] = suf[i + 3] + 1, ans += suf[i];
		else if (S[i] == 'B' && S[i + 1] == 'C')
			suf[i] = suf[i + 2] + 1;
		else if (S[i] == 'A')
			suf[i] = suf[i + 1], ans += suf[i];
	}
	printf("%lld\n", ans);
	return 0;
}
