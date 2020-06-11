// BZ4919.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, head[MAX_N], current, fa[MAX_N], val[MAX_N], idx[MAX_N];
multiset<int> ms[MAX_N];

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
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        dfs(edges[i].to, u);
        if (ms[idx[edges[i].to]].size() > ms[idx[u]].size())
            swap(idx[edges[i].to], idx[u]);
        for (multiset<int>::iterator it = ms[idx[edges[i].to]].begin(); it != ms[idx[edges[i].to]].end(); it++)
            ms[idx[u]].insert(*it);
    }
    multiset<int>::iterator it = ms[idx[u]].lower_bound(val[u]);
    if (it != ms[idx[u]].end())
        ms[idx[u]].erase(it);
    ms[idx[u]].insert(val[u]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &val[i], &fa[i]), addpath(fa[i], i), idx[i] = i;
    dfs(1, 0), printf("%d\n", int(ms[idx[1]].size()));
    return 0;
}