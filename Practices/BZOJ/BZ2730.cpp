// BZ2730.cpp
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
int curtans = 0;
vector<int> G[510], anspool;
void addpath(int src, int dst) { G[src].push_back(dst), G[dst].push_back(src); }
int dfn[510], low[510], limit, curtdfn, n, m, tmpx, tmpy, secans;
void dfs(int u)
{
    dfn[u] = curtdfn++;
    int siz = G[u].size();
    for (int i = 0; i < siz; i++)
    {
        int to = G[u][i];
        if (to == limit || dfn[to] != 0)
            continue;
        dfs(to);
    }
    low[u] = curtdfn;
}
void tarjan(int u)
{
}
void solve()
{
    anspool.clear(), curtans = 0, secans = 0, curtdfn = 0;
    for (limit = 1; limit <= n; limit++)
    {
        memset(dfn, 0, sizeof(dfn)), memset(low, 0, sizeof(low));
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            if (i != limit && dfn[i] == 0)
                dfs(i), cnt++;
        if (curtans < cnt)
            anspool.clear(), anspool.push_back(limit), curtans = cnt;
        else if (curtans == cnt)
            anspool.push_back(limit);
    }
    // got the answers;
    for (int i = 0; i < curtans; i++)
    {
        int currentLimit = anspool[i];
    }
    return;
}
int main()
{
    while (scanf("%d", &m) && m != 0)
    {
        for (int i = 0; i < 510; i++)
            G[i].resize(0);
        n = 0;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &tmpx, &tmpy);
            addpath(tmpx, tmpy);
            n = max(n, max(tmpx, tmpy));
        }
        solve();
    }
    return 0;
}