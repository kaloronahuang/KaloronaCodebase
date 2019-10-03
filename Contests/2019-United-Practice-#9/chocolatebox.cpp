// chocolatebox.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int tree1[MAX_N << 2], tree2[MAX_N << 2], n, m, k, p1, p2, seq_org[MAX_N], seq_pow[MAX_N];

int quick_pow(int bas, int tim, int mod)
{
	if (mod == 0)
		return 0;
	int ans = 1;
	bas %= mod;
	while (tim)
	{
		if (tim & 1)
			ans = 1LL * ans * bas % mod;
		bas = 1LL * bas * bas % mod;
		tim >>= 1;
	}
	return ans;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)

void build(int l, int r, int p, int *nodes, int *seq, int mod)
{
	if (mod == 0)
		return;
	if (l == r)
		return (void)(nodes[p] = seq[l]);
	int mid = (l + r) >> 1;
	build(l, mid, lson, nodes, seq, mod), build(mid + 1, r, rson, nodes, seq, mod);
	nodes[p] = 1LL * nodes[lson] * nodes[rson] % mod;
}

int query(int ql, int qr, int l, int r, int p, int mod, int *nodes)
{
	if (mod == 0)
		return 0;
	if (ql <= l && r <= qr)
		return nodes[p];
	int mid = (l + r) >> 1, ret = 1;
	if (ql <= mid)
		ret = 1LL * ret * query(ql, qr, l, mid, lson, mod, nodes) % mod;
	if (mid < qr)
		ret = 1LL * ret * query(ql, qr, mid + 1, r, rson, mod, nodes) % mod;
	return ret;
}

int main()
{
	freopen("chocolatebox.in", "r", stdin);
	freopen("chocolatebox.out", "w", stdout);
	scanf("%d%d%d%d%d", &n, &m, &k, &p1, &p2);
	for (int i = 1; i <= n; i++)
		scanf("%d", &seq_org[i]), seq_pow[i] = quick_pow(k, seq_org[i], p2);
	build(1, n, 1, tree1, seq_org, p1), build(1, n, 1, tree2, seq_pow, p2);
	while (m--)
	{
		int typ, l, r;
		scanf("%d%d%d", &typ, &l, &r);
		printf("%d\n", query(l, r, 1, n, 1, (typ == 1 ? p1 : p2), (typ == 1 ? tree1 : tree2)));
	}
	return 0;
}

