// PPARTS.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200, mod = 998244353, G = 3;

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

const int invG = fpow(G, mod - 2);

namespace Polynomial
{

	int poly_bit, poly_siz, rev[MAX_N];

	void ntt_prepare(int len)
	{
		poly_bit = 0, poly_siz = 1;
		while (poly_siz <= len)
			poly_bit++, poly_siz <<= 1;
	}
	
	void ntt_initialize()
	{
		for (int i = 0; i < poly_siz; i++)
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
	}
	
	void ntt(int *arr, int dft)
	{
		for (int i = 0; i < poly_siz; i++)
			if (i < rev[i])
				swap(arr[i], arr[rev[i]]);
		for (int step = 1; step < poly_siz; step <<= 1)
		{
			int omega_n = fpow(dft == 1 ? G : invG, (mod + 1) / (step << 1));
			for (int j = 0; j < poly_siz; j += (step << 1))
			{
				int omega_nk = 1;
				for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_nk * omega_n % mod)
				{
					int t = 1LL * arr[k + step] * omega_nk % mod;
					arr[k + step] = (0LL + arr[k] + mod - t) % mod, arr[k] = (0LL + arr[k] + t) % mod;
				}
			}
		}
		if (dft == -1)
		{
			int inv = fpow(poly_siz, mod - 2);
			for (int i = 0; i < poly_siz; i++)
				arr[i] = 1LL * arr[i] * inv % mod;
		}
	}
	
	void poly_diff(int *src, int *dst, int deg)
	{
		for (int i = 0; i < deg - 1; i++)
		    dst[i] = 1LL * src[i + 1] * (i + 1) % mod;
		dst[deg - 1] = 0;
	}

	void poly_sigma(int *src, int *dst, int deg)
	{
		for (int i = 1; i < deg; i++)
		    dst[i] = 1LL * src[i - 1] * fpow(i, mod - 2) % mod;
		dst[0] = 0;
	}
	
	void poly_inverse(int deg, int *src, int *dst)
	{
		if (deg == 1)
			return (void)(dst[0] = fpow(src[0], mod - 2));
		static int invTmp[MAX_N];
		poly_inverse((deg + 1) >> 1, src, dst);
		ntt_prepare(deg << 1), ntt_initialize();
		for (int i = 0; i < deg; i++)
			invTmp[i] = src[i];
		for (int i = deg; i < poly_siz; i++)
			invTmp[i] = 0;
		ntt(invTmp, 1), ntt(dst, 1);
		for (int i = 0; i < poly_siz; i++)
			dst[i] = 1LL * dst[i] * ((2LL + mod - 1LL * invTmp[i] * dst[i] % mod) % mod) % mod;
		ntt(dst, -1);
		for (int i = deg; i < poly_siz; i++)
			dst[i] = 0;
	}
	
	void poly_ln(int deg, int *src, int *dst)
	{
		static int src_tmp[MAX_N], lower_tmp[MAX_N];
		ntt_prepare(deg << 1);
		for (int i = 0; i < poly_siz; i++)
			src_tmp[i] = lower_tmp[i] = 0;
		poly_diff(src, src_tmp, deg), poly_inverse(deg, src, lower_tmp);
		for (int i = deg; i < poly_siz; i++)
			src_tmp[i] = lower_tmp[i] = 0;
		ntt_prepare(deg << 1), ntt_initialize();
		ntt(src_tmp, 1), ntt(lower_tmp, 1);
		for (int i = 0; i < poly_siz; i++)
			src_tmp[i] = 1LL * src_tmp[i] * lower_tmp[i] % mod;
		ntt(src_tmp, -1);
		for (int i = deg; i < poly_siz; i++)
			dst[i] = 0;
		poly_sigma(src_tmp, dst, deg);
	}
	
	void poly_exp(int deg, int *src, int *dst)
	{
		static int tmp_ln[MAX_N];
		if (deg == 1)
			return (void)(dst[0] = 1);
		poly_exp((deg + 1) >> 1, src, dst), poly_ln(deg, dst, tmp_ln);
		ntt_prepare(deg << 1), ntt_initialize();
		for (int i = 0; i < deg; i++)
			tmp_ln[i] = (0LL + src[i] + mod - tmp_ln[i]) % mod;
		for (int i = deg; i < poly_siz; i++)
			tmp_ln[i] = 0;
		tmp_ln[0] = (0LL + tmp_ln[0] + 1) % mod;
		ntt(dst, 1), ntt(tmp_ln, 1);
		for (int i = 0; i < poly_siz; i++)
			dst[i] = 1LL * dst[i] * tmp_ln[i] % mod;
		ntt(dst, -1);
		for (int i = deg; i < poly_siz; i++)
			dst[i] = tmp_ln[i] = 0;
	}

}

int n, m, f[MAX_N], h[MAX_N], o[MAX_N], inv[MAX_N];

int main()
{
	scanf("%d%d", &n, &m), inv[0] = inv[1] = 1;
	for (int i = 2; i < MAX_N; i++)
		inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		if (b > 0 && 1LL * a * (b + 1) <= n)
			f[a * (b + 1)] = (0LL + f[a * (b + 1)] + mod - 1) % mod;
		if (a <= n)
			f[a] = (0LL + f[a] + 1) % mod;
	}
	for (int i = 1; i <= n; i++)
		if (f[i])
			for (int j = 1; 1LL * i * j <= n; j++)
				h[i * j] = (0LL + h[i * j] + 1LL * f[i] * inv[j] % mod) % mod;
	Polynomial::poly_exp(n + 1, h, o);
	for (int i = 1; i <= n; i++)
		printf("%d ", o[i]);
	puts("");
	return 0;
}
