// BZ1924.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int n, R, C, start_pt, current, head[MAX_N], dfn[MAX_N], stk[MAX_N], tail, low[MAX_N];
int ncnt, aff[MAX_N], ptot, dp[MAX_N], gans, deg[MAX_N], xi[MAX_N], yi[MAX_N], typ[MAX_N], end_pt, weight[MAX_N];
vector<int> Rmp, Cmp, G[MAX_N];
map<pair<int, int>, int> ext;
bool inst[MAX_N];

struct edge
{
    int to, nxt;
} edges[3202400];

int ripe(vector<int> &rhs, int x) { return lower_bound(rhs.begin(), rhs.end(), x) - rhs.begin() + 1; }

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, stk[++tail] = u, inst[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        ncnt++;
        do
        {
            aff[stk[tail]] = ncnt, inst[stk[tail]] = false;
        } while (stk[tail--] != u);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &R, &C);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &xi[i], &yi[i], &typ[i]), ext[make_pair(xi[i], yi[i])] = i;
        Rmp.push_back(xi[i]), Cmp.push_back(yi[i]);
    }
    sort(Rmp.begin(), Rmp.end()), Rmp.erase(unique(Rmp.begin(), Rmp.end()), Rmp.end());
    sort(Cmp.begin(), Cmp.end()), Cmp.erase(unique(Cmp.begin(), Cmp.end()), Cmp.end());
    R = Rmp.size(), C = Cmp.size();
    for (int i = 1; i <= n; i++)
    {
        int x = ripe(Rmp, xi[i]), y = ripe(Cmp, yi[i]);
        addpath(x + n, i), addpath(y + n + R, i);
        if (typ[i] == 1)
            addpath(i, x + n);
        else if (typ[i] == 2)
            addpath(i, y + n + R);
        else
            for (int d = 0; d < 8; d++)
            {
                int dstx = xi[i] + dx[d], dsty = yi[i] + dy[d];
                if (ext.count(make_pair(dstx, dsty)))
                    addpath(i, ext[make_pair(dstx, dsty)]);
            }
    }
    start_pt = n + R + C + 1, end_pt = start_pt + 1;
    for (int i = 1; i <= n; i++)
        addpath(start_pt, i), addpath(i, end_pt);
    for (int i = 1; i <= end_pt; i++)
        if (dfn[i] == 0)
            tarjan(i);
    for (int i = 1; i <= n; i++)
        weight[aff[i]]++;
    for (int u = 1; u <= end_pt; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[u] != aff[edges[i].to])
            {
                G[aff[u]].push_back(aff[edges[i].to]), deg[aff[edges[i].to]]++;
                // printf("%d %d\n", aff[u], aff[edges[i].to]);
            }
    queue<int> q;
    for (int u = 1; u <= ncnt; u++)
        if (u != aff[start_pt] && deg[u] == 0)
            for (int i = 0, siz = G[u].size(); i < siz; i++)
                deg[G[u][i]]--;
    q.push(aff[start_pt]), dp[aff[start_pt]] = weight[aff[start_pt]];
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0, siz = G[u].size(); i < siz; i++)
        {
            int v = G[u][i];
            dp[G[u][i]] = max(dp[G[u][i]], dp[u] + weight[G[u][i]]);
            if (--deg[G[u][i]] == 0)
                q.push(G[u][i]);
        }
    }
    printf("%d\n", dp[aff[end_pt]]);
    return 0;
}