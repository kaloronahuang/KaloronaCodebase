// icefire.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

int n, upper, mp[MAX_N], mpcnt;

int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (isdigit(c))
		x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

int ripe(int x) { return lower_bound(mp + 1, mp + 1 + mpcnt, x) - mp; }

void fileIO()
{
	freopen("icefire.in", "r", stdin);
	freopen("icefire.out", "w", stdout);
}

struct queryInfo
{
	int opt, t, x, y;
} queries[MAX_N];

struct node
{
	int pre, suf, sum[2];
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void update(int qx, int l, int r, int p, int typ, int val, int sgn)
{
	nodes[p].pre += sgn * (1 - typ) * val, nodes[p].suf += sgn * typ * val;
	nodes[p].sum[typ] += sgn;
	if (l == r)
		return;
	if (qx <= mid)
		update(qx, l, mid, lson, typ, val, sgn);
	else
		update(qx, mid + 1, r, rson, typ, val, sgn);
}

int queryPre(int k, int l, int r, int p, int acc = 0)
{
	if (l == r)
	{
		if (acc + nodes[p].sum[0] == 0)
			return -1;
		return l;
	}
	if (k <= nodes[lson].pre)
		return queryPre(k, l, mid, lson, acc);
	else
		return queryPre(k - nodes[lson].pre, mid + 1, r, rson, acc + nodes[lson].sum[0]);
}

int querySuf(int k, int l, int r, int p, int acc = 0)
{
	if (l == r)
	{
		if (acc + nodes[p].sum[1] == 0)
			return -1;
		return l;
	}
	if (k <= nodes[rson].suf)
		return querySuf(k, mid + 1, r, rson, acc);
	else
		return querySuf(k - nodes[rson].suf, l, mid, lson, acc + nodes[rson].sum[1]);
}

int check(int threshold)
{
	int ice = queryPre(threshold, 1, upper, 1);
	int fire = querySuf(threshold, 1, upper, 1);
	if (ice == -1 || fire == -1)
		return 0;
	if (ice > fire)
		return 0;
	return fire;
}

#undef mid

int main()
{
	fileIO();
	n = read();
	for (int i = 1; i <= n; i++)
	{
		queries[i].opt = read(), queries[i].t = read();
		if (queries[i].opt == 1)
			queries[i].x = read(), queries[i].y = read(), mp[++mpcnt] = queries[i].x;
	}
	sort(mp + 1, mp + 1 + mpcnt), mpcnt = unique(mp + 1, mp + 1 + mpcnt) - mp - 1;
	upper = mpcnt;
	for (int i = 1; i <= n; i++)
		queries[i].x = ripe(queries[i].x);
	int acc = 0;
	for (int i = 1; i <= n; i++)
	{
		if (queries[i].opt == 1)
			update(queries[i].x, 1, upper, 1, queries[i].t, queries[i].y, 1), acc += queries[i].y;
		else
		{
			register int rid = queries[i].t;
			update(queries[rid].x, 1, upper, 1, queries[rid].t, queries[rid].y, -1), acc -= queries[i].y;
		}
		register int l = 0, r = acc, res = -1;
		while (l <= r)
		{
			register int mid = (l + r) >> 1;
			if (check(mid))
				res = mid, l = mid + 1;
			else
				r = mid - 1;
		}
		if (res == -1)
			puts("Peace");
		else
			printf("%d %d\n", mp[check(res)], res << 1);
	}
	return 0;
}
