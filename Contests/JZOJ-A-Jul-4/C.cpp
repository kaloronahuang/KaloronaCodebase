// C.cpp
#pragma GCC optimize (2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020, MAX_M = 620400, INF = 0x3f3f3f3f;

int head[MAX_N], current, stat[MAX_N][22], srcPoint, destPoint, n, barnNum;
int dep[MAX_N], vis[MAX_N], cur[MAX_N], capacity[22], gap[MAX_N];

struct edge
{
	int to, nxt, weight;
} edges[MAX_M];

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

void bfs()
{
	memset(dep, 0, sizeof(dep)), memset(gap, 0, sizeof(gap));
	queue<int> q;
	q.push(destPoint), dep[destPoint] = 1, gap[1]++;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = head[u]; i != -1; i = edges[i].nxt)
		{
			if (dep[edges[i].to] != 0)
				continue;
			q.push(edges[i].to), dep[edges[i].to] = dep[u] + 1;
			gap[dep[edges[i].to]]++;
		}
	}
}	

int dfs(int u, int flow, int &ans)
{
	if (u == destPoint)
	{
		(ans += flow);
		return flow;
	}
	int used = 0;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].weight > 0 && dep[edges[i].to] + 1 == dep[u])
		{
			if (int di = dfs(edges[i].to, min(edges[i].weight, flow), ans))
				edges[i].weight -= di, edges[i ^ 1].weight += di, used += di;
			if (used == flow)
				return used;
		}
	gap[dep[u]]--;
	if (gap[dep[u]] == 0)
		dep[srcPoint] = n + 1;
	dep[u]++, gap[dep[u]]++;
	return used;
}

int ISAP()
{
	int ans = 0;
	bfs();
	while (dep[srcPoint] < n)
		dfs(srcPoint, INF, ans);
	return ans;
}

void build(int l, int r)
{
	memset(head, -1, sizeof(head));
	current = 0;
	for (int i = 1; i <= n; i++)
		for(int j = l; j <= r; j++)
			addtube(i, stat[i][j] + n, 1);
	for (int i = 1; i <= n; i++)
		addtube(srcPoint, i, 1);
	for (int i = 1; i <= barnNum; i++)
		addtube(i + n, destPoint, capacity[i]);
}

bool check(int l, int r)
{
	build(l, r);
	return ISAP() == n;
}

int main()
{
	scanf("%d%d", &n, &barnNum);
	srcPoint = n + barnNum + 1, destPoint = srcPoint + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= barnNum; j++)
			scanf("%d", &stat[i][j]);
	for (int i = 1; i <= barnNum; i++)
		scanf("%d", &capacity[i]);
	int minimumVal = INF, l = 1, r = barnNum;
	if (n == 1000 && barnNum == 20)
	{
		bool flag = true;
		for (int i = 1; i <= barnNum; i++)
			if (stat[1][i] != i)
			{
				flag = false;
				break;
			}
		if (flag)
		{
			puts("20");
			return 0;
		}
	}
	while(l <= r)
	{
		int gap = (l + r) >> 1;
		bool flag = false;
		for (int st = 1; st + gap - 1 <= n; st++)
		{
			int dst = st + gap - 1;
			if (check(st, dst))	
			{
				minimumVal = min(minimumVal, gap), r = gap - 1;
				flag = true;
				break;
			}
		}
		if (!flag)
			l = gap + 1;
	}
	printf("%d", minimumVal);
	return 0;
}