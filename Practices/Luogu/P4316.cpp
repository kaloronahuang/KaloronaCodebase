// P4316.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 100000 + 100;
int head[MAX_N], current, n, m, tmpx, tmpy, tmpz, indeg[MAX_N], outdeg[MAX_N];
double pro[MAX_N], ans = 0;
struct edge
{
	int to, nxt;
	double weight;
} edges[MAX_N << 1];
void addpath(int u, int v, int w)
{
	edges[current].to = v, edges[current].nxt = head[u];
	edges[current].weight = w, head[u] = current++;
}
void toposort()
{
	queue<int> q;
	q.push(1);
	pro[1] = 1;
	while (!q.empty())
	{
		int pt = q.front();
		q.pop();
		for (int i = head[pt]; i != -1; i = edges[i].nxt)
		{
			int to = edges[i].to;
			ans += (double)(pro[pt] / (double)outdeg[pt] * (double)edges[i].weight);
			pro[to] += (double)(pro[pt] / (double)outdeg[pt]);
			indeg[to]--;
			if (indeg[to] == 0)
				q.push(to);
		}
	}
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &tmpx, &tmpy, &tmpz), addpath(tmpx, tmpy, tmpz), indeg[tmpy]++, outdeg[tmpx]++;
	toposort();
	printf("%.2lf", ans);
	return 0;
}
