// CF280C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5 + 100;
int head[MAX_N], current, n, tmpx, tmpy;
double ans = 0;
struct edge
{
	int to, nxt;
} edges[MAX_N << 1];
void addpath(int u, int v)
{
	edges[current].to = v, edges[current].nxt = head[u];
	head[u] = current++;
}
void dfs(int u, int fa, int dep)
{
	ans += 1.0 / dep;
	for(int i = head[u]; i != -1; i = edges[i].nxt)
		if(edges[i].to != fa)
			dfs(edges[i].to, u, dep + 1);
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for(int i = 1; i <= n - 1; i++)
		scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
	dfs(1, 0, 1);
	printf("%.20lf", ans);
	return 0;
}
