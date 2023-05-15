// BSGS.cpp
#include <bits/stdc++.h>

using namespace std;

int mod, a, b;

map<int, int> ump;

int fpow(int bas, int tim)
{
	int ret = 1;
	while (tim)
	{
		if (tim & 1)
			ret = 1LL * ret * bas % mod;
		bas = 1LL * bas * bas % mod;
		tim >>= 1;
	}
	return ret;
}

int main()
{
	scanf("%d%d%d", &mod, &a, &b);
	int m = sqrt(mod), acc = b;
	for (int i = 0; i < m; i++, acc = 1LL * acc * a % mod)
		if (ump.count(acc) == 0)
			ump[acc] = i;
	int unit = fpow(a, m);
	acc = 1;
	for (int i = 0; i < m; i++, acc = 1LL * acc * unit % mod)
		if (ump.count(acc))
		{
			printf("%lld\n", (1LL * i * m - ump[acc] + mod - 1) % (mod - 1));
			return 0;
		}
	puts("no solution");
	return 0;
}
