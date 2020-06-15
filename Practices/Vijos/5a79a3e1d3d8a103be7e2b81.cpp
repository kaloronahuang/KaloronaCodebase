// 5a79a3e1d3d8a103be7e2b81.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 300100;

int n, q, lans, up[20][MAX_N], hbit[MAX_N], top[MAX_N], dep[MAX_N], son[MAX_N];
int head[MAX_N], current, ulen[MAX_N];
vector<int> cup[MAX_N], cdown[MAX_N];

inline char gc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
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

struct edge
{
	int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

void dfs(int u, int fa)
{
	dep[u] = dep[fa] + 1, up[0][u] = fa;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa)
		{
			dfs(edges[i].to, u);
			son[u] = ulen[son[u]] < ulen[edges[i].to] ? edges[i].to : son[u];
		}
	ulen[u] = ulen[son[u]] + 1;
}

void collect(int u, int org)
{
	top[u] = org;
	if (son[u])
		collect(son[u], org);
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != up[0][u] && edges[i].to != son[u])
			collect(edges[i].to, edges[i].to);
}

int query(int u, int k)
{
	if (dep[u] < k)
		return 0;
	if (k == 0)
		return u;
	int b = hbit[k];
	k ^= (1 << b), u = up[b][u];
	if (k == 0)
		return u;
	if (dep[u] - dep[top[u]] == k)
		return top[u];
	if (dep[u] - dep[top[u]] > k)
		return cdown[top[u]][dep[u] - dep[top[u]] - k - 1];
	return cup[top[u]][k - (dep[u] - dep[top[u]]) - 1];
}

int main()
{
	memset(head, -1, sizeof(head)), n = read();
	for (int i = 1, u, v; i <= n - 1; i++)
		u = read(), v = read(), addpath(u, v), addpath(v, u);
	dfs(1, 0), collect(1, 1);
	for (int i = 1; i < 20; i++)
		for (int j = 1; j <= n; j++)
			up[i][j] = up[i - 1][up[i - 1][j]];
	for (int i = 1; i <= n; i++)
		if (i == top[i])
		{
			int u = i, len = 0;
			while (len < ulen[i] && u)
				u = up[0][u], cup[i].push_back(u), len++;
			len = 0, u = i;
			while (len < ulen[i])
				u = son[u], cdown[i].push_back(u), len++;
		}
	int mx_bit = 0;
	for (int i = 1; i <= n; i++)
	{
		if (i & (1 << (mx_bit + 1)))
			mx_bit++;
		hbit[i] = mx_bit;
	}
	q = read();
	while (q--)
	{
		int a = read(), b = read();
		a ^= lans, b ^= lans;
		printf("%d\n", lans = query(a, b));
	}
	return 0;
}
