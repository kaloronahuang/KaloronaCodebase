// Hotel.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, head[MAX_N], current, dep[MAX_N], son[MAX_N];
ll ans, *g[MAX_N], *f[MAX_N], dp[MAX_N], *lptr = dp;

struct edge
{
	int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

void dfs(int u, int fa)
{
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa)
		{
			dfs(edges[i].to, u);
			son[u] = dep[son[u]] > dep[son[edges[i].to]] ? son[u] : edges[i].to;
		}
	dep[u] = dep[son[u]] + 1;
}

void calc(int u, int fa)
{
	if (son[u])
		f[son[u]] = f[u] + 1, g[son[u]] = g[u] - 1, calc(son[u], u);
	f[u][0] = 1, ans += g[u][0];
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa && son[u] != edges[i].to)
		{
			f[edges[i].to] = lptr, lptr += dep[edges[i].to] << 1;
			g[edges[i].to] = lptr, lptr += dep[edges[i].to] << 1;
			calc(edges[i].to, u);
			for (int j = 0; j < dep[edges[i].to]; j++)
			{
				if (j != 0)
					ans += f[u][j - 1] * g[edges[i].to][j];
				ans += g[u][j + 1] * f[edges[i].to][j];
			}
			for (int j = 0; j < dep[edges[i].to]; j++)
			{
				g[u][j + 1] += f[u][j + 1] * f[edges[i].to][j];
				if (j != 0)
					g[u][j - 1] += g[edges[i].to][j];
				f[u][j + 1] += f[edges[i].to][j];
			}
		}
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1, u, v; i <= n - 1; i++)
		scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
	dfs(1, 0), f[1] = lptr, lptr += dep[1] << 1, g[1] = lptr, lptr += dep[1] << 1;
	calc(1, 0), printf("%lld\n", ans);
	return 0;
}
