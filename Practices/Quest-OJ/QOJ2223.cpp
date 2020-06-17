// QOJ2223.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, k, hi[MAX_N], stk[MAX_N], tail, fa[MAX_N], siz[MAX_N], deg[MAX_N];
ll ans, rem[MAX_N];

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &hi[i]);
		int p = 0;
		while (tail && hi[stk[tail]] >= hi[i])
			p = stk[tail--];
		if (p != 0)
			fa[p] = i;
		fa[i] = stk[tail], stk[++tail] = i;
	}
	for (int i = 1; i <= n; i++)
		deg[fa[i]]++, siz[i] = 1;
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (deg[i] == 0)
			q.push(i);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		rem[u] += 1LL * siz[u] * (hi[u] - hi[fa[u]]);
		if (rem[u] > 0)
		{
			ll coeff = (rem[u] - 1) / k + 1;
			ans += coeff, rem[u] -= 1LL * coeff * k;
		}
		rem[fa[u]] += rem[u], siz[fa[u]] += siz[u];
		if (--deg[fa[u]] == 0)
			q.push(fa[u]);
	}
	printf("%lld\n", ans);
	return 0;
}
