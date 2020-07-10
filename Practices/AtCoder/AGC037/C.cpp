// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;
typedef long long ll;

int n, ai[MAX_N], bi[MAX_N];
priority_queue<pii> pq;
ll ans;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &ai[i]);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &bi[i]);
		if (bi[i] != ai[i])
			pq.push(make_pair(bi[i], i));
	}
	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		int pre = (u + n - 2) % n + 1, suf = u % n + 1, steps = (bi[u] - ai[u]) / (bi[pre] + bi[suf]);
		if (steps == 0)
			puts("-1"), exit(0);
		ans += steps, bi[u] -= steps * (bi[pre] + bi[suf]);
		if (ai[u] != bi[u])
			pq.push(make_pair(bi[u], u));
	}
	printf("%lld\n", ans);
	return 0;
}
