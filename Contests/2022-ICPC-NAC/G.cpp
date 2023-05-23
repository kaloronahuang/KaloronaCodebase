// G.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550, MAX_P = MAX_N * MAX_N, dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

int n, m, head[MAX_P], current, outbound_id, dfn[MAX_P], low[MAX_P], aff[MAX_P], stk[MAX_P], tail, ptot, ncnt, deg[MAX_P], sites[MAX_P];
char mp[MAX_N][MAX_N];
bool inst[MAX_P];
vector<int> near_sites[MAX_P];
set<int> near_sites_ext[MAX_P];
vector<int> G[MAX_P];

struct edge
{
    int to, nxt;
} edges[MAX_P];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

inline int calc(int x, int y) { return (x - 1) * m + y; }

void connect_if(int x, int y, int dstx, int dsty)
{
    if (1 <= dstx && dstx <= n && 1 <= dsty && dsty <= m && mp[dstx][dsty] != '.' && mp[dstx][dsty] != '#')
        addpath(calc(dstx, dsty), calc(x, y));
    else
        addpath(outbound_id, calc(x, y));
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, inst[u] = true, stk[++tail] = u;
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

int occupied, ans;

void dfs(int u)
{
    // occupy;
    for (int tag : near_sites_ext[u])
    {
        sites[tag]++;
        if (sites[tag] == 1)
            occupied++;
    }
    ans = max(ans, occupied);
    for (int v : G[u])
        dfs(v);
    for (int tag : near_sites_ext[u])
    {
        sites[tag]--;
        if (sites[tag] == 0)
            occupied--;
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), outbound_id = n * m + 1;
    for (int i = 1; i <= n; i++)
        scanf("%s", mp[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] != '#' && mp[i][j] != '.')
            {
                // scan the sites first;
                for (int d = 0; d < 4; d++)
                {
                    int dstx = i + dx[d], dsty = j + dy[d];
                    if (1 <= dstx && dstx <= n && 1 <= dsty && dsty <= m && mp[dstx][dsty] == '#')
                        near_sites[calc(i, j)].push_back(calc(dstx, dsty));
                }
                switch (mp[i][j])
                {
                case '<':
                    connect_if(i, j, i, j - 1);
                    break;
                case '>':
                    connect_if(i, j, i, j + 1);
                    break;
                case '^':
                    connect_if(i, j, i - 1, j);
                    break;
                case 'v':
                    connect_if(i, j, i + 1, j);
                    break;
                }
            }
    tarjan(outbound_id);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] != '#' && mp[i][j] != '.' && dfn[calc(i, j)] == 0)
                tarjan(calc(i, j));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (mp[i][j] != '#' && mp[i][j] != '.')
            {
                int u = calc(i, j);
                for (int x : near_sites[u])
                    near_sites_ext[aff[u]].insert(x);
            }
    for (int u = 1; u <= outbound_id; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[u] != aff[edges[i].to])
                G[aff[u]].push_back(aff[edges[i].to]), deg[aff[edges[i].to]]++;
    for (int i = 1; i <= ncnt; i++)
        if (deg[i] == 0)
            dfs(i);
    printf("%d\n", ans);
    return 0;
}