// fun.cpp
#include <bits/stdc++.h>
#include "fun.h"

using namespace std;

const int MAX_N = 550;

int dist[MAX_N][MAX_N], mxn;
bool vis[MAX_N], flag;
vector<int> ansBox;

void dfs(int u, int cnt, int last)
{
	vis[u] = true, ansBox.push_back(u);
	if (cnt == mxn)
	{
		flag = true;
		return;
	}
	for (int i = 0; i < mxn; i++)
		if (!vis[i] && last >= dist[u][i])
		{
			dfs(i, cnt + 1, dist[u][i]);
			if (flag)
				return;
		}
	vis[u] = false, ansBox.pop_back();
}

vector<int> createFunTour(int n, int q)
{
	mxn = n;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (i != j)
				dist[i][j] = dist[j][i] = hoursRequired(i, j);

	if (n > 17)
	{
		int ptA = 0, ptB = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (dist[i][j] > dist[ptA][ptB])
					ptA = i, ptB = j;
		int u = ptA;
		vis[u] = true, ansBox.push_back(u);
		while (ansBox.size() != n)
		{
			int nxt = -1;
			for (int i = 0; i < n; i++)
				if (!vis[i] && (nxt == -1 || dist[u][i] > dist[u][nxt]))
					nxt = i;
			ansBox.push_back(nxt), u = nxt, vis[u] = true;
		}
		return ansBox;
	}

	for (int i = 0; i < n; i++)
		if (!flag)
			dfs(i, 1, 0x3f3f3f3f);
	return ansBox;
}
