// NOMURA2020C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, seq[MAX_N];
ll leaves, ans;

int main()
{
	scanf("%d", &n);
	for (int i = 0; i <= n; i++)
		scanf("%d", &seq[i]), leaves += seq[i];
	if (n == 0)
		if (seq[0] == 1)
			puts("1"), exit(0);
		else
			puts("-1"), exit(0);
	if (seq[0] != 0)
		puts("-1"), exit(0);
	ll bas = ans = 1;
	for (int i = 1; i <= n; i++)
	{
		bas <<= 1;
		if (seq[i] > bas)
			puts("-1"), exit(0);
		ans += min(bas, leaves);
		bas = min(bas, leaves) - seq[i];
		leaves -= seq[i];
	}
	printf("%lld\n", ans);
	return 0;
}
