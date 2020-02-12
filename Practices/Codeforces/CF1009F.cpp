// CF1009F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, head[MAX_N], current, dep[MAX_N], son[MAX_N], siz[MAX_N], idx[MAX_N], ans[MAX_N];
unordered_map<int, int> ump[MAX_N];
set<pair<int, int> /**/> st[MAX_N];

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
    siz[u] = 1, dep[u] = dep[fa] + 1, ump[idx[u]][dep[u]] = 1, st[idx[u]].insert(make_pair(-1, dep[u]));
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
            son[u] = (siz[edges[i].to] > siz[son[u]]) ? edges[i].to : son[u];
        }
}

void merge(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            merge(edges[i].to, u);
            if (ump[idx[edges[i].to]].size() > ump[idx[u]].size())
                swap(idx[edges[i].to], idx[u]);
            // merge;
            for (unordered_map<int, int>::iterator it = ump[idx[edges[i].to]].begin(); it != ump[idx[edges[i].to]].end(); it++)
                if (ump[idx[u]].find(it->first) != ump[idx[u]].end())
                {
                    st[idx[u]].erase(make_pair(-ump[idx[u]][it->first], it->first));
                    ump[idx[u]][it->first] += it->second;
                    st[idx[u]].insert(make_pair(-ump[idx[u]][it->first], it->first));
                }
                else
                {
                    ump[idx[u]][it->first] = it->second;
                    st[idx[u]].insert(make_pair(-it->second, it->first));
                }
        }
    ans[u] = st[idx[u]].begin()->second - dep[u];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n; i++)
        idx[i] = i;
    dfs(1, 0), merge(1, 0);
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return 0;
}