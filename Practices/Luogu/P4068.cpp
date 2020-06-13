// P4068.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 440, INF = 0x3f3f3f3f;

typedef long long ll;

int n, ai[MAX_N], bi[MAX_N], ci[MAX_N], head[MAX_N], current, cnt[MAX_N];
int pre[MAX_N], flow[MAX_N], start_pos, end_pos;
ll dist[MAX_N];
bool vis[MAX_N];

struct edge
{
	int to, nxt, weight;
	ll cost;
} edges[MAX_N * MAX_N << 1];

void addpath(int src, int dst, int weight, ll cost)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	edges[current].weight = weight, edges[current].cost = cost;
	head[src] = current++;
}

void addtube(int src, int dst, int weight, ll cost)
{
	addpath(src, dst, weight, cost);
	addpath(dst, src, 0, -cost);
}

bool spfa()
{
	queue<int> q;
	memset(vis, 0, sizeof(vis)), memset(dist, 0xbf, sizeof(dist));
	memset(pre, -1, sizeof(pre)), q.push(start_pos), flow[start_pos] = INF;
	vis[start_pos] = true, dist[start_pos] = 0;
	while (!q.empty())
	{
		int u = q.front();
		q.pop(), vis[u] = false;
		for (int i = head[u]; i != -1; i = edges[i].nxt)
			if (edges[i].weight > 0 && dist[edges[i].to] < dist[u] + edges[i].cost)
			{
				dist[edges[i].to] = dist[u] + edges[i].cost;
				pre[edges[i].to] = i, flow[edges[i].to] = min(flow[u], edges[i].weight);
				if (!vis[edges[i].to])
					vis[edges[i].to] = true, q.push(edges[i].to);
			}
	}
	return pre[end_pos] != -1;
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &ai[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &bi[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &ci[i]);
	start_pos = n + 1, end_pos = start_pos + 1;
	for (int i = 1; i <= n; i++)
	{
		int acc = ai[i];
		for (int j = 2; 1LL * j * j <= acc; j++)
			while (acc % j == 0)
				acc /= j, cnt[i]++;
		if (acc > 1)
			cnt[i]++;
		if (cnt[i] & 1)
			addtube(start_pos, i, bi[i], 0);
		else
			addtube(i, end_pos, bi[i], 0);
	}
	for (int i = 1; i <= n; i++)
		if (cnt[i] & 1)
			for (int j = 1; j <= n; j++)
				if ((ai[i] % ai[j] == 0 && cnt[j] + 1 == cnt[i]) || (ai[j] % ai[i] == 0 && cnt[i] + 1 == cnt[j]))
					addtube(i, j, INF, 1LL * ci[i] * ci[j]);
	ll cst = 0, mflow = 0;
	while (spfa())
	{
		int u = end_pos;
		if (cst + 1LL * dist[end_pos] * flow[end_pos] < 0)
		{
			mflow += cst / -dist[end_pos];
			break;
		}
		cst += 1LL * dist[end_pos] * flow[end_pos], mflow += flow[end_pos];
		while (u != start_pos)
		{
			edges[pre[u]].weight -= flow[end_pos];
			edges[pre[u] ^ 1].weight += flow[end_pos];
			u = edges[pre[u] ^ 1].to;
		}
	}
	printf("%lld\n", mflow);
	return 0;
}
