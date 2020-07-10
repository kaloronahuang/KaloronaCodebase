// UOJ67.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, head[MAX_N], current, dfn[MAX_N], low[MAX_N], ptot, cut[MAX_N], deg[MAX_N];

struct edge
{
	int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

void tarjan(int u, int fa)
{
	dfn[u] = low[u] = ++ptot;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (dfn[edges[i].to] == 0)
		{
			tarjan(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
			if (low[edges[i].to] >= dfn[u])
				cut[u]++;
		}
		else if (edges[i].to != fa)
			low[u] = min(low[u], dfn[edges[i].to]);
	cut[u] -= fa == 0;
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++)
		scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0)
			tarjan(i, 0);
	vector<int> ansBox;
	for (int i = 1; i <= n; i++)
		if (deg[i] == (m - (n - 2)) && cut[i] <= 0)
			ansBox.push_back(i);
	printf("%lld\n", 1LL * ansBox.size());
	for (int x : ansBox)
		printf("%d ", x);
	puts("");
	return 0;
}
