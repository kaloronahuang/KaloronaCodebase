// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, MAX_P = MAX_N << 1, INF = 0x3f3f3f3f;

int n, m, ai[MAX_N][MAX_N], bi[MAX_N][MAX_N], ptot;
int rmat[MAX_N], mat[MAX_N][MAX_N], f[MAX_N][MAX_N], g[MAX_N][MAX_N];
pair<int, int> trans[MAX_N * MAX_N];
vector<int> tr[MAX_N][MAX_N];

namespace NetworkFlow
{

	int head[MAX_P], current, deg[MAX_P], start_pos, end_pos, dep[MAX_P], cur[MAX_P];

	struct edge
	{
		int to, nxt, weight, pos;
	} edges[MAX_N * MAX_N << 2];
	
	void addpath(int src, int dst, int weight, int pos)
	{
		edges[current].to = dst, edges[current].nxt = head[src];
		edges[current].weight = weight, edges[current].pos = pos, head[src] = current++;
	}
	
	void addtube(int src, int dst, int weight)
	{
		addpath(src, dst, weight, deg[dst]);
		addpath(dst, src, 0, deg[src]);
		deg[src]++, deg[dst]++;
	}
	
	void build()
	{
		memset(head, -1, sizeof(head)), memset(deg, 0, sizeof(deg));
		current = 0, start_pos = (n << 1) + 1, end_pos = start_pos + 1;
		for (int i = 1; i <= n; i++)
			addtube(start_pos, i, 1), addtube(i + n, end_pos, 1);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (mat[i][j])
					addtube(i, j + n, 1);
	}
	
	bool bfs()
	{
		memset(dep, 0, sizeof(dep));
		queue<int> q;
		q.push(start_pos), dep[start_pos] = 1;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int i = head[u]; i != -1; i = edges[i].nxt)
				if (dep[edges[i].to] == 0 && edges[i].weight > 0)
					dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
		}
		return dep[end_pos] != 0;
	}
	
	int dfs(int u, int flow)
	{
		if (u == end_pos || flow == 0)
			return flow;
		for (int i = head[u]; i != -1; i = edges[i].nxt)
			if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
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
			memcpy(cur, head, sizeof(cur));
			while (int di = dfs(start_pos, INF))
				ret += di;
		}
		for (int u = 1; u <= n; u++)
			for (int i = head[u]; i != -1; i = edges[i].nxt)
				if (edges[i].to != start_pos && edges[i].weight == 0)
					rmat[u] = edges[i].to - n;
		return ret;
	}

}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &ai[i][j]), bi[i][j] = ++ptot;
			trans[ai[i][j]].first = i, trans[bi[i][j]].second = i;
		}
	for (int i = 1; i <= n * m; i++)
		tr[trans[i].first][trans[i].second].push_back(i);
	for (int k = 1; k <= m; k++)
	{
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				mat[i][j] = !tr[i][j].empty();
		NetworkFlow::build(), NetworkFlow::dinic();
		for (int i = 1; i <= n; i++)
		{
			int x = tr[i][rmat[i]].back();
			tr[i][rmat[i]].pop_back();
			f[i][k] = x, g[rmat[i]][k] = x;
		}
	}
	for (int i = 1; i <= n; i++, puts(""))
		for (int j = 1; j <= m; j++)
			printf("%d ", f[i][j]);
	for (int i = 1; i <= n; i++, puts(""))
		for (int j = 1; j <= m; j++)
			printf("%d ", g[i][j]);
	return 0;
}
