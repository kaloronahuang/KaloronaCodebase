// LOJ2876.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, MAX_H = 2020, dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};

typedef pair<int, int> pii;

int n, m, p, qi, dist[MAX_H][MAX_H], aff[MAX_H][MAX_H], ecnt, mem[MAX_N], up[20][MAX_N], max_val[20][MAX_N];
int dep[MAX_N];
char mp[MAX_H][MAX_H];

struct edge
{
	int u, v, w;
	bool operator<(const edge &rhs) const { return w < rhs.w; }
} edges[MAX_H * MAX_H];

vector<pii> G[MAX_N];

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void dfs(int u, int fa)
{
	up[0][u] = fa, dep[u] = dep[fa] + 1;
	for (pii v : G[u])
		if (v.first != fa)
		{
			max_val[0][v.first] = v.second;
			dfs(v.first, u);
		}
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &p, &qi);
	for (int i = 1; i <= n; i++)
		scanf("%s", mp[i] + 1);
	queue<pii> q;
	for (int i = 1, x, y; i <= p; i++)
		scanf("%d%d", &x, &y), q.push(make_pair(x, y)), aff[x][y] = i, mem[i] = i;
	while (!q.empty())
	{
		int x = q.front().first, y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int dstx = x + dx[i], dsty = y + dy[i];
			if (mp[dstx][dsty] == '.')
				if (aff[dstx][dsty] == 0)
					aff[dstx][dsty] = aff[x][y], dist[dstx][dsty] = dist[x][y] + 1, q.push(make_pair(dstx, dsty));
				else if (aff[dstx][dsty] != aff[x][y])
					edges[++ecnt] = edge{aff[dstx][dsty], aff[x][y], dist[x][y] + dist[dstx][dsty]};
		}
	}
	sort(edges + 1, edges + 1 + ecnt);
	for (int i = 1; i <= ecnt; i++)
	{
		int u = edges[i].u, v = edges[i].v;
		if (find(u) != find(v))
		{
			mem[find(v)] = find(u);
			G[u].push_back(make_pair(v, edges[i].w));
			G[v].push_back(make_pair(u, edges[i].w));
		}
	}
	for (int i = 1; i <= p; i++)
		if (dep[i] == 0)
			dfs(i, 0);
	for (int i = 1; i < 20; i++)
		for (int j = 1; j <= p; j++)
		{
			up[i][j] = up[i - 1][up[i - 1][j]];
			max_val[i][j] = max(max_val[i - 1][j], max_val[i - 1][up[i - 1][j]]);
		}
	while (qi--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if (find(x) != find(y))
			puts("-1");
		else
		{
			int ans = 0;
			if (dep[x] < dep[y])
				swap(x, y);
			for (int i = 19; i >= 0; i--)
				if (dep[up[i][x]] >= dep[y])
					ans = max(ans, max_val[i][x]), x = up[i][x];
			if (x == y)
			{
				printf("%d\n", ans);
				continue;
			}
			for (int i = 19; i >= 0; i--)
				if (up[i][x] != up[i][y])
				{
					ans = max(ans, max(max_val[i][x], max_val[i][y]));
					x = up[i][x];
					y = up[i][y];
				}
			ans = max(ans, max(max_val[0][x], max_val[0][y]));
			printf("%d\n", ans);
		}
	}
	return 0;
}
