// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200;

typedef long long ll;

int n, bucket[MAX_N], rnk[MAX_N], pos[MAX_N], fa[MAX_N], son[MAX_N], top[MAX_N];
int lft[MAX_N], rig[MAX_N], dtot, anti[MAX_N], weights[MAX_N], siz[MAX_N], dep[MAX_N];
char org[MAX_N];
vector<int> last_pos[MAX_N], G[MAX_N];

namespace Trie
{

	int ch[MAX_N][26], ptot = 1;
	
	void insert(char *str, int src)
	{
		int p = 1;
		for (int i = 1; str[i]; i++)
		{
			int c = str[i] - 'a';
			if (ch[p][c] == 0)
				ch[p][c] = ++ptot;
			p = ch[p][c], last_pos[src].push_back(p);
		}
	}

}

namespace SegmentTree
{

	ll nodes[2][MAX_N << 2], tag[MAX_N << 2], nval[MAX_N << 2];
	
	#define lson (p << 1)
	#define rson ((p << 1) | 1)
	#define mid ((l + r) >> 1)
	
	void pushup(int p)
	{
		for (int i = 0; i < 2; i++)
			nodes[i][p] = nodes[i][lson] + nodes[i][rson];
	}
	
	void pushdown(int p)
	{
		if (tag[p])
		{
			tag[lson] += tag[p], tag[rson] += tag[p];
			nodes[1][lson] += tag[p] * tag[p] * nval[lson] + 2LL * tag[p] * nodes[0][lson];
			nodes[1][rson] += tag[p] * tag[p] * nval[rson] + 2LL * tag[p] * nodes[0][rson];
			nodes[0][lson] += tag[p] * nval[lson];
			nodes[0][rson] += tag[p] * nval[rson];
			tag[p] = 0;
		}
	}
	
	void build(int l, int r, int p)
	{
		if (l == r)
			return (void)(nval[p] = weights[anti[l]]);
		build(l, mid, lson), build(mid + 1, r, rson);
		nval[p] = nval[lson] + nval[rson];
	}
	
	void update(int ql, int qr, int l, int r, int p)
	{
		if (ql <= l && r <= qr)
		{
			nodes[1][p] += nval[p] + 2LL * nodes[0][p];
			nodes[0][p] += nval[p], tag[p]++;
			return;
		}
		pushdown(p);
		if (ql <= mid)
			update(ql, qr, l, mid, lson);
		if (mid < qr)
			update(ql, qr, mid + 1, r, rson);
		pushup(p);
	}
	
}

struct node
{
	int ch[26], link, dep;
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
	for (int i = 1; i <= ptot; i++)
		weights[i] = nodes[i].dep - nodes[nodes[i].link].dep;
	for (int i = ptot; i >= 1; i--)
		if (nodes[rnk[i]].link != 0)
			G[nodes[rnk[i]].link].push_back(rnk[i]);
}

void dfs1(int u)
{
	siz[u] = 1, dep[u] = dep[fa[u]] + 1;
	for (int v : G[u])
	{
		fa[v] = u, dfs1(v);
		siz[u] += siz[v], son[u] = siz[v] > siz[son[u]] ? v : son[u];
	}
}

void dfs2(int u, int org)
{
	lft[u] = ++dtot, top[u] = org, anti[dtot] = u;
	if (son[u])
		dfs2(son[u], org);
	for (int v : G[u])
		if (v != son[u])
			dfs2(v, v);
}

void updateChain(int p)
{
	while (p)
	{
		SegmentTree::update(lft[top[p]], lft[p], 1, ptot, 1);
		p = fa[top[p]];
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%s", org + 1), Trie::insert(org, i);
	queue<int> q;
	q.push(1), pos[1] = 1;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = 0; i < 26; i++)
			if (Trie::ch[u][i])
				pos[Trie::ch[u][i]] = insert(i, pos[u]), q.push(Trie::ch[u][i]);
	}
	for (int i = 1; i <= n; i++)
		for (int &u : last_pos[i])
			u = pos[u];
	radixSort(), dfs1(1), dfs2(1, 1), SegmentTree::build(1, ptot, 1);
	for (int i = 1; i <= n; i++)
	{
		for (int j : last_pos[i])
			updateChain(j);
		printf("%lld\n", SegmentTree::nodes[1][1]);
	}
	return 0;
}
