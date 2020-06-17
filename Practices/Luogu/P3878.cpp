// P3878.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 40;

int T, n, vi[MAX_N], bound, ans;

int calc()
{
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i <= bound; i++)
		sum1 += vi[i];
	for (int i = bound + 1; i <= n; i++)
		sum2 += vi[i];
	return abs(sum1 - sum2);
}

void simulatingAnneal()
{
	double Temp = 5000, endTemp = 1e-10, coeff = 0.90;
	while (Temp > endTemp)
	{
		int x = rand() % n + 1, y = rand() % n + 1;
		swap(vi[x], vi[y]);
		int ndiff = calc();
		if (ndiff < ans)
			ans = ndiff;
		else if (exp(-(ndiff - ans) / Temp) < double(rand()) / double(RAND_MAX))
			swap(vi[x], vi[y]);
		Temp *= coeff;
	}
}

int main()
{
	scanf("%d", &T), srand(time(NULL));
	while (T--)
	{
		scanf("%d", &n), bound = n >> 1, ans = 0x7fffffff;
		for (int i = 1; i <= n; i++)
			scanf("%d", &vi[i]);
		int saTot = 1000;
		while (saTot--)
			simulatingAnneal();
		printf("%d\n", ans);
	}
	return 0;
}
