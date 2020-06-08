// P4517.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220, mod = 1000000007;

int n, m, head[MAX_N], current, up[MAX_N], dfn[MAX_N], low[MAX_N];
int ptot, stk[MAX_N], tail, siz[MAX_N], loop[MAX_N], loop_siz;
int ans, bin[MAX_N], g[MAX_N], pre[MAX_N];

struct edge
{
	int to, nxt;
} edges[MAX_N * MAX_N];

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

int fpow(int bas, int tim)
{
	int ret = 1;
	while (tim)
	{
		if (tim & 1)
			ret = 1LL * ret * bas % mod;
		bas = 1LL * bas * bas % mod;
		tim >>= 1;
	}
	return ret;
}

void calcLoop()
{
	if (loop_siz == 2)
	{
		ans = (0LL + ans + 1LL * (bin[loop[1]] - 1) * (bin[loop[2]] - 1) % mod) % mod;
		return;
	}
	for (int i = 1; i < loop_siz; i++)
		for (int j = 1; j <= loop_siz; j++)
		{
			memset(g, 0, sizeof(g));
			memset(pre, 0, sizeof(pre));
			pre[j] = g[j] = bin[loop[j]] - 1;
			for (int k = j + 1; k <= loop_siz; k++)
			{
				g[k] = 1LL * (bin[loop[k]] - 1) * ((0LL + pre[k - 1] + mod - pre[max(0, k - i - 1)]) % mod) % mod;
				pre[k] = (0LL + pre[k - 1] + g[k]) % mod;
				if (j + loop_siz - k <= i)
					ans = (0LL + ans + g[k]) % mod;
			}
		}
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++ptot, stk[++tail] = u, siz[u] = 1;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (dfn[edges[i].to])
			low[u] = min(low[u], dfn[edges[i].to]);
		else
		{
			tarjan(edges[i].to);
			if (low[edges[i].to] >= dfn[u])
			{
				int x = loop_siz = 0, sum = 0;
				do
				{
					x = stk[tail--];
					sum += siz[x], loop[++loop_siz] = siz[x];
				} while (x != edges[i].to);
				loop[++loop_siz] = n - sum, siz[u] += sum;
				calcLoop();
			}
			low[u] = min(low[u], low[edges[i].to]);
		}
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++)
		scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
	for (int i = bin[0] = 1; i <= m; i++)
		bin[i] = 2LL * bin[i - 1] % mod;
	tarjan(1), ans = 1LL * ans * fpow(fpow(2, mod - 2), n) % mod;
	printf("%d\n", ans);
	return 0;
}
