// P2787.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200;

int n, q, nodes[MAX_N << 2][26], tag[MAX_N << 2], ovec[26];
char str[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
	for (int i = 0; i < 26; i++)
		nodes[p][i] = nodes[lson][i] + nodes[rson][i];
}

void build(int l, int r, int p)
{
	if (l == r)
		return (void)(nodes[p][str[l] - 'A'] = 1);
	build(l, mid, lson), build(mid + 1, r, rson);
	pushup(p);
}

void pushdown(int p, int l, int r)
{
	if (tag[p])
	{
		tag[lson] = tag[rson] = tag[p], tag[p]--;
		memset(nodes[lson], 0, sizeof(nodes[lson]));
		memset(nodes[rson], 0, sizeof(nodes[rson]));
		nodes[lson][tag[p]] = mid - l + 1;
		nodes[rson][tag[p]] = r - mid;
		tag[p] = 0;
	}
}

void update(int ql, int qr, int l, int r, int p, int val)
{
	if (ql <= l && r <= qr)
	{
		memset(nodes[p], 0, sizeof(nodes[p]));
		nodes[p][val] = r - l + 1, tag[p] = val + 1;
		return;
	}
	pushdown(p, l, r);
	if (ql <= mid)
		update(ql, qr, l, mid, lson, val);
	if (mid < qr)
		update(ql, qr, mid + 1, r, rson, val);
	pushup(p);
}

void query(int ql, int qr, int l, int r, int p)
{
	if (ql <= l && r <= qr)
	{
		for (int c = 0; c < 26; c++)
			ovec[c] += nodes[p][c];
		return;
	}
	pushdown(p, l, r);
	if (ql <= mid)
		query(ql, qr, l, mid, lson);
	if (mid < qr)
		query(ql, qr, mid + 1, r, rson);
}

int main()
{
	scanf("%d%d%s", &n, &q, str + 1);
	for (int i = 1; i <= n; i++)
		if ('a' <= str[i] && str[i] <= 'z')
			str[i] = 'A' + str[i] - 'a';
	build(1, n, 1);
	while (q--)
	{
		int opt, x, y;
		scanf("%d%d%d", &opt, &x, &y);
		if (opt == 1)
		{
			scanf("%s", str + 1);
			if ('a' <= str[1] && str[1] <= 'z')
				str[1] = 'A' + str[1] - 'a';
			memset(ovec, 0, sizeof(ovec));
			query(x, y, 1, n, 1), printf("%d\n", ovec[str[1] - 'A']);
		}
		else if (opt == 2)
		{
			scanf("%s", str + 1);
			if ('a' <= str[1] && str[1] <= 'z')
				str[1] = 'A' + str[1] - 'a';
			update(x, y, 1, n, 1, str[1] - 'A');
		}
		else
		{
			memset(ovec, 0, sizeof(ovec)), query(x, y, 1, n, 1);
			int l = x;
			for (int i = 0; i < 26; i++)
				if (ovec[i])
					update(l, l + ovec[i] - 1, 1, n, 1, i), l += ovec[i];
		}
	}
	return 0;
}
