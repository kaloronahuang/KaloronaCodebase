// tree.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 19491001, rev_opt[4] = {0, 2, 1, 4};

int head[MAX_N], current, upweight[MAX_N], fa[20][MAX_N], dep[MAX_N];
int n, m, vi[MAX_N];

struct group
{
	int a, b;
	group() {}
	group(int a_, int b_) : a(a_), b(b_) {}
} trs_up[MAX_N], trs_down[MAX_N];

struct edge
{
	int to, nxt, weight;
} edges[MAX_N << 1];

int sta[30], tail;

int read()
{
	char ch = getchar();
	int x = 0, f = 1;
	while (!isdigit(ch))
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch))
		x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
	return f * x;
}

void addpath(int src, int dst, int weight)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	edges[current].weight = weight, head[src] = current++;
}

int quick_pow(int bas, int tim)
{
	int ans = 1;
	while (tim)
	{
		if (tim & 1)
			ans = 1LL * ans * bas % mod;
		bas = 1LL * bas * bas % mod;
		tim >>= 1;
	}
	return ans;
}

int getLCA(int x, int y)
{
	bool flag = false;
	if (dep[x] < dep[y])
		swap(x, y), flag = true;
	for (int i = 19; i >= 0; i--)
		if (dep[fa[i][x]] >= dep[y])
			x = fa[i][x];
	if (x == y)
		return x;
	if (flag)
		swap(x, y);
	for (int i = 19; i >= 0; i--)
		if (fa[i][x] != fa[i][y])
			x = fa[i][x], y = fa[i][y];
	return fa[0][x];
}

void dfs(int u)
{
	dep[u] = dep[fa[0][u]] + 1;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa[0][u])
		{
			fa[0][edges[i].to] = u, upweight[edges[i].to] = edges[i].weight;
			trs_up[edges[i].to] = trs_up[u], trs_down[edges[i].to] = trs_down[u];
			if (edges[i].weight == 1)
			{
				trs_down[edges[i].to].b = (trs_down[edges[i].to].b + vi[edges[i].to]) % mod;
				trs_up[edges[i].to].b = (1LL * trs_up[u].a * vi[u] + trs_up[u].b) % mod;
			}
			else if (edges[i].weight == 2)
			{
				trs_down[edges[i].to].b = (trs_down[edges[i].to].b - vi[edges[i].to] + mod) % mod;
				trs_up[edges[i].to].b = (1LL * trs_up[edges[i].to].b - 1LL * trs_up[u].a * vi[u] % mod + mod) % mod;
			}
			else
			{
				trs_down[edges[i].to].a = 1LL * trs_down[u].a * vi[edges[i].to] % mod;
				trs_down[edges[i].to].b = 1LL * trs_down[u].b * vi[edges[i].to] % mod;
				trs_up[edges[i].to].a = 1LL * trs_up[edges[i].to].a * vi[u] % mod;
			}
			dfs(edges[i].to);
		}
}

int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	memset(head, -1, sizeof(head));
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		vi[i] = (read() + mod) % mod;
	for (int i = 1, u, v, w; i <= n - 1; i++)
		scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
	trs_up[1] = trs_down[1] = group(1, 0);
	dfs(1);
	for (int i = 1; i <= 19; i++)
		for (int j = 1; j <= n; j++)
			fa[i][j] = fa[i - 1][fa[i - 1][j]];
	while (m--)
	{
		int x = read(), y = read(), lca = getLCA(x, y);
		int A = 1LL * trs_up[x].a * quick_pow(trs_up[lca].a, mod - 2) % mod;
		int B = 1LL * (trs_up[x].b - trs_up[lca].b + mod) % mod * quick_pow(trs_up[lca].a, mod - 2) % mod;
		if (x == lca)
			A = 1, B = 0;
		int C = 1LL * trs_down[y].a * quick_pow(trs_down[lca].a, mod - 2) % mod;
		int D = (trs_down[y].b - 1LL * trs_down[lca].b * C % mod) % mod;
		if (y == lca)
			C = 1, D = 0;
		A = 1LL * A * C % mod;
		B = (1LL * B * C % mod + D) % mod;
		long long ans = (1LL * A * vi[x] % mod + B + mod) % mod;
		while (ans < 0)
			ans += mod;
		printf("%lld\n", ans);
	}
	return 0;
}
