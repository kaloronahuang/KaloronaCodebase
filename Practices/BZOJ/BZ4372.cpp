// BZ4372.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, head[MAX_N], current, up[MAX_N], siz[MAX_N], roots[MAX_N][2], ptot, droot;
int st[20][MAX_N], dep[MAX_N], stot, log2_[MAX_N], pos[MAX_N];
bool vis[MAX_N];
char cmdlet[20];

struct edge
{
	int to, nxt;
} edges[MAX_N << 1];

struct node
{
	int lson, rson, sum;
} nodes[MAX_N * 60];

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

int max_val = 0x7fffffff, groot;

void fdfs(int u, int fa, int capacity)
{
	int max_sub = 0;
	siz[u] = 1;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa && !vis[edges[i].to])
		{
			fdfs(edges[i].to, u, capacity), siz[u] += siz[edges[i].to];
			max_sub = max(max_sub, siz[edges[i].to]);
		}
	max_sub = max(max_sub, capacity - siz[u]);
	if (max_sub < max_val)
		max_val = max_sub, groot = u;
}

int find_root(int entry_point, int capacity) { return max_val = 0x7fffffff, fdfs(entry_point, 0, capacity), groot; }

void solve(int u, int capacity)
{
	vis[u] = true;
	for (int i = head[u], tmp, subg; i != -1; i = edges[i].nxt)
		if (!vis[edges[i].to])
		{
			tmp = siz[edges[i].to], subg = find_root(edges[i].to, tmp);
			up[subg] = u, solve(subg, tmp);
		}
}

void dfs(int u, int fa)
{
	st[0][++stot] = u, pos[u] = stot, dep[u] = dep[fa] + 1;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa)
			dfs(edges[i].to, u), st[0][++stot] = u;
}

int gmin(int x, int y) { return dep[x] < dep[y] ? x : y; }

int getLCA(int x, int y)
{
	if (pos[x] > pos[y])
		swap(x, y);
	int d = log2_[pos[y] - pos[x] + 1];
	return gmin(st[d][pos[x]], st[d][pos[y] - (1 << d) + 1]);
}

int getDist(int x, int y) { return dep[x] + dep[y] - (dep[getLCA(x, y)] << 1); }

#define mid ((l + r) >> 1)

int query(int ql, int qr, int l, int r, int p)
{
	if (p == 0)
		return 0;
	if (ql <= l && r <= qr)
		return nodes[p].sum;
	int ret = 0;
	if (ql <= mid)
		ret += query(ql, qr, l, mid, nodes[p].lson);
	if (mid < qr)
		ret += query(ql, qr, mid + 1, r, nodes[p].rson);
	return ret;
}

int update(int qx, int l, int r, int p, int val)
{
	if (p == 0)
		p = ++ptot;
	nodes[p].sum += val;
	if (l == r)
		return p;
	if (qx <= mid)
		nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
	else
		nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
	return p;
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= n - 1; i++)
		scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
	solve(droot = find_root(1, n), n), dfs(1, 0);
	for (int i = 2; i <= stot; i++)
		log2_[i] = log2_[i >> 1] + 1;
	for (int i = 1; i < 20; i++)
		for (int j = 1; j + (1 << i) - 1 <= stot; j++)
			st[i][j] = gmin(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
	while (m--)
	{
		scanf("%s", cmdlet + 1);
		if (cmdlet[1] == 'Q')
		{
			int u, ans = 0;
			scanf("%d", &u);
			for (int x = u; x; x = up[x])
			{
				ans += query(getDist(u, x), n, 0, n, roots[x][0]);
				if (up[x])
					ans -= query(getDist(u, up[x]), n, 0, n, roots[x][1]);
			}
			printf("%d\n", ans);
		}
		else
		{
			int u, a, b;
			scanf("%d%d%d", &u, &a, &b);
			for (int x = u; x; x = up[x])
			{
				if (a >= getDist(x, u))
					roots[x][0] = update(min(n, a - getDist(x, u)), 0, n, roots[x][0], b);
				if (up[x] && a >= getDist(up[x], u))
					roots[x][1] = update(min(n, a - getDist(up[x], u)), 0, n, roots[x][1], b);
			}
		}
	}
	return 0;
}
