// CF932F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, RANGE = 2e5, BASE = 1e5;

typedef long long ll;

const ll INF = (1LL << 62) - 1 + (1LL << 62);

int n, ai[MAX_N], bi[MAX_N], ptot, stot, head[MAX_N], current, roots[MAX_N];
ll dp[MAX_N];

struct edge
{
	int to, nxt;
} edges[MAX_N << 1];

struct segment
{
	ll k, b;
} segs[MAX_N * 30];

struct node
{
	int lson, rson, sid;
} nodes[MAX_N];

ll evaluate(int id, ll x) { return 1LL * segs[id].k * (x - BASE) + segs[id].b; }

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

#define mid ((l + r) >> 1)

int update(int l, int r, int p, int sid)
{
	if (p == 0)
		p = ++ptot;
	if (evaluate(nodes[p].sid, l) >= evaluate(sid, l) && evaluate(nodes[p].sid, r) >= evaluate(sid, r))
		return nodes[p].sid = sid, p;
	if (evaluate(nodes[p].sid, l) <= evaluate(sid, l) && evaluate(nodes[p].sid, r) <= evaluate(sid, r))
		return p;
	if (segs[sid].k < segs[nodes[p].sid].k)
		if (evaluate(sid, mid) <= evaluate(nodes[p].sid, mid))
			nodes[p].lson = update(l, mid, nodes[p].lson, nodes[p].sid), nodes[p].sid = sid;
		else
			nodes[p].rson = update(mid + 1, r, nodes[p].rson, sid);
	else if (evaluate(sid, mid) <= evaluate(nodes[p].sid, mid))
		nodes[p].rson = update(mid + 1, r, nodes[p].rson, nodes[p].sid), nodes[p].sid = sid;
	else
		nodes[p].lson = update(l, mid, nodes[p].lson, sid);
	return p;
}

int merge(int x, int y, int l, int r)
{
	if (x == 0 || y == 0)
		return x + y;
	if (l == r)
		return evaluate(nodes[x].sid, l) >= evaluate(nodes[y].sid, l) ? y : x;
	nodes[x].lson = merge(nodes[x].lson, nodes[y].lson, l, mid);
	nodes[x].rson = merge(nodes[x].rson, nodes[y].rson, mid + 1, r);
	update(l, r, x, nodes[y].sid);
	return x;
}

ll query(int qx, int l, int r, int p)
{
	if (p == 0)
		return INF;
	ll ret = evaluate(nodes[p].sid, qx);
	if (l == r)
		return ret;
	if (qx <= mid)
		ret = min(ret, query(qx, l, mid, nodes[p].lson));
	else
		ret = min(ret, query(qx, mid + 1, r, nodes[p].rson));
	return ret;
}

void solve(int u, int fa)
{
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa)
		{
			solve(edges[i].to, u);
			roots[u] = merge(roots[u], roots[edges[i].to], 0, RANGE);
		}
	if (roots[u])
		dp[u] = query(ai[u] + BASE, 0, RANGE, roots[u]);
	segs[++stot] = segment{bi[u], dp[u]};
	roots[u] = update(0, RANGE, roots[u], stot);
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &ai[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &bi[i]);
	for (int i = 1, u, v; i <= n - 1; i++)
		scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
	segs[0] = {0, INF}, solve(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%lld ", dp[i]);
	puts("");
	return 0;
}
