// snackstore.cpp
#include <bits/stdc++.h>

#define ll long long
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 110, MAX_Q = 1e6 + 200, INF = 0x3f3f3f3f, MAX_E = 10100;

int head[MAX_N], current, n, m, q, val[MAX_N];
vector<int> mapping;

struct edge
{
	int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	edges[current].weight = weight, head[src] = current++;
}

struct package
{
	int limit;
	bool vis[MAX_N];
	ll distances[MAX_N][MAX_N];
	
	void shortest_path(int u)
	{
		memset(vis, false, sizeof(vis));
		ll *dist = distances[u];
		priority_queue<pr> pq;
		pq.push(make_pair(0, u)), dist[u] = 0;
		while (!pq.empty())
		{
			int curt = pq.top().second;
			pq.pop();
			if (val[curt] > limit && curt != u)
				continue;
			if (vis[curt])
				continue;
			vis[curt] = true;
			for (int i = head[curt]; i != -1; i = edges[i].nxt)
				if (dist[edges[i].to] > dist[curt] + edges[i].weight)
				{
					dist[edges[i].to] = dist[curt] + edges[i].weight;
					pq.push(make_pair(-dist[edges[i].to], edges[i].to));
				}
		}
	}
	
	package(int lim)
	{
		limit = lim;
		memset(distances, 0x3f, sizeof(distances));
		for (int i = 1; i <= n; i++)
			shortest_path(i), sort(distances[i] + 1, distances[i] + 1 + n);
	}
} *pkgs[MAX_N];

int main()
{
	freopen("snackstore.in", "r", stdin);
	freopen("snackstore.out", "w", stdout);
	memset(head, -1, sizeof(head));
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++)
		scanf("%d", &val[i]), mapping.push_back(val[i]);
	sort(mapping.begin(), mapping.end());	
	mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
	for (int i = 1, u, v, w; i <= m; i++)
		scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
	for (int i = 0, siz = mapping.size(); i < siz; i++)
		pkgs[i] = new package(mapping[i]);
	while (q--)
	{
		int s, c, d;
		scanf("%d%d%d", &s, &c, &d);
		int id = lower_bound(mapping.begin(), mapping.end(), c) - mapping.begin();
		int ans = lower_bound(pkgs[id]->distances[s] + 1, pkgs[id]->distances[s] + 1 + n, d) - (pkgs[id]->distances[s]) - 1;
		printf("%d\n", ans);
	}
	return 0;
}
