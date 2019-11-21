// P3178.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, vi[MAX_N], lft[MAX_N], rig[MAX_N], anti[MAX_N], head[MAX_N], current, ptot;
ll dist[MAX_N], nodes1[MAX_N << 2], nodes2[MAX_N << 2];

struct edge
{
	int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

void dfs(int u, int fa)
{
	lft[u] = ++ptot, anti[ptot] = u, dist[u] = dist[fa] + 1;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa)
			dfs(edges[i].to, u);
	rig[u] = ptot;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p)
{
	nodes1[lson] += nodes1[p], nodes1[rson] += nodes1[p];
	nodes2[lson] += nodes2[p], nodes2[rson] += nodes2[p];
	nodes1[p] = nodes2[p] = 0;
}

void update(int ql, int qr, int l, int r, int p, ll val1, ll val2)
{
	if (ql <= l && r <= qr)
	{
		nodes1[p] += val1, nodes2[p] += val2;
		return;
	}
	pushdown(p);
	if (ql <= mid)
		update(ql, qr, l, mid, lson, val1, val2);
	if (mid < qr)
		update(ql, qr, mid + 1, r, rson, val1, val2);
}

ll query(int qx, int l, int r, int p)
{
	if (l == r)
		return dist[anti[l]] * nodes1[p] + nodes2[p];
	pushdown(p);
	if (qx <= mid)
		return query(qx, l, mid, lson);
	else
		return query(qx, mid + 1, r, rson);
}

#undef lson
#undef rson
#undef mid

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &vi[i]);
	for (int i = 1, u, v; i <= n - 1; i++)
		scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
		update(lft[i], rig[i], 1, n, 1, 0, vi[i]);
	while (m--)
	{
		int opt, x, a;
		scanf("%d%d", &opt, &x);
		if (opt == 1)
			scanf("%d", &a), update(lft[x], rig[x], 1, n, 1, 0, a);
		else if (opt == 2)
			scanf("%d", &a), update(lft[x], rig[x], 1, n, 1, a, -((dist[x] - 1) * a));
		else
			printf("%lld\n", query(lft[x], 1, n, 1));
	}
	return 0;
}
