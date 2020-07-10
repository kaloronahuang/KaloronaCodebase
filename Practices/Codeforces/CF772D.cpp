// CF772D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200, mod = 1e9 + 7, RANGE = 1e6;

int n, ai[MAX_N], bin[MAX_N], poly[3][MAX_N], f[MAX_N];

void fwt(int *arr)
{
	for (int step = 1; step < RANGE; step *= 10)
		for (int i = RANGE - 1; i >= 0; i--)
			if ((i / step) % 10 != 0)
				arr[i - step] = (0LL + arr[i - step] + arr[i]) % mod;
}

void ifwt(int *arr)
{
	for (int step = 1; step < RANGE; step *= 10)
		for (int i = 0; i < RANGE; i++)
			if ((i / step) % 10 != 0)
				arr[i - step] = (0LL + arr[i - step] + mod - arr[i]) % mod;
}
				

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &ai[i]), poly[0][ai[i]]++;
		poly[1][ai[i]] = (0LL + poly[1][ai[i]] + ai[i]) % mod;
		poly[2][ai[i]] = (0LL + poly[2][ai[i]] + 1LL * ai[i] * ai[i] % mod) % mod;
	}
	for (int i = bin[0] = 1; i <= RANGE; i++)
		bin[i] = 2LL * bin[i - 1] % mod;
	for (int i = 0; i < 3; i++)
		fwt(poly[i]);
	for (int i = 0; i < RANGE; i++)
	{
		if (poly[0][i] == 0)
			continue;
		if (poly[0][i] == 1)
		{
			f[i] = poly[2][i];
			continue;
		}
		f[i] = 1LL * bin[poly[0][i] - 2] * ((0LL + 1LL * poly[1][i] * poly[1][i] % mod + poly[2][i]) % mod) % mod;
	}
	ifwt(f);
	long long ans = 0;
	for (int i = 0; i < RANGE; i++)
		ans ^= 1LL * i * f[i];
	printf("%lld\n", ans);
	return 0;
}
