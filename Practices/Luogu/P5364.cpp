// P5364.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 35, mod = 1e9 + 7;

ll upper;
int m, bound, binomial[MAX_N][MAX_N];

struct matrix
{
	int mat[MAX_N][MAX_N];
	void clear() { memset(mat, 0, sizeof(mat)); }
	int *operator[](const int &rhs) { return mat[rhs]; }
	matrix operator*(const matrix &rhs)
	{
		matrix ret;
		ret.clear();
		for (int k = 0; k < bound; k++)
			for (int i = 0; i < bound; i++)
				if (mat[i][k])
					for (int j = 0; j < bound; j++)
						if (rhs.mat[k][j])
							ret.mat[i][j] = (0LL + ret.mat[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
		return ret;
	}
	matrix operator^(const ll &rhs)
	{
		ll tim = rhs;
		matrix bas = *this, ret;
		ret.clear();
		for (int i = 0; i < bound; i++)
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
} trans;

int main()
{
	scanf("%lld%d", &upper, &m), binomial[0][0] = 1;
	for (int i = 1; i <= m; i++)
	{
		binomial[i][0] = binomial[i][i] = 1;
		for (int j = 1; j < i; j++)
			binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
	}
	bound = m + 3;
	for (int i = 0; i <= m; i++)
		for (int j = 0; j <= i; j++)
			trans[i][j] = binomial[i][j];
	for (int i = 0; i <= m; i++)
		trans[m + 1][i] = trans[m + 2][i] = binomial[m][i];
	trans[m + 1][m + 2] = 1, trans[m + 2][m + 2] = 2;
	trans = trans ^ upper, printf("%d\n", trans[m + 1][0]);
	return 0;
}
