// NegativeLoop.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, m, head[MAX_N], current, dist[MAX_N], cnt[MAX_N];
bool vis[MAX_N];

struct edge
{
	int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
	edges[current].to = dst, edges[current].weight = weight;
	edges[current].nxt = head[src], head[src] = current++;
}

bool spfa()
{
	memset(vis, false, sizeof(vis));
	queue<int> q;
	q.push(1), vis[1] = true, dist[1] = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		if (++cnt[u] >= n)
			return false;
		vis[u] = false;
		for (int i = head[u]; i != -1; i = edges[i].nxt)
			if (dist[edges[i].to] > dist[u] + edges[i].weight)
			{
				dist[edges[i].to] = dist[u] + edges[i].weight;
				if (!vis[edges[i].to])
					q.push(edges[i].to), vis[edges[i].to] = true;
			}
	}
	return true;
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		memset(head, -1, sizeof(head));
		memset(cnt, 0, sizeof(cnt));
		memset(dist, 0x3f, sizeof(dist));
		current = 0, scanf("%d%d", &n, &m);
		for (int i = 1, u, v, w; i <= m; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			addpath(u, v, w);
			if (w >= 0)
				addpath(v, u, w);
		}
		puts(spfa() ? "NO" : "YES");
	}
	return 0;
}
