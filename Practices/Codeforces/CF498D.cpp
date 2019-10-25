// CF498D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int nodes[MAX_N << 2][60], n, q, ai[MAX_N], m;
char opt[5];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p, int ls, int rs)
{
	for (int st = 0; st < 60; st++)
		nodes[p][st] = nodes[ls][st] + nodes[rs][(nodes[ls][st] + st) % 60];
}

void update(int qx, int l, int r, int p, int val)
{
	if (l == r)
	{
		for (int st = 0; st < 60; st++)
			nodes[p][st] = (st % val == 0 ? 2 : 1);
		return;
	}
	if (qx <= mid)
		update(qx, l, mid, lson, val);
	else
		update(qx, mid + 1, r, rson, val);
	pushup(p, lson, rson);
}

int query(int ql, int qr, int l, int r, int p, int tim)
{
	if (ql <= l && r <= qr)
		return nodes[p][tim % 60];
	int ret = 0;
	if (ql <= mid)
		ret = query(ql, qr, l, mid, lson, tim);
	if (mid < qr)
		ret += query(ql, qr, mid + 1, r, rson, (tim + ret) % 60);
	return ret;
}

#undef lson
#undef rson
#undef mid

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &ai[i]), update(i, 1, n, 1, ai[i]);
	scanf("%d", &m);
	while (m--)
	{
		int x, y;
		scanf("%s%d%d", opt + 1, &x, &y);
		if (opt[1] == 'C')
			update(x, 1, n, 1, y);
		else
			printf("%d\n", query(x, y - 1, 1, n, 1, 0));
	}
	return 0;
}
