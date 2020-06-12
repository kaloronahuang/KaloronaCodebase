// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200;

int n, m, c, wi[MAX_N];
bool mp[55][MAX_N][MAX_N];

struct matrix
{
	bool mat[MAX_N][MAX_N];

	void clear() { memset(mat, 0, sizeof(mat)); }

	bool *operator[](const int &rhs) { return mat[rhs]; }

	matrix operator*(const matrix &rhs)
	{
		matrix ret;
		ret.clear();
		static bitset<MAX_N> bA[MAX_N], bB[MAX_N];
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				bA[i][j] = mat[i][j];
				bB[i][j] = rhs.mat[j][i];
			}
		for (int i = 1; i <= n; i++)
			if (bA[i].any())
				for (int j = 1; j <= n; j++)
					ret[i][j] = (bA[i] & bB[j]).any();
		return ret;
	}

	matrix operator^(const int &rhs)
	{
		int tim = rhs;
		matrix ret, bas = *this;
		ret.clear();
		for (int i = 1; i <= n; i++)
			ret[i][i] = 1;
		while (tim)
		{
			if (tim & 1)
				ret = ret * bas;
			bas = bas * bas;
			tim >>= 1;
		}
		return ret;
	}
} curt, trans;

int main()
{
	scanf("%d%d%d", &n, &m, &c);
	for (int i = 1, u, v, lv; i <= m; i++)
		scanf("%d%d%d", &u, &v, &lv), mp[lv][u][v] = true;
	for (int i = 1; i <= c; i++)
		scanf("%d", &wi[i]);
	curt[1][1] = trans[n][n] = true;
	for (int i = 0; i <= c; i++)
	{
		int diff = (i == c ? n : wi[i + 1] - wi[i]);
		matrix nxt = curt * (trans ^ diff);
		if (nxt[1][n])
		{
			matrix acc = curt;
			for (int j = 1; j <= n; j++)
			{
				acc = acc * trans;
				if (acc[1][n])
					printf("%d\n", j + wi[i]), exit(0);
			}
		}
		else if (i == c)
			puts("Impossible"), exit(0);
		curt = nxt;
		for (int a = 1; a <= n; a++)
			for (int b = 1; b <= n; b++)
				trans[a][b] |= mp[i + 1][a][b];
	}
	return 0;
}
