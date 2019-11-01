// emperor.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int fa[MAX_N], n, m, s;

struct edge
{
	int from, to, weight;
	bool operator<(const edge &nd) const { return weight < nd.weight; }
} edges[MAX_N];

inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main()
{
	freopen("emperor.in", "r", stdin);
	freopen("emperor.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &edges[i].from, &edges[i].to, &edges[i].weight);
	sort(edges + 1, edges + 1 + m);
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	int cnt = 0;
	long long ans = 0;
	for (int i = 1; cnt <= n - 1 && i <= m; i++)
		if (find(edges[i].from) != find(edges[i].to))
		{
			fa[find(edges[i].from)] = find(edges[i].to);
			ans += edges[i].weight, cnt++;
		}
	if (cnt != n - 1)
		puts("-1");
	else
		printf("%lld", ans);
	return 0;
}
