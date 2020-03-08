// LOJ3077.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 1e6 + 200;

int n, m, head[MAX_N], current, dfn[MAX_N], low[MAX_N], stk[MAX_N], aff[MAX_N];
int tail, ptot, deg[MAX_N], vertexTot, edgeTot, ncnt, ans[MAX_N], mem[MAX_N], remTot;
bool inst[MAX_N], valid[MAX_N], vis[MAX_N], checked[MAX_N];
set<int> G[MAX_N];
vector<pair<pair<int, int>, int> /**/> rem[MAX_N];
vector<int> remPts;

struct edge
{
    int to, nxt;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ptot, vertexTot++, edgeTot += deg[u], stk[++tail] = u, inst[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            if (dfn[edges[i].to] == 0)
                tarjan(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
            else if (inst[edges[i].to])
                low[u] = min(low[u], dfn[edges[i].to]);
    if (low[u] == dfn[u])
    {
        ncnt++;
        do
        {
            aff[stk[tail]] = ncnt, inst[stk[tail]] = false;
        } while (stk[tail--] != u);
    }
}

void dfs(int u)
{
    vis[u] = true;
    vertexTot++, edgeTot += G[u].size();
    for (auto &dst : G[u])
        if (!vis[dst])
            dfs(dst);
}

void rebuild(int org, int fa, int u, int len)
{
    G[fa].erase(u), G[u].erase(fa);
    if (valid[u])
    {
        if (org == u)
        {
            ans[len] += 2;
            if (ans[len] >= 3)
                puts("Yes"), exit(0);
            return;
        }
        rem[org].emplace_back(make_pair(u, len), ++remTot);
        rem[u].emplace_back(make_pair(org, len), remTot);
        return;
    }
    int dst = *G[u].begin();
    rebuild(org, u, dst, len + 1);
}

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

bool check(int x, int y)
{
    for (auto i : remPts)
        mem[i] = i;
    for (auto u : remPts)
        for (auto v : rem[u])
            if (!checked[v.second])
                mem[find(u)] = find(v.first.first);
    return find(x) == find(y);
}

void solve(int u, int org, int dep)
{
    if (!check(u, org))
        return;
    if (dep && u == org)
    {
        if (++ans[dep] >= 3)
            puts("Yes"), exit(0);
        return;
    }
    while (!rem[u].empty() && rem[u].back().first.first < org)
        rem[u].pop_back();
    for (int i = 0; i < rem[u].size(); i++)
    {
        pair<pair<int, int>, int> x = rem[u][i];
        if (!checked[x.second] && !vis[x.first.first])
        {
            checked[x.second] = vis[x.first.first] = true;
            solve(x.first.first, org, dep + x.first.second);
            checked[x.second] = vis[x.first.first] = false;
        }
    }
}

int main()
{
    // freopen("4-01.in", "r", stdin);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
        {
            vertexTot = 0, edgeTot = 0, tarjan(i, 0);
            if ((edgeTot >> 1) - vertexTot - 2 >= sqrt(vertexTot))
            {
                puts("Yes");
                return 0;
            }
        }
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[edges[i].to] == aff[u])
                G[u].insert(edges[i].to);
    for (int i = 1; i <= n; i++)
    {
        valid[i] = G[i].size() >= 3;
        if (!vis[i])
        {
            // start pos of the loop;
            vertexTot = edgeTot = 0, dfs(i);
            if (edgeTot == (vertexTot << 1))
            {
                ans[vertexTot] += 2;
                if (ans[vertexTot] >= 3)
                {
                    puts("Yes");
                    return 0;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (valid[i])
        {
            remPts.push_back(i);
            while (!G[i].empty())
            {
                int u = *G[i].begin();
                rebuild(i, i, u, 1);
            }
        }
    for (int i = 1; i <= n; i++)
        sort(rem[i].begin(), rem[i].end()), reverse(rem[i].begin(), rem[i].end());
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; i++)
        if (valid[i])
            solve(i, i, 0);
    puts("No");
    return 0;
}