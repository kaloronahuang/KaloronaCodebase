// lilac.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2550, MAX_M = MAX_N * (MAX_N - 1) / 2;

typedef pair<int, int> pii;

int n, m, mp[MAX_N][MAX_N], start_pos, ecnt, ui[MAX_M], vi[MAX_M];

void fileIO()
{
	freopen("lilac.in", "r", stdin);
	freopen("lilac.out", "w", stdout);
}

namespace Subtask1
{

	const int MAX_P = 2e6 + 200;
	
	int dist[MAX_P];
	bool vis[MAX_P];

	int getId(int x, int stat) { return stat * n + x; }

	int handler()
	{
		memset(dist, 0x3f, sizeof(dist));
		dist[getId(start_pos, 0)] = 0;
		for (int stat = 0; stat < (1 << m); stat++)
		{
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					dist[getId(i, stat)] = min(dist[getId(i, stat)], dist[getId(j, stat)] + abs(i - j));
			for (int i = 0; i < m; i++)
			{
				int u = ui[i], v = vi[i];
				dist[getId(u, stat | (1 << i))] = min(dist[getId(u, stat | (1 << i))], dist[getId(v, stat)] + abs(u - v));
				swap(u, v);
				dist[getId(u, stat | (1 << i))] = min(dist[getId(u, stat | (1 << i))], dist[getId(v, stat)] + abs(u - v));
			}
		}
		for (int i = 1; i <= n; i++)
			printf("%d ", dist[getId(i, (1 << m) - 1)]);
		puts("");
		return 0;
	}

}

int main()
{
	fileIO();
	memset(mp, -1, sizeof(mp));
	scanf("%d%d%d", &n, &m, &start_pos);
	for (int i = 1, u, v; i <= m; i++)
		scanf("%d%d", &u, &v), mp[u][v] = mp[v][u] = ecnt++, ui[i - 1] = u, vi[i - 1] = v;
	return Subtask1::handler();
	return 0;
}
