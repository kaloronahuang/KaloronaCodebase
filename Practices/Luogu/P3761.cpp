// P3761.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int n, head[MAX_N], current, distances[5][MAX_N], *dist, up[MAX_N], pre[MAX_N], forbid;

struct edge
{
	int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	edges[current].weight = weight, head[src] = current++; 
}

void dfs(int u, int fa, bool faenabled = false)
{
	if (faenabled)
		up[u] = fa;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa && (i >> 1) != forbid)
		{
			dist[edges[i].to] = dist[u] + edges[i].weight;
			if (faenabled)
				pre[edges[i].to] = i;
			dfs(edges[i].to, u, faenabled);
		}
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1, u, v, w; i <= n - 1; i++)
		scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
	int A, B;
	dist = distances[0], forbid = -1;
	dist[1] = 0, dfs(1, 0), A = max_element(dist + 1, dist + 1 + n) - dist;
	dist[A] = 0, dfs(A, 0, true), B = max_element(dist + 1, dist + 1 + n) - dist;
	int ans = 0x3f3f3f3f;
	for (int u = B; u != A; u = up[u])
	{
		forbid = pre[u] >> 1;
		int uA, uB, pans = edges[pre[u]].weight;
		memset(distances[1], -1, sizeof(distances[1]));
		dist = distances[1], dist[u] = 0, dfs(u, up[u]);
		uA = max_element(dist + 1, dist + 1 + n) - dist;
		memset(distances[2], -1, sizeof(distances[2]));
		dist = distances[2], dist[uA] = 0, dfs(uA, 0);
		uB = max_element(dist + 1, dist + 1 + n) - dist;
		int dA = dist[uB];
		memset(distances[1], 0x3f, sizeof(distances[1]));
		memset(distances[2], 0x3f, sizeof(distances[2]));
		dist = distances[1], dist[uA] = 0, dfs(uA, 0);
		dist = distances[2], dist[uB] = 0, dfs(uB, 0);
		int tmpA = 0x3f3f3f3f;
		for (int i = 1; i <= n; i++)
			tmpA = min(tmpA, max(distances[1][i], distances[2][i]));
			
		memset(distances[1], -1, sizeof(distances[1]));
		dist = distances[1], dist[up[u]] = 0, dfs(up[u], u);
		uA = max_element(dist + 1, dist + 1 + n) - dist;
		memset(distances[2], -1, sizeof(distances[2]));
		dist = distances[2], dist[uA] = 0, dfs(uA, 0);
		uB = max_element(dist + 1, dist + 1 + n) - dist;
		int dB = dist[uB];
		memset(distances[1], 0x3f, sizeof(distances[1]));
		memset(distances[2], 0x3f, sizeof(distances[2]));
		dist = distances[1], dist[uA] = 0, dfs(uA, 0);
		dist = distances[2], dist[uB] = 0, dfs(uB, 0);
		int tmpB = 0x3f3f3f3f;
		for (int i = 1; i <= n; i++)
			tmpB = min(tmpB, max(distances[1][i], distances[2][i]));
		
		pans += tmpA + tmpB, ans = min(ans, max(pans, max(dA, dB)));
	}
	printf("%d\n", ans);
	return 0;
}
