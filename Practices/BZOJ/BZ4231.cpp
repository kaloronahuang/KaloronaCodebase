// BZ4231.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 6e5 + 200;

typedef pair<int, int> pii;

int n, m, head[MAX_N], current;
int ansBox[MAX_N], dep[MAX_N], up[20][MAX_N], upweight[MAX_N];
char cmdlet[MAX_N], S[MAX_N];
vector<pii> tags[2][MAX_N];

struct AC_Automaton
{
	int ch[MAX_N][26], lft[MAX_N], rig[MAX_N], nodes[MAX_N], fail[MAX_N], dtot, ptot = 1;
	vector<int> G[MAX_N];
	
	void dfs(int u)
	{
		lft[u] = ++dtot;
		for (int v : G[u])
			dfs(v);
		rig[u] = dtot;
	}
	
	void build()
	{
		queue<int> q;
		for (int i = 0; i < 26; i++)
			if (ch[1][i])
				q.push(ch[1][i]), fail[ch[1][i]] = 1;
			else
				ch[1][i] = 1;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int i = 0; i < 26; i++)
				if (ch[u][i])
					fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]);
				else
					ch[u][i] = ch[fail[u]][i];
		}
		for (int i = 2; i <= ptot; i++)
			G[fail[i]].push_back(i);
		dfs(1);
	}
	
	inline int lowbit(int x) { return x & (-x); }
	
	void update(int x, int d)
	{
		for (; x <= dtot; x += lowbit(x))
			nodes[x] += d;
	}
	
	int query(int x, int ret = 0)
	{
		for (; x; x -= lowbit(x))
			ret += nodes[x];
		return ret;
	}
	
} tr[2];

struct edge
{
	int to, nxt, weight;
} edges[MAX_N << 1];

struct queryInfo
{
	int u, v, rt, pos, rev;
} queries[MAX_N];

void addpath(int src, int dst, int weight)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fa)
{
	up[0][u] = fa, dep[u] = dep[fa] + 1;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa)
			upweight[edges[i].to] = edges[i].weight, dfs(edges[i].to, u);
}

int getLCA(int x, int y)
{
	if (dep[x] < dep[y])
		swap(x, y);
	for (int i = 19; i >= 0; i--)
		if (dep[up[i][x]] >= dep[y])
			x = up[i][x];
	if (x == y)
		return x;
	for (int i = 19; i >= 0; i--)
		if (up[i][x] != up[i][y])
			x = up[i][x], y = up[i][y];
	return up[0][x];
}

int kmp()
{
	static int nxt[MAX_N];
	int ret = 0, tLen = strlen(cmdlet + 1), i = 0, j = -1;
	char *T = cmdlet + 1;
	nxt[0] = -1;
	while (i < tLen)
	{
		if (j == -1 || T[i] == T[j])
			nxt[++i] = ++j;
		else
			j = nxt[j];
	}
	int curt = 0, pre = 0;
	while (S[curt])
	{
		if (pre == -1 || S[curt] == T[pre])
			curt++, pre++;
		else
			pre = nxt[pre];
		if (pre == tLen)
			ret++;
	}
	return ret;
}

int jump(int u, int delta)
{
	for (int i = 19; i >= 0; i--)
		if (delta & (1 << i))
			u = up[i][u];
	return u;
}

void collect(int u, int p1, int p2, int fa)
{
	tr[0].update(tr[0].lft[p1], 1), tr[1].update(tr[1].lft[p2], 1);
	for (pii x : tags[0][u])
	{
		int org = x.first;
		ansBox[org] += x.second * (tr[0].query(tr[0].rig[queries[x.first].pos]) - tr[0].query(tr[0].lft[queries[x.first].pos] - 1));
	}
	for (pii x : tags[1][u])
	{
		int org = x.first;
		ansBox[org] += x.second * (tr[1].query(tr[1].rig[queries[x.first].rev]) - tr[1].query(tr[1].lft[queries[x.first].rev] - 1));
	}
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa)
			collect(edges[i].to, tr[0].ch[p1][edges[i].weight], tr[1].ch[p2][edges[i].weight], u);
	tr[0].update(tr[0].lft[p1], -1), tr[1].update(tr[1].lft[p2], -1);
}

int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v; i <= n - 1; i++)
	{
		scanf("%d%d%s", &u, &v, cmdlet + 1);
		addpath(u, v, cmdlet[1] - 'a'), addpath(v, u, cmdlet[1] - 'a');
	}
	dfs(1, 0);
	for (int i = 1; i <= 19; i++)
		for (int j = 1; j <= n; j++)
			up[i][j] = up[i - 1][up[i - 1][j]];
	for (int qptr = 1, u, v; qptr <= m; qptr++)
	{
		scanf("%d%d%s", &u, &v, cmdlet + 1);
		queries[qptr].u = u, queries[qptr].v = v;
		queries[qptr].rt = getLCA(u, v);
		int p = 1, len = strlen(cmdlet + 1);
		for (int i = 1; i <= len; i++)
		{
			if (tr[0].ch[p][cmdlet[i] - 'a'] == 0)
				tr[0].ch[p][cmdlet[i] - 'a'] = ++tr[0].ptot;
			p = tr[0].ch[p][cmdlet[i] - 'a'];
		}
		queries[qptr].pos = p, p = 1;
		for (int i = len; i >= 1; i--)
		{
			if (tr[1].ch[p][cmdlet[i] - 'a'] == 0)
				tr[1].ch[p][cmdlet[i] - 'a'] = ++tr[1].ptot;
			p = tr[1].ch[p][cmdlet[i] - 'a'];
		}
		queries[qptr].rev = p;
		if (!((queries[qptr].rt == u) || (queries[qptr].rt == v)))
		{
			int b = min(len - 1, dep[queries[qptr].u] - dep[queries[qptr].rt]), sublen = b, a = 0, j;
			for (a = 0, j = jump(queries[qptr].u, dep[queries[qptr].u] - dep[queries[qptr].rt] - b); j != queries[qptr].rt; a++, j = up[0][j])
				S[a] = upweight[j] + 'a';
			b = min(len - 1, dep[queries[qptr].v] - dep[queries[qptr].rt]), sublen += b;
			for (a = sublen - 1, j = jump(queries[qptr].v, dep[queries[qptr].v] - dep[queries[qptr].rt] - b); j != queries[qptr].rt; a--, j = up[0][j])
				S[a] = upweight[j] + 'a';
			S[sublen] = 0;
			ansBox[qptr] = kmp();
		}
		if (dep[queries[qptr].v] - dep[queries[qptr].rt] >= len)
		{
			tags[0][queries[qptr].v].push_back(make_pair(qptr, 1));
			tags[0][jump(queries[qptr].v, dep[queries[qptr].v] - dep[queries[qptr].rt] - len + 1)].push_back(make_pair(qptr, -1));
		}
		if (dep[queries[qptr].u] - dep[queries[qptr].rt] >= len)
		{
			tags[1][queries[qptr].u].push_back(make_pair(qptr, 1));
			tags[1][jump(queries[qptr].u, dep[queries[qptr].u] - dep[queries[qptr].rt] - len + 1)].push_back(make_pair(qptr, -1));
		}
	}
	tr[0].build(), tr[1].build(), collect(1, 1, 1, 0);
	for (int i = 1; i <= m; i++)
		printf("%d\n", ansBox[i]);
	return 0;
}
