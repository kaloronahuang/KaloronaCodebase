// P5203.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

int n, m, head[MAX_N], current, fa[20][MAX_N], dep[MAX_N];
int xi[MAX_N], yi[MAX_N], lcas[MAX_N], bucket[MAX_N];
long long ans;

struct edge
{
	int to, nxt;
} edges[MAX_N << 1];

map<pair<int, int>, int> mp;

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

void dfs(int u, int fat)
{
	dep[u] = dep[fat] + 1, fa[0][u] = fat;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fat)
			dfs(edges[i].to, u);
}

int getLCA(int x, int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	for (int i = 19; i >= 0; i--)
		if (dep[fa[i][x]] >= dep[y])
			x = fa[i][x];
	if (x == y)
		return x;
	for (int i = 19; i >= 0; i--)
		if (fa[i][x] != fa[i][y])
			x = fa[i][x], y = fa[i][y];
	return fa[0][x];
}

void refresh(int u)
{
	bucket[u] += bucket[fa[0][u]];
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa[0][u])
			refresh(edges[i].to);
}

int under(int x, int lca)
{
	if (x == lca)
		return -1;
	for (int i = 19; i >= 0; i--)
		if (dep[fa[i][x]] > dep[lca])
			x = fa[i][x];
	return x;
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i < n; i++)
		scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
	dfs(1, 0);
	for (int i = 1; i <= 19; i++)
		for (int j = 1; j <= n; j++)
			fa[i][j] = fa[i - 1][fa[i - 1][j]];
	for (int i = n; i <= m; i++)
	{
		scanf("%d%d", &xi[i], &yi[i]), lcas[i] = getLCA(xi[i], yi[i]);
		int ux = under(xi[i], lcas[i]), uy = under(yi[i], lcas[i]);
		if (ux != -1)
			ans -= (++bucket[ux]);
		if (uy != -1)
			ans -= (++bucket[uy]);
		if (ux != -1 && uy != -1)
			ans -= (mp[make_pair(min(ux, uy), max(ux, uy))]++);
	}
	refresh(1);
	for (int i = n; i <= m; i++)
		ans += bucket[xi[i]] + bucket[yi[i]] - (bucket[lcas[i]] << 1);
	printf("%lld", ans);
	return 0;
}
