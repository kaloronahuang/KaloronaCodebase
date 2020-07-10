// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, mod = 998244353;

int n, cnt[3], ans = 1;
char str[MAX_N];

int encode(char c) { return c == 'R' ? 0 : (c == 'G' ? 1 : 2); }

int main()
{
	scanf("%d%s", &n, str + 1), n *= 3;
	for (int i = 1; i <= n; i++)
	{
		int x[3], y[3], opt = encode(str[i]);
		memcpy(x, cnt, sizeof(x)), cnt[opt]++;
		memcpy(y, cnt, sizeof(y));
		sort(x, x + 3), sort(y, y + 3);
		if (y[2] != x[2])
			continue;
		else if (y[0] != x[0])
			ans = 1LL * ans * (x[1] - x[0]) % mod;
		else
			ans = 1LL * ans * (x[2] - x[1]) % mod;
	}
	for (int i = 1; i <= n / 3; i++)
		ans = 1LL * ans * i % mod;
	printf("%d\n", ans);
	return 0;
}
