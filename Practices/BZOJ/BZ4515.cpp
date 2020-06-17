// BZ4515.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;
const ll INF = 123456789123456789LL;

int n, q, head[MAX_N], current, dep[MAX_N], top[MAX_N], lft[MAX_N], rig[MAX_N], ptot, anti[MAX_N];
int siz[MAX_N], son[MAX_N], up[MAX_N];
ll dist[MAX_N];

struct edge
{
	int to, nxt, weight;
} edges[MAX_N << 1];

struct node
{
	ll mn, k, b;
	bool tag;
} nodes[MAX_N << 3];

ll calc(int p, int x) { return 1LL * nodes[p].k * dist[anti[x]] + nodes[p].b; }

ll calc(ll k, ll b, ll x) { return 1LL * k * dist[anti[x]] + b; }

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p) { nodes[p].mn = min(nodes[p].mn, min(nodes[lson].mn, nodes[rson].mn)); }

void build(int l, int r, int p)
{
	nodes[p].mn = INF;
	if (l == r)
		return;
	build(l, mid, lson), build(mid + 1, r, rson);
	pushup(p);
}

void update(int ql, int qr, int l, int r, int p, ll k, ll b)
{
	if (ql <= l && r <= qr)
	{
		if (nodes[p].tag)
			if (calc(p, l) >= calc(k, b, l) && calc(p, r) >= calc(k, b, r))
				nodes[p].k = k, nodes[p].b = b;
			else if (calc(p, l) <= calc(k, b, l) && calc(p, r) <= calc(k, b, r))
				return;
			else
			{
				if (k < nodes[p].k)
					if (calc(k, b, mid) <= calc(p, mid))
						update(ql, qr, l, mid, lson, nodes[p].k, nodes[p].b), nodes[p].k = k, nodes[p].b = b;
					else
						update(ql, qr, mid + 1, r, rson, k, b);
				else if (calc(k, b, mid) <= calc(p, mid))
					update(ql, qr, mid + 1, r, rson, nodes[p].k, nodes[p].b), nodes[p].k = k, nodes[p].b = b;
				else
					update(ql, qr, l, mid, lson, k, b);
				nodes[p].mn = min(nodes[p].mn, min(calc(p, l), calc(p, r)));
				pushup(p);
				return;
			}
		else
			nodes[p].k = k, nodes[p].b = b, nodes[p].tag = true;
		nodes[p].mn = min(nodes[p].mn, min(calc(p, l), calc(p, r)));
		return;
	}
	if (ql <= mid)
		update(ql, qr, l, mid, lson, k, b);
	if (mid < qr)
		update(ql, qr, mid + 1, r, rson, k, b);
	pushup(p);
}

ll query(int ql, int qr, int l, int r, int p)
{
	if (ql <= l && r <= qr)
		return nodes[p].mn;
	ll ret = INF;
	if (nodes[p].tag)
		ret = min(calc(p, max(l, ql)), calc(p, min(r, qr)));
	if (ql <= mid)
		ret = min(ret, query(ql, qr, l, mid, lson));
	if (mid < qr)
		ret = min(ret, query(ql, qr, mid + 1, r, rson));
	return ret;
}

void addpath(int src, int dst, int weight)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	edges[current].weight = weight, head[src] = current++;
}

void dfs1(int u, int fa)
{
	dep[u] = dep[fa] + 1, siz[u] = 1, up[u] = fa;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa)
		{
			dist[edges[i].to] = dist[u] + edges[i].weight, dfs1(edges[i].to, u);
			siz[u] += siz[edges[i].to], son[u] = siz[edges[i].to] > siz[son[u]] ? edges[i].to : son[u];
		}
}

void dfs2(int u, int org)
{
	lft[u] = ++ptot, top[u] = org, anti[ptot] = u;
	if (son[u])
		dfs2(son[u], org);
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != up[u] && edges[i].to != son[u])
			dfs2(edges[i].to, edges[i].to);
	rig[u] = ptot;
}

int getLCA(int x, int y)
{
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]])
			swap(x, y);
		x = up[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}

void update(int x, int y, ll k, ll b)
{
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]])
			swap(x, y);
		update(lft[top[x]], lft[x], 1, n, 1, k, b);
		x = up[top[x]];
	}
	if (lft[x] > lft[y])
		swap(x, y);
	update(lft[x], lft[y], 1, n, 1, k, b);
}

ll query(int x, int y)
{
	ll ret = INF;
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]])
			swap(x, y);
		ret = min(ret, query(lft[top[x]], lft[x], 1, n, 1));
		x = up[top[x]];
	}
	if (lft[x] > lft[y])
		swap(x, y);
	ret = min(ret, query(lft[x], lft[y], 1, n, 1));
	return ret;
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &q);
	for (int i = 1, u, v, w; i <= n - 1; i++)
		scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
	dfs1(1, 0), dfs2(1, 1), build(1, n, 1);
	while (q--)
	{
		int opt, s, t, lca;
		ll a, b;
		scanf("%d%d%d", &opt, &s, &t);
		if (opt == 1)
		{
			lca = getLCA(s, t), scanf("%lld%lld", &a, &b);
			update(s, lca, -a, 1LL * a * dist[s] + b);
			update(lca, t, a, 1LL * a * (dist[s] - 2LL * dist[lca]) + b);
		}
		else
			printf("%lld\n", query(s, t));
	}
	return 0;
}
