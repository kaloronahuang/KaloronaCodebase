// SP104.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20;
const double eps = 1e-8;

int T, n, m;
double mat[MAX_N][MAX_N];

int sig(int x) { return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1); }

double det()
{
	double ret = 1;
	for (int i = 1; i <= n - 1; i++)
	{
		int key = i;
		for (int j = i + 1; key == 0 && j <= n - 1; j++)
			if (sig(mat[j][i] - mat[key][i]) < 0)
				key = j;
		if (key != i)
			for (int j = 1; j <= n - 1; j++)
				swap(mat[key][j], mat[i][j]);
		if (fabs(mat[i][i]) < eps)
			return 0;
		for (int j = i + 1; j <= n - 1; j++)
			if (i != j)
			{
				double rate = mat[j][i] / mat[i][i];
				for (int k = i; k <= n; k++)
					mat[j][k] -= 1LL * rate * mat[i][k];
			}
	}
	for (int i = 1; i <= n - 1; i++)
		ret *= mat[i][i];
	return ret;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		memset(mat, 0, sizeof(mat));
		scanf("%d%d", &n, &m);
		for (int i = 1, u, v; i <= m; i++)
			scanf("%d%d", &u, &v), mat[u][u]++, mat[v][v]++, mat[u][v]--, mat[v][u]--;
		printf("%.0lf\n", abs(det()));
	}
	return 0;
}
