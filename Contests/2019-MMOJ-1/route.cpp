// route.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define rg register

using namespace std;

const int MAX_N = 1e5 + 10, MAX_E = 5e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int head[MAX_N], current, n, m, q, roots[MAX_N][2], fa[17][MAX_N], dep[MAX_N], ptot;
int lft[MAX_N], rig[MAX_N], ncnt, siz[MAX_N], top[MAX_N], son[MAX_N], anti[MAX_N];
ll dist[MAX_N];
char opt[20];

struct edge
{
	int to, nxt, weight;
} edges[MAX_N];

struct node
{
	ll sum;
	int lson, rson;
} nodes[MAX_E * 75];

inline char gc(){
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}

int read()
{
	int x = 0, f = 1;
	char ch = gc();
	while (!isdigit(ch))
	{
		if (ch == '-')
			f = -1;
		ch = gc();
	}
	while (isdigit(ch))
		x = (x << 3) + (x << 1) + ch - '0', ch = gc();
	return f * x;
}

void addpath(int src, int dst, int weight)
{
	current++;
	edges[current].to = dst, edges[current].nxt = head[src];
	edges[current].weight = weight, head[src] = current;
}

inline void dfs1(int u)
{
	dep[u] = dep[fa[0][u]] + 1, siz[u] = 1;
	for (int i = head[u]; i; i = edges[i].nxt)
		dist[edges[i].to] = dist[u] + edges[i].weight, dfs1(edges[i].to), siz[u] += siz[edges[i].to], son[u] = (siz[son[u]] < siz[edges[i].to]) ? edges[i].to : son[u];
}

inline void dfs2(int u, int org)
{
	lft[u] = ++ncnt, top[u] = org;
	if (son[u] > 0)
		dfs2(son[u], org);
	for (int i = head[u]; i; i = edges[i].nxt)
		if (edges[i].to != son[u])
			dfs2(edges[i].to, edges[i].to);
	rig[u] = ncnt;
}

int getLCA(int x, int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	for (int i = 16; i >= 0; i--)
		if (dep[fa[i][x]] >= dep[y])
			x = fa[i][x];
	if (x == y)
		return x;
	for (int i = 16; i >= 0; i--)
		if (fa[i][x] != fa[i][y])
			x = fa[i][x], y = fa[i][y];
	return fa[0][x];
}

inline int update(int qx, int l, int r, int p, ll val)
{
	if (p == 0)
		p = ++ptot, nodes[p].sum = INF;
	if (l == r)
	{
		nodes[p].sum = min(nodes[p].sum, val);
		return p;
	}
	int mid = (l + r) >> 1;
	if (qx <= mid)
		nodes[p].lson = update(qx, l, mid, nodes[p].lson, val),
		nodes[p].sum = min(nodes[p].sum, nodes[nodes[p].lson].sum);
	else
		nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val),
		nodes[p].sum = min(nodes[p].sum, nodes[nodes[p].rson].sum);
	return p;
}

inline ll query(int ql, int qr, int l, int r, int p)
{
	if (p == 0)
		return INF;
	if (ql <= l && r <= qr)
		return nodes[p].sum;
	int mid = (l + r) >> 1;
	ll ret = INF;
	if (ql <= mid)
		ret = min(ret, query(ql, qr, l, mid, nodes[p].lson));
	if (mid < qr)
		ret = min(ret, query(ql, qr, mid + 1, r, nodes[p].rson));
	return ret;
}

ll jump(int u, int v)
{
	ll ret = INF;
	while (u != 0)
		ret = min(ret, query(lft[top[u]], lft[u], 1, n, roots[v][0])), u = fa[0][top[u]];
	return ret;
}

int main()
{
	freopen("route.in", "r", stdin);
	freopen("route.out", "w", stdout);
	n = read(), m = read(), q = read();
	for (int i = 2, w; i <= n; i++)
		fa[0][i] = read(), w = read(), addpath(fa[0][i], i, w);
	dfs1(1), dfs2(1, 1);
	for (int i = 1; i <= 16; i++)
		for (int j = 1; j <= n; j++)
			fa[i][j] = fa[i - 1][fa[i - 1][j]];
	for (int i = 1, u, v, w; i <= m; i++)
	{
		u = read(), v = read(), w = read();
		roots[u][0] = update(lft[v], 1, n, roots[u][0], 0LL - dist[v] + w);
		roots[u][1] = update(lft[v], 1, n, roots[u][1], 0LL + dist[v] + w);
		swap(u, v);
		roots[u][0] = update(lft[v], 1, n, roots[u][0], 0LL - dist[v] + w);
		roots[u][1] = update(lft[v], 1, n, roots[u][1], 0LL + dist[v] + w);
	}
	while (q--)
	{
		int u, v;
		u = read(), v = read(), opt[1] = gc();
		ll std_dist = dist[u] + dist[v] - (dist[getLCA(u, v)] << 1);
		if (opt[1] == 'B' || opt[1] == 'D')
		{
			ll res = jump(u, v);
			std_dist = min(std_dist, dist[u] + res);
		}
		if (opt[1] == 'C' || opt[1] == 'D')
		{
			ll res = query(lft[u], rig[u], 1, n, roots[v][1]);
			std_dist = min(std_dist, res - dist[u]);
		}
		printf("%lld\n", std_dist);
	}
	return 0;
}
