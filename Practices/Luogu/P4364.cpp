// P4364.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, fa[MAX_N], siz[MAX_N], di[MAX_N];
int nodes[MAX_N << 2], tag[MAX_N << 2], ans[MAX_N], lptr[MAX_N];
double splen;

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

// SegmentTree;

void pushup(int p) { nodes[p] = min(nodes[lson], nodes[rson]); }

void pushdown(int p)
{
	if (tag[p])
	{
		tag[lson] += tag[p], tag[rson] += tag[p];
		nodes[lson] += tag[p], nodes[rson] += tag[p];
		tag[p] = 0;
	}
}

void build(int l, int r, int p)
{
	if (l == r)
		return (void)(nodes[p] = l);
	build(l, mid, lson), build(mid + 1, r, rson);
	pushup(p);
}

void update(int ql, int qr, int l, int r, int p, int val)
{
	if (ql <= l && r <= qr)
		return (void)(nodes[p] += val, tag[p] += val);
	pushdown(p);
	if (ql <= mid)
		update(ql, qr, l, mid, lson, val);
	if (mid < qr)
		update(ql, qr, mid + 1, r, rson, val);
	pushup(p);
}

int query(int k, int l, int r, int p)
{
	if (l == r)
		return l + (nodes[p] < k);
	pushdown(p);
	if (k <= nodes[rson])
		return query(k, l, mid, lson);
	else
		return query(k, mid + 1, r, rson);
}

int main()
{
	scanf("%d%lf", &n, &splen);
	for (int i = 1; i <= n; i++)
		scanf("%d", &di[i]);
	for (int i = n; i >= 1; i--)
		fa[i] = int(i / splen), siz[i] = 1;
	for (int i = n; i >= 1; i--)
		siz[fa[i]] += siz[i];
	sort(di + 1, di + 1 + n), reverse(di + 1, di + 1 + n);
	for (int i = n - 1; i >= 1; i--)
		if (di[i] == di[i + 1])
			lptr[i] = lptr[i + 1] + 1;
	build(1, n, 1);
	for (int i = 1; i <= n; i++)
	{
		if (fa[i] != fa[i - 1])
			update(ans[fa[i]], n, 1, n, 1, siz[fa[i]] - 1);
		int x = query(siz[i], 1, n, 1);
		x += lptr[x], lptr[x]++, x -= lptr[x] - 1, ans[i] = x;
		update(x, n, 1, n, 1, -siz[i]);
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", di[ans[i]]);
	puts("");
	return 0;
}
