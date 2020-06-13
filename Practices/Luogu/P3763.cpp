// P3763.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

struct node
{
	int ch[4], link, dep;
} nodes[MAX_N << 1];

int T, n1, n2, bucket[MAX_N << 1], siz[MAX_N << 1], rnk[MAX_N << 1];
int ptot = 1, last_ptr = 1;
char str[2][MAX_N];
ll ans;

void insert(int c)
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
}

int getId(char c) { return c == 'A' ? 0 : (c == 'T' ? 1 : (c == 'G' ? 2 : 3)); }

void dfs(int ptr, int p, int rem)
{
	if (rem < 0)
		return;
	if (ptr == n2 + 1)
		return (void)(ans += siz[p]);
	for (int i = 0; i < 4; i++)
	{
		if (nodes[p].ch[i] == 0)
			continue;
		dfs(ptr + 1, nodes[p].ch[i], rem - (getId(str[1][ptr]) != i));
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		memset(nodes, 0, sizeof(nodes));
		memset(bucket, 0, sizeof(bucket));
		memset(siz, 0, sizeof(siz));
		memset(rnk, 0, sizeof(rnk));
		ptot = last_ptr = 1, ans = 0;
		scanf("%s%s", str[0] + 1, str[1] + 1);
		n1 = strlen(str[0] + 1), n2 = strlen(str[1] + 1);
		for (int i = 1; i <= n1; i++)
			insert(getId(str[0][i])), siz[last_ptr]++;
		for (int i = 1; i <= ptot; i++)
			bucket[nodes[i].dep]++;
		for (int i = 1; i <= ptot; i++)
			bucket[i] += bucket[i - 1];
		for (int i = 1; i <= ptot; i++)
			rnk[bucket[nodes[i].dep]--] = i;
		for (int i = ptot; i >= 2; i--)
			siz[nodes[rnk[i]].link] += siz[rnk[i]];
		dfs(1, 1, 3), printf("%lld\n", ans);
	}
	return 0;
}
