// Cut.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e4 + 200, MAX_E = 1e5 + 200;

int n, m, head[MAX_N], current, dfn[MAX_N], low[MAX_N];
int cut[MAX_N], ptot;

struct edge
{
	int to, nxt;
} edges[MAX_E << 1];

void tarjan(int u, int fa, int rt)
{
	dfn[u] = low[u] = ++ptot;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa)
			if (dfn[edges[i].to] == 0)
			{
				tarjan(edges[i].to, u, rt);
				if (low[edges[i].to] >= dfn[u])
					cut[u]++;
				low[u] = min(low[u], low[edges[i].to]);
			}
			else
				low[u] = min(low[u], dfn[edges[i].to]);
	cut[u] -= (u == rt);
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		edges[current].to = v, edges[current].nxt = head[u];
		head[u] = current++;
		edges[current].to = u, edges[current].nxt = head[v];
		head[v] = current++;
	}
	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0)
			tarjan(i, 0, i);
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if (cut[i] > 0)
			cnt++;
	printf("%d\n", cnt);
	for (int i = 1; i <= n; i++)
		if (cut[i] > 0)
			printf("%d ", i);
	puts("");
	return 0;
}
