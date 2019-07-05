// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100, mod = 10081;

int head[MAX_N], current, dp[MAX_N][2], deg[MAX_N], n;

struct edge
{
	int to, nxt;
} edges[MAX_N<<1];

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

void dfs(int u, int fa)
{
	if(deg[u] == 1)
	{
		dp[u][0] = 1, dp[u][1] = 2;
		return;
	}
	int tmp_A = 1, tmp_B = 1;
	for(int i = head[u];i!=-1;i=edges[i].nxt)
		if(edges[i].to != fa)
		{
			dfs(edges[i].to, u);
			tmp_A = tmp_A * dp[edges[i].to][1] % mod, tmp_B = tmp_B * (dp[edges[i].to][1] - dp[edges[i].to][0] + mod) % mod;
		}
	dp[u][0] = tmp_B % mod;
	dp[u][1] = (tmp_A + tmp_B) % mod;
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for(int i = 1, tmpx, tmpy; i <= n - 1; i++)
		scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx), deg[tmpx]++, deg[tmpy]++;
	int rt = 1;
	deg[rt]++;
	dfs(rt, 0);
	printf("%d", dp[rt][1]);
	return 0;
}
