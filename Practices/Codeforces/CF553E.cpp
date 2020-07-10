// CF553E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55, MAX_E = 220, MAX_T = 2e4 + 200, MAX_P = 2e5 + 20;
const double pi = acos(-1.0);

struct cd
{
	double real, image;
	cd(double x = 0, double y = 0) : real(x), image(y) { }
	cd operator+(const cd& rhs) { return cd(real + rhs.real, image + rhs.image); }
	cd operator*(const cd& rhs) { return cd(real * rhs.real - image * rhs.image, real * rhs.image + image * rhs.real); }
	cd operator-(const cd& rhs) { return cd(real - rhs.real, image - rhs.image); }
} F[MAX_P], G[MAX_P];

int n, m, T, exfee, dist[MAX_N], rev[MAX_P], poly_siz, poly_bit;
double f[MAX_N][MAX_T], g[MAX_E][MAX_T];
bool vis[MAX_N];

struct edge
{
	int u, v, w;
	double prob[MAX_T], suf[MAX_T];
} edges[MAX_E];

void fft_prepare(int len)
{
	poly_siz = 1, poly_bit = 0;
	while (poly_siz <= len)
		poly_siz <<= 1, poly_bit++;
}

void fft_initialize()
{
	for (int i = 0; i < poly_siz; i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1));
}

void fft(cd *arr, int dft)
{
	for (int i = 0; i < poly_siz; i++)
		if (i < rev[i])
			swap(arr[i], arr[rev[i]]);
	for (int step = 1; step < poly_siz; step <<= 1)
	{
		cd omega_n = cd(cos(pi * dft / step), sin(pi * dft / step));
		for (int j = 0; j < poly_siz; j += (step << 1))
		{
			cd omega_nk = cd(1, 0);
			for (int k = j; k < j + step; k++, omega_nk = omega_nk * omega_n)
			{
				cd t = arr[k + step] * omega_nk;
				arr[k + step] = arr[k] - t, arr[k] = arr[k] + t;
			}
		}
	}
	if (dft == -1)
		for (int i = 0; i < poly_siz; i++)
			arr[i].real /= poly_siz;
}

void solve(int l, int r)
{
	if (l == r)
	{
		for (int i = 1; i < n; i++)
			f[i][l] = 1e9;
		for (int i = 1; i <= m; i++)
		{
			g[i][l] += edges[i].suf[T - l + 1] * (dist[edges[i].v] + exfee);
			f[edges[i].u][l] = min(f[edges[i].u][l], g[i][l] + edges[i].w);
		}
		return;
	}
	int mid = (l + r) >> 1;
	solve(mid + 1, r);
	fft_prepare(r - l + r - mid), fft_initialize();
	for (int i = 1; i <= m; i++)
	{
		memset(F, 0, sizeof(cd) * poly_siz), memset(G, 0, sizeof(cd) * poly_siz);
		for (int j = 1; j <= r - l; j++)
			F[r - l - j].real = edges[i].prob[j];
		for (int j = mid + 1; j <= r; j++)
			G[j - mid - 1].real = f[edges[i].v][j];
		fft(F, 1), fft(G, 1);
		for (int j = 0; j < poly_siz; j++)
			F[j] = F[j] * G[j];
		fft(F, -1);
		for (int j = 0; j < mid - l + 1; j++)
			g[i][l + j] += F[r - mid - 1 + j].real;
	}
	solve(l, mid);
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &T, &exfee);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
		for (int j = 1, val; j <= T; j++)
			scanf("%d", &val), edges[i].prob[j] = 1.0 * val / 1e5;
		for (int j = T; j >= 1; j--)
			edges[i].suf[j] = edges[i].prob[j] + edges[i].suf[j + 1];
	}
	// obtaining shortest path;
	memset(dist, 0x3f, sizeof(dist)), dist[n] = 0;
	for (int k = 1; k <= n; k++)
	{
		int u = 0;
		for (int i = 1; i <= n; i++)
			if (!vis[i] && dist[i] < dist[u])
				u = i;
		vis[u] = true;
		for (int i = 1; i <= m; i++)
			if (edges[i].v == u)
				dist[edges[i].u] = min(dist[edges[i].u], dist[u] + edges[i].w);
	}
	solve(0, T), printf("%.6lf\n", f[1][0]);
	return 0;
}
