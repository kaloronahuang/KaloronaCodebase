// P3953.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 100100, MAX_E = 200010;

int head[MAX_N], n, m, k, p, current, T;
ll dist[MAX_N], dp[MAX_N][60];
bool vis[MAX_N], inst[MAX_N][60];

struct edge
{
	int to, nxt;
	ll weight;
	bool tag;
} edges[MAX_E << 1];

void addpath(int src, int dst, ll weight, bool toggle)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	edges[current].tag = toggle, edges[current].weight = weight;
	head[src] = current++;
}

void shortest_path()
{
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, false, sizeof(vis));
	priority_queue<pr> pq;
	pq.push(make_pair(0, n)), dist[n] = 0;
	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (int i = head[u]; i != -1; i = edges[i].nxt)
			if (edges[i].tag == true && dist[edges[i].to] > dist[u] + edges[i].weight)
				dist[edges[i].to] = dist[u] + edges[i].weight, pq.push(make_pair(-dist[edges[i].to], edges[i].to));
	}
}

int dfs(int u, int addition)
{
	if (inst[u][addition])
		return -1;
	if (dp[u][addition])
		return dp[u][addition];
	inst[u][addition] = true;
	if (u == n)
		dp[u][addition] = 1;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (dist[edges[i].to] - dist[u] + edges[i].weight <= addition && edges[i].tag == true)
		{
			ll diff = dist[edges[i].to] - dist[u] + edges[i].weight;
			if (dfs(edges[i].to, addition - diff) == -1)
				return (dp[u][addition] = -1);
			dp[u][addition] = (1LL * dp[u][addition] + 1LL * dp[edges[i].to][addition - diff]) % p;
		}
	inst[u][addition] = false;
	return dp[u][addition];
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		memset(head, -1, sizeof(head)), current = 0;
		memset(inst, 0, sizeof(inst)), memset(dp, 0, sizeof(dp));
		scanf("%d%d%d%d", &n, &m, &k, &p);
		for (int i = 1, u, v, w; i <= m; i++)
			scanf("%d%d%d", &u, &v, &w), addpath(u, v, w, false), addpath(v, u, w, true);
		shortest_path();
		for (int i = 0; i < current; i++)
			edges[i].tag ^= 1;
		printf("%d\n", dfs(1, k));
	}
	return 0;
}