// BZ3590.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 13, MAX_E = 90;

int T, n, m, f[1 << MAX_N], h[1 << MAX_N][MAX_N][2], g[1 << MAX_N][MAX_N][MAX_N];
int head[MAX_N], log2_[1 << MAX_N], current;

struct edge
{
	int to, nxt, weight;
} edges[MAX_E << 1];

inline int lowbit(int x) { return x & (-x); }

void addpath(int src, int dst, int weight)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	edges[current].weight = weight, head[src] = current++;
}

int main()
{
	scanf("%d", &T);
	for (int i = 2; i < (1 << MAX_N); i++)
		log2_[i] = log2_[i >> 1] + 1;
	while (T--)
	{
		memset(head, -1, sizeof(head));
		memset(f, 0x0f, sizeof(f)), memset(g, 0x0f, sizeof(g));
		memset(h, 0x0f, sizeof(h)), current = 0;
		
		scanf("%d%d", &n, &m);
		for (int i = 1, u, v, w; i <= m; i++)
			scanf("%d%d%d", &u, &v, &w), u--, v--, addpath(u, v, w), addpath(v, u, w);
		for (int stat = 0; stat < (1 << n); stat++)
		{
			for (int sub = ((1 << n) - 1) ^ stat; sub; sub -= lowbit(sub))
			{
				int u = log2_[lowbit(sub)];
				for (int i = head[u]; i != -1; i = edges[i].nxt)
					if (stat & (1 << (edges[i].to)))
						if (edges[i].weight < h[stat][u][0])
							swap(h[stat][u][0], h[stat][u][1]), h[stat][u][0] = edges[i].weight;
						else
							h[stat][u][1] = min(h[stat][u][1], edges[i].weight);
			}
		}
		for (int i = 0; i < n; i++)
			f[1 << i] = g[1 << i][i][i] = 0;
		for (int stat = 0; stat < (1 << n); stat++)
			for (int tA = stat; tA; tA -= lowbit(tA))
				for (int tB = stat; tB; tB -= lowbit(tB))
				{
					int a = log2_[lowbit(tA)], b = log2_[lowbit(tB)];
					if (a == b)
						continue;
					for (int i = head[b]; i != -1; i = edges[i].nxt)
						if (stat & (1 << (edges[i].to)))
							g[stat][a][b] = min(g[stat][a][b], g[stat ^ (1 << b)][a][edges[i].to] + edges[i].weight);
				}
		for (int stat = 0; stat < (1 << n); stat++)
		{
			if (stat == lowbit(stat))
				continue;
			for (int sub = stat & (stat - 1); sub; sub = (sub - 1) & stat)
				for (int tA = sub; tA; tA -= lowbit(tA))
					for (int tB = sub; tB; tB -= lowbit(tB))
					{
						int a = log2_[lowbit(tA)], b = log2_[lowbit(tB)];
						if (a == b)
							f[stat] = min(f[stat], f[stat ^ sub] + g[sub][a][b] + h[stat ^ sub][a][0] + h[stat ^ sub][a][1]);
						else
							f[stat] = min(f[stat], f[stat ^ sub] + g[sub][a][b] + h[stat ^ sub][a][0] + h[stat ^ sub][b][0]);
					}
		}
		if (f[(1 << n) - 1] == 0x0f0f0f0f)
			puts("impossible");
		else
			printf("%d\n", f[(1 << n) - 1]);
	}
	return 0;
}
