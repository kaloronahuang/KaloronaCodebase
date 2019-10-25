// CF505D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], n, m, current, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail;
int fa[MAX_N], ncnt, aff[MAX_N], siz[MAX_N];
bool inst[MAX_N], mark[MAX_N];

struct edge
{
	int to, nxt;
} edges[MAX_N << 1];

inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++ptot, inst[u] = true, stk[++tail] = u;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (dfn[edges[i].to] == 0)
			tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
		else if (inst[edges[i].to])
			low[u] = min(low[u], dfn[edges[i].to]);
	if (dfn[u] == low[u])
	{
		ncnt++;
		do
		{
			aff[stk[tail]] = ncnt, inst[stk[tail]] = false, siz[ncnt]++, mark[ncnt] = siz[ncnt] > 1;
		} while (stk[tail--] != u);
	}
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++)
		scanf("%d%d", &u, &v), addpath(u, v);
	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0)
			tarjan(i);
	for (int i = 1; i <= ncnt; i++)
		fa[i] = i;
	for (int u = 1; u <= n; u++)
		for (int i = head[u]; i != -1; i = edges[i].nxt)
			if (find(aff[u]) != find(aff[edges[i].to]))
				siz[find(aff[u])] += siz[find(aff[edges[i].to])], mark[find(aff[u])] |= mark[find(aff[edges[i].to])], fa[find(aff[edges[i].to])] = fa[find(aff[u])];
	int ans = 0;
	for (int u = 1; u <= ncnt; u++)
		if (fa[u] == u)
			ans += (mark[u] ? siz[u] : siz[u] - 1);
	printf("%d", ans);
	return 0;
}
