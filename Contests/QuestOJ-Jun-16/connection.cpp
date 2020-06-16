// connection.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int n, m, head[MAX_N], current, start_pos, end_pos, cur[MAX_N], dep[MAX_N], ui[MAX_N], vi[MAX_N];

struct edge
{
	int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight)
{
	addpath(src, dst, weight);
	addpath(dst, src, 0);
}

bool bfs()
{
	memset(dep, 0, sizeof(int) * (n + 5));
	queue<int> q;
	q.push(start_pos), dep[start_pos] = 1;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = head[u]; i != -1; i = edges[i].nxt)
			if (edges[i].weight > 0 && dep[edges[i].to] == 0)
				dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
	}
	return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
	if (u == end_pos || flow == 0)
		return flow;
	for (int &i = cur[u]; i != -1; i = edges[i].nxt)
		if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight > 0)
			if (int di = dfs(edges[i].to, min(flow, edges[i].weight)))
			{
				edges[i].weight -= di, edges[i ^ 1].weight += di;
				return di;
			}
	return 0;
}

int dinic()
{
	int ret = 0;
	while (bfs())
	{
		memcpy(cur, head, sizeof(int) * (n + 5));
		while (int di = dfs(start_pos, INF))
			ret += di;
	}
	return ret;
}

int main()
{
	scanf("%d%d", &n, &m), start_pos = 1, end_pos = start_pos + 1;
	for (int i = 1, u, v; i <= m; i++)
		scanf("%d%d", &ui[i], &vi[i]);
	int ans = INF;
	for (end_pos = 2; end_pos <= n; end_pos++)
	{
		memset(head, -1, sizeof(int) * (n + 5)), current = 0;
		for (int i = 1; i <= m; i++)
			addtube(ui[i], vi[i], 1), addtube(vi[i], ui[i], 1);
		ans = min(ans, dinic());
	}
	printf("%d\n", ans);
	return 0;
}
