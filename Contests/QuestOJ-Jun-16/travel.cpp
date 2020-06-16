// travel.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 10007;

int n, q, C, ai[MAX_N], bi[MAX_N];

inline char nc()
{
    static char buf[1 << 20], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    register int x = 0, f = 1;
    register char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

int nodes[MAX_N << 2][21];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

int add(register int x, register int y)
{
	x += y;
	if (x >= mod)
		x -= mod;
	return x;
}

void pushup(int p)
{
	memset(nodes[p], 0, sizeof(nodes[p]));
	for (int i = 0; i <= C; i++)
		if (nodes[lson][i])
			for (int j = 0; j <= C; j++)
				if (nodes[rson][j])
					nodes[p][min(i + j, C)] = add(nodes[p][min(i + j, C)], nodes[lson][i] * nodes[rson][j] % mod);
}

void build(int l, int r, int p)
{
	if (l == r)
	{
		nodes[p][0] = bi[l], nodes[p][1] = ai[l];
		return;
	}
	build(l, mid, lson), build(mid + 1, r, rson);
	pushup(p);
}

void update(int qx, int l, int r, int p)
{
	if (l == r)
	{
		nodes[p][0] = bi[l], nodes[p][1] = ai[l];
		return;
	}
	if (qx <= mid)
		update(qx, l, mid, lson);
	else
		update(qx, mid + 1, r, rson);
	pushup(p);
}

int main()
{
	n = read(), C = read();
	for (int i = 1; i <= n; i++)
		ai[i] = read() % mod;
	for (int i = 1; i <= n; i++)
		bi[i] = read() % mod;
	build(1, n, 1), q = read();
	while (q--)
	{
		register int opt = read(), x = read() % mod, y = read() % mod;
		ai[opt] = x, bi[opt] = y;
		update(opt, 1, n, 1), printf("%d\n", nodes[1][C]);
	}
	return 0;
}
