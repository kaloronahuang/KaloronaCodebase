#include <bits/stdc++.h>
#include "swap.h"

using namespace std;

const int MAX_N = 3e5 + 200, MAX_E = 2e5 + 200;

int mem[MAX_N], ptot, up[20][MAX_N], weights[MAX_N], dep[MAX_N], deg[MAX_N];
bool vis[MAX_N];
vector<int> G[MAX_N];

struct edge
{
	int u, v, w;
	bool operator<(const edge &rhs) const { return w < rhs.w; }
} edges[MAX_E];

int find(int x) { return mem[x] == x ? x : mem[x] = find(mem[x]); }

void dfs(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	for (int v : G[u])
		dfs(v, u); //, cerr << u << " " << v << endl;
}

void init(int N, int M, vector<int> U, vector<int> V, vector<int> W)
{
	for (int i = 0; i < M; i++)
		edges[i + 1] = edge{U[i] + 1, V[i] + 1, W[i]};
	sort(edges + 1, edges + 1 + M), ptot = N + M;
	for (int i = 1; i <= ptot; i++)
		mem[i] = i;
	for (int i = 1; i <= M; i++)
	{
		int u = edges[i].u, v = edges[i].v;
		deg[u]++, deg[v]++;
		weights[i + N] = edges[i].w;
		int fu = find(u), fv = find(v);
		if (fu == fv)
			vis[i + N] = true, G[i + N].push_back(fu), up[0][fu] = i + N, mem[fu] = i + N;
		else
		{
			G[i + N].push_back(fu), G[i + N].push_back(fv);
			up[0][fu] = up[0][fv] = i + N;
			mem[fu] = mem[fv] = i + N;
			vis[i + N] = vis[fu] || vis[fv] || (deg[u] >= 3) || (deg[v] >= 3);
		}
	}
	dfs(ptot, 0);
	/*
	for (int i = 1; i <= M; i++)
		cerr << "u = " << edges[i].u << " v = " << edges[i].v << " w = " << edges[i].w << endl;
	cerr << endl;
	for (int i = 1; i <= ptot; i++)
		cerr << "u = " << i << " : " << vis[i] << endl;
	*/
	vis[0] = true;
	for (int i = 1; i < 20; i++)
		for (int j = 1; j <= ptot; j++)
			up[i][j] = up[i - 1][up[i - 1][j]];
}

int getMinimumFuelCapacity(int X, int Y)
{
	X++, Y++;
	if (dep[X] <= dep[Y])
		swap(X, Y);
	for (int i = 19; i >= 0; i--)
		if (dep[up[i][X]] >= dep[Y])
			X = up[i][X];
	// cerr << endl;
	// cerr << "Q " << X << " " << Y << endl;
	if (X != Y)
	{
		for (int i = 19; i >= 0; i--)
			if (up[i][X] != up[i][Y])
				X = up[i][X], Y = up[i][Y];
		X = up[0][X];
	}
	// cerr << "Q " << X << " " << Y << endl;
	for (int i = 19; i >= 0; i--)
		if (!vis[up[i][X]])
			X = up[i][X];
	// cerr << "Q " << X << " " << Y << endl;
	if (!vis[X])
		X = up[0][X];
	// cerr << "Q " << X << " " << Y << endl;
	if (X == 0)
		return -1;
	return weights[X];
}
