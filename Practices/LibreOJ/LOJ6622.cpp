// LOJ6622.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 961661263, MAX_N = 75;

int n, m, mp[MAX_N][MAX_N][1 << 12], poly_siz, poly_bit, poly[1 << 12], tmp[MAX_N][MAX_N];
char str[MAX_N];

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

const int inv2 = fpow(2, mod - 2);

int det(int (*mat)[MAX_N])
{
    int ret = 1;
    for (int i = 1; i <= n - 1; i++)
    {
        int key = 0;
        for (int j = i; j <= n - 1 && key == 0; j++)
            if (mat[j][i] > 0)
                key = j;
        if (key != i)
        {
            if (key == 0)
                return 0;
            ret = mod - ret;
            for (int j = 1; j <= n - 1; j++)
                swap(mat[i][j], mat[key][j]);
        }
        int inv = fpow(mat[i][i], mod - 2);
        for (int j = i + 1; j <= n - 1; j++)
        {
            int rate = 1LL * mat[j][i] * inv % mod;
            for (int k = i; k <= n - 1; k++)
                mat[j][k] = (0LL+ mat[j][k] + mod - 1LL * rate * mat[i][k] % mod) % mod;
        }
    }
    for (int i = 1; i <= n - 1; i++)
        ret = 1LL * ret * mat[i][i] % mod;
    return ret;
}

void fwt(int *arr, int dft)
{
	for (int step = 1, bi = 1; step < poly_siz; step <<= 1, bi++)
		for (int j = 0; j + step < poly_siz; j += (step << 1))
			for (int k = j; k < j + step; k++)
			{
				int &a = arr[k], &b = arr[k + step];
				int u = arr[k], v = arr[k + step];
				if (str[bi] == '&')
					a = (0LL + a + mod + 1LL * dft * b % mod) % mod;
				else if (str[bi] == '|')
					b = (0LL + b + mod + 1LL * dft * a % mod) % mod;
				else
					a = (0LL + u + v) % mod, b = (0LL + u + mod - v) % mod;
			}
	if (dft == -1)
	{
		int idxcnt = 0;
		for (int i = 1; i <= poly_bit; i++)
			idxcnt += str[i] == '^';
		int inv = fpow(inv2, idxcnt);
		for (int i = 0; i < poly_siz; i++)
			arr[i] = 1LL * arr[i] * inv % mod;
	}
}

int main()
{
	scanf("%d%d%s", &n, &m, str + 1), poly_bit = strlen(str + 1), poly_siz = 1 << poly_bit;
	for (int i = 1, u, v, w; i <= m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		mp[u][v][w] = (0LL + mp[u][v][w] + mod - 1) % mod;
		mp[v][u][w] = (0LL + mp[v][u][w] + mod - 1) % mod;
		mp[u][u][w]++, mp[v][v][w]++;
	}
	for (int i = 1; i <= n - 1; i++)
		for (int j = 1; j <= n - 1; j++)
			fwt(mp[i][j], 1);
	for (int w = 0; w < (1 << poly_bit); w++)
	{
		for (int i = 1; i <= n - 1; i++)
			for (int j = 1; j <= n - 1; j++)
				tmp[i][j] = mp[i][j][w];
		poly[w] = det(tmp);
	}
	fwt(poly, -1);
	for (int i = poly_siz - 1; i >= 0; i--)
		if (poly[i])
			printf("%d\n", i), exit(0);
	puts("-1");
	return 0;
}
