// P2633.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], n, m, current, ptot, fa[20][MAX_N], dep[MAX_N];
int val[MAX_N], upper, roots[MAX_N];
vector<int> mp;

struct edge
{
	int to, nxt;
} edges[MAX_N << 1];

struct node
{
	int sum, lson, rson;
} nodes[MAX_N * 20];

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

int update(int qx, int l, int r, int pre, int val)
{
	int p = ++ptot;
	nodes[p] = nodes[pre], nodes[p].sum += val;
	if (l == r)
		return p;
	int mid = (l + r) >> 1;
	if (qx <= mid)
		nodes[p].lson = update(qx, l, mid, nodes[pre].lson, val);
	else
		nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson, val);
	return p;
}

int query(int k, int l, int r, int p1, int p2, int p3, int p4)
{
	if (l == r)
		return l;
	int lval = nodes[nodes[p1].lson].sum + nodes[nodes[p2].lson].sum - nodes[nodes[p3].lson].sum - nodes[nodes[p4].lson].sum, mid = (l + r) >> 1;
	if (k > lval)
		return query(k - lval, mid + 1, r, nodes[p1].rson, nodes[p2].rson, nodes[p3].rson, nodes[p4].rson);
	else
		return query(k, l, mid, nodes[p1].lson, nodes[p2].lson, nodes[p3].lson, nodes[p4].lson);
}

void dfs(int u, int fat)
{
	fa[0][u] = fat, dep[u] = dep[fat] + 1;
	roots[u] = update(val[u], 1, upper, roots[fat], 1);
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fat)
			dfs(edges[i].to, u);
}

int getLCA(int x, int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	for (int i = 19; i >= 0; i--)
		if (dep[fa[i][x]] >= dep[y])
			x = fa[i][x];
	if (x == y)
		return x;
	for (int i = 19; i >= 0; i--)
		if (fa[i][x] != fa[i][y])
			x = fa[i][x], y = fa[i][y];
	return fa[0][x];
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &val[i]), mp.push_back(val[i]);
	sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
	for (int i = 1; i <= n; i++)
		val[i] = lower_bound(mp.begin(), mp.end(), val[i]) - mp.begin() + 1;
	upper = mp.size();
	for (int i = 1, u, v; i <= n - 1; i++)
		scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
	dfs(1, 0);
	for (int i = 1; i <= 19; i++)
		for (int j = 1; j <= n; j++)
			fa[i][j] = fa[i - 1][fa[i - 1][j]];
	int lastans = 0;
	while (m--)
	{
		int x, y, k;
		scanf("%d%d%d", &x, &y, &k), x ^= lastans;
		int lca = getLCA(x, y);
		printf("%d\n", lastans = mp[query(k, 1, upper, roots[x], roots[y], roots[lca], roots[fa[0][lca]]) - 1]);
	}
	return 0;
}
