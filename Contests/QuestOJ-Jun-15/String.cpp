// String.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8e6 + 200;

typedef long long ll;
typedef pair<int, int> pii;

int n, pos[MAX_N], siz[MAX_N], rnk[MAX_N], bucket[MAX_N], Ttot, top[MAX_N], G[MAX_N][26], tag[MAX_N], gtot;
char str[MAX_N];
ll dist[MAX_N];

struct node
{
	int ch[3], dep, link;
} nodes[MAX_N];

int ptot = 1;

int insert(int c, int last_ptr)
{
	int pre = last_ptr, p = last_ptr = ++ptot;
	nodes[p].dep = nodes[pre].dep + 1;
	while (pre && nodes[pre].ch[c] == 0)
		nodes[pre].ch[c] = p, pre = nodes[pre].link;
	if (pre == 0)
		nodes[p].link = 1;
	else
	{
		int q = nodes[pre].ch[c];
		if (nodes[q].dep == nodes[pre].dep + 1)
			nodes[p].link = q;
		else
		{
			int clone = ++ptot;
			nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
			nodes[p].link = nodes[q].link = clone;
			while (pre && nodes[pre].ch[c] == q)
				nodes[pre].ch[c] = clone, pre = nodes[pre].link;
		}
	}
	return last_ptr;
}

void radixSort()
{
	for (int i = 1; i <= ptot; i++)
		bucket[nodes[i].dep]++;
	for (int i = 1; i <= ptot; i++)
		bucket[i] += bucket[i - 1];
	for (int i = 1; i <= ptot; i++)
		rnk[bucket[nodes[i].dep]--] = i;
	for (int i = ptot; i >= 2; i--)
		siz[nodes[rnk[i]].link] += siz[rnk[i]];
	for (int i = 1; i <= ptot; i++)
		dist[i] = 1LL * siz[i] * (nodes[i].dep - nodes[nodes[i].link].dep);
	for (int i = 1; i <= ptot; i++)
		dist[rnk[i]] += dist[nodes[rnk[i]].link];
}

int insertTrie(int fa, int c)
{
	int p = G[fa][c];
	if (p == 0)
		G[fa][c] = p = ++gtot;
	tag[p]++;
	return p;
}

int main()
{
	scanf("%d", &Ttot), top[1] = gtot = 1;
	for (int i = 2, fa; i <= Ttot; i++)
		scanf("%d%s", &fa, str + 1), top[i] = insertTrie(top[fa], str[1] - 'a');
	scanf("%s", str + 1), n = strlen(str + 1);
	queue<int> q;
	q.push(1), pos[1] = 1;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = 0; i < 26; i++)
			if (G[u][i])
				siz[pos[G[u][i]] = insert(i, pos[u])] += tag[G[u][i]], q.push(G[u][i]);
	}
	radixSort();
	ll ans = 0;
	for (int i = 1, p = 1, clen = 0; i <= n; i++)
	{
		int c = str[i] - 'a';
		while (p && nodes[p].ch[c] == 0)
			p = nodes[p].link, clen = min(clen, nodes[p].dep);
		if (p == 0)
		{
			p = 1, clen = 0;
			continue;
		}
		clen++, p = nodes[p].ch[c];
		ans += 1LL * (clen - nodes[nodes[p].link].dep) * siz[p] + dist[nodes[p].link];
		// printf("%lld %lld\n", 1LL * (clen - nodes[nodes[p].link].dep) * siz[p], dist[nodes[p].link]);
	}
	printf("%lld\n", ans);
	return 0;
}
