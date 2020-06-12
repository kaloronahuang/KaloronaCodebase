// P4364.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, fa[MAX_N], head[MAX_N], current, siz[MAX_N], di[MAX_N], upper, nodes[MAX_N << 2];
double splen;
vector<int> mp;

struct edge
{
	int to, nxt;
} edges[MAX_N << 1];

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

void dfs(int u)
{
	siz[u] = 1;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		dfs(edges[i].to), siz[u] += siz[edges[i].to];
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void update(int qx, int l, int r, int p, int delta = 1)
{
	nodes[p] += delta;
	if (l == r)
		return;
	if (qx <= mid)
		update(qx, l, mid, lson, delta);
	else
		update(qx, mid + 1, r, rson, delta);
}

int queryKth(int k, int l, int r, int p)
{
	if (l == r)
		return l;
	if (k <= nodes[rson])
		return queryKth(k, mid + 1, r, rson);
	else
		return queryKth(k - nodes[rson], l, mid, lson);
}

vector<int> ans;

void collect(int u)
{
	int pos = queryKth(siz[u], 0, upper, 1);
	ans.push_back(pos), update(pos, 0, upper, 1, -1);
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		collect(edges[i].to);
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%lf", &n, &splen);
	for (int i = 1; i <= n; i++)
		scanf("%d", &di[i]), mp.push_back(di[i]);
	for (int i = n; i >= 1; i--)
		fa[i] = int(i / splen), addpath(fa[i], i);
	dfs(0), sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
	upper = mp.size(), update(0, 0, upper, 1);
	for (int i = 1; i <= n; i++)
		di[i] = ripe(di[i]), update(di[i], 0, upper, 1);
	collect(0);
	for (int i = 1; i <= n; i++)
		printf("%d ", mp[ans[i] - 1]);
	puts("");
	return 0;
}
