// message.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef pair<int, int> pii;

int T, n, m, head[MAX_N], current, ansBox[MAX_N], siz[MAX_N], dep[MAX_N], bucket[MAX_N];
bool tag[MAX_N];
vector<pii> queries[MAX_N];

struct edge
{
	int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
	edges[current].to = dst, edges[current].nxt = head[src];
	head[src] = current++;
}

int max_val = 0x3f3f3f3f, groot;

void fdfs(int u, int fa, int capacity)
{
	siz[u] = 1;
	int max_son = 0;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa && tag[edges[i].to] == false)
			fdfs(edges[i].to, u, capacity), siz[u] += siz[edges[i].to], max_son = max(max_son, siz[edges[i].to]);
	max_son = max(max_son, capacity - siz[u]);
	if (max_son < max_val)
		groot = u, max_val = max_son;
}

int find_root(int entryPoint, int capacity) { return max_val = 0x3f3f3f3f, groot = 0, fdfs(entryPoint, 0, capacity), groot; }

void mark(int u, int fa, int delta)
{
	dep[u] = dep[fa] + 1, bucket[dep[u]] += delta;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa && !tag[edges[i].to])
			mark(edges[i].to, u, delta);
}

void collect(int u, int fa, int capacity)
{
	for (int i = 0, siz_ = queries[u].size(); i < siz_; i++)
	{
		if (queries[u][i].first - dep[u] > 0 && queries[u][i].first - dep[u] <= capacity)
			ansBox[queries[u][i].second] += bucket[queries[u][i].first - dep[u]];
		if (queries[u][i].first == dep[u])
			ansBox[queries[u][i].second]++;
	}
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (edges[i].to != fa && !tag[edges[i].to])
			collect(edges[i].to, u, capacity);
}

void solve(int u, int capacity)
{
	tag[u] = true, dep[u] = 0;
	for (int j = 0; j <= capacity; j++)
		bucket[j] = 0;
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (!tag[edges[i].to])
			mark(edges[i].to, u, 1);
	for (int i = 0, siz_ = queries[u].size(); i < siz_; i++)
		ansBox[queries[u][i].second] += bucket[queries[u][i].first];
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (!tag[edges[i].to])
			mark(edges[i].to, u, -1), collect(edges[i].to, u, capacity), mark(edges[i].to, u, 1);
	for (int i = head[u]; i != -1; i = edges[i].nxt)
		if (!tag[edges[i].to])
			mark(edges[i].to, u, -1);
	for (int i = head[u], tmp; i != -1; i = edges[i].nxt)
		if (!tag[edges[i].to])
			tmp = siz[edges[i].to], solve(find_root(edges[i].to, tmp), tmp);
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		memset(head, -1, sizeof(head)), current = 0;
		memset(siz, 0, sizeof(siz)), memset(bucket, 0, sizeof(bucket));
		memset(dep, 0, sizeof(dep)), memset(tag, 0, sizeof(tag));
		memset(ansBox, 0, sizeof(ansBox));
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			queries[i].clear();
		for (int i = 1, u, v; i <= n - 1; i++)
			scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
		for (int i = 1, u, k; i <= m; i++)
			scanf("%d%d", &u, &k), queries[u].push_back(make_pair(k, i)), ansBox[i] = k == 0;
		solve(find_root(1, n), n);
		for (int i = 1; i <= m; i++)
			printf("%d\n", ansBox[i]);
	}
	return 0;
}