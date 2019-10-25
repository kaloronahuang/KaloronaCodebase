// P3225.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1050;

int head[MAX_N], current, n, m, dfn[MAX_N], low[MAX_N], ptot, ptlist[MAX_N];
int cut[MAX_N], roots[MAX_N], rtot, st[MAX_N], tail;
ll ans1, ans2;
vector<pr> bcc;
bool vis[MAX_N];

struct edge
{
	int to, nxt;
} edges[MAX_N];

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++ptot;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (dfn[edges[i].to] == 0)
		{
			tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
			if (low[edges[i].to] >= dfn[u])
				cut[u]++;
		}
		else
			low[u] = min(low[u], dfn[edges[i].to]);
}

void dfs(int u)
{
	vis[u] = true, st[++tail] = u;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (vis[edges[i].to] == false)
		{
			dfs(edges[i].to);
			if (low[edges[i].to] >= dfn[u])
			{
				pair<int, int> nbcc = make_pair(0, 0);
				while (st[tail] != u)
				{
					if (cut[st[tail]] > 0)
						nbcc.first++;
					else
						nbcc.second++;
					tail--;
				}
				if (cut[st[tail]] > 0)
					nbcc.first++;
				else
					nbcc.second++;
				bcc.push_back(nbcc);
			}
		}
}

int main()
{
	int case_id = 1;
	while (scanf("%d", &m) != EOF && m != 0)
	{
		memset(head, -1, sizeof(head)), current = 0, n = 0;
		memset(dfn, 0, sizeof(dfn)), memset(low, 0, sizeof(low));
		memset(cut, false, sizeof(cut)), ptot = 0, rtot = 0;
		ans1 = 0, ans2 = 1, memset(vis, false, sizeof(vis));
		bcc.clear(), tail = 0;
		for (int i = 1, u, v; i <= m; i++)
		{
			scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
			ptlist[++n] = u, ptlist[++n] = v;
		}
		sort(ptlist + 1, ptlist + 1 + n), n = unique(ptlist + 1, ptlist + 1 + n) - ptlist - 1;
		for (int i = 1; i <= n; i++)
			if (dfn[ptlist[i]] == 0)
				roots[++rtot] = ptlist[i], tarjan(ptlist[i]);
		for (int i = 1; i <= rtot; i++)
			cut[roots[i]]--;
		for (int i = 1; i <= n; i++)
			if (vis[ptlist[i]] == false)
				dfs(ptlist[i]);
		for (int i = 0, siz = bcc.size(); i < siz; i++)
		{
			pr curt = bcc[i];
			if (curt.first == 1)
				ans1++, ans2 *= curt.second;
			else if (curt.first == 0)
				ans1 += 2, ans2 *= (curt.second) * (curt.second - 1) / 2;
		}
		printf("Case %d: %lld %lld\n", case_id++, ans1, ans2);
	}
	return 0;
}
