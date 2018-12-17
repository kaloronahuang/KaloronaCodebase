// P2024.cpp
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 500;
int fa[3 * maxn], N, K;
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int a, int b)
{
	int ra = find(a), rb = find(b);
	if (ra != rb)
		fa[rb] = ra;
}
int main()
{
	scanf("%d%d", &N, &K);
	for (int i = 0; i < 3 * maxn; i++)
		fa[i] = i;
	int ans = 0;
	for (int i = 0; i < K; i++)
	{
		int opt, u, v;
		scanf("%d%d%d", &opt, &u, &v);
		int su = u, eu = u + N, pu = u + 2 * N;
		int sv = v, ev = v + N, pv = v + 2 * N;
		if (u > N || v > N)
		{
			ans++;
			continue;
		}
		if (opt == 1)
		{
			if (find(su) == find(sv))
				continue;
			if (find(pu) == find(sv) || find(pv) == find(su))
			{
				ans++;
				continue;
			}
			merge(su, sv), merge(eu, ev), merge(pu, pv);
		}
		else
		{
			if (u == v || find(su) == find(sv) || find(pv) == find(su))
			{
				ans++;
				continue;
			}
			merge(pu, sv), merge(su, ev), merge(eu, pv);
		}
	}
	printf("%d", ans);
	return 0;
}