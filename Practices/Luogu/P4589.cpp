// P4589.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1220, INF = 0x3f3f3f3f;

int n, m, val[MAX_N], head[MAX_N], current, cur[MAX_N], dep[MAX_N];
int start_pos, end_pos;
bool mp[MAX_N][MAX_N];
vector<int> succ[MAX_N], mpx;

int ripe(int x) { return lower_bound(mpx.begin(), mpx.end(), x) - mpx.begin() + 1; }

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight)
{
    addpath(src, dst, weight);
    addpath(dst, src, 0);
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(start_pos), dep[start_pos] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dep[edges[i].to] == 0 && edges[i].weight > 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pos] != 0;
}

int dfs(int u, int flow)
{
    if (u == end_pos || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight)))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
    return 0;
}

int dinic()
{
    int ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(cur));
        while (int di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

bool check(int mid)
{
    memset(head, -1, sizeof(head)), current = 0;
    start_pos = (m << 1 | 1), end_pos = start_pos + 1;
    vector<int> V;
    for (int i = 1; i <= m; i++)
        if (ripe(val[i]) < mid)
            V.push_back(i), addtube(start_pos, i, 1), addtube(i + m, end_pos, 1);
    for (int u : V)
        for (int v : V)
            if (u != v && mp[u][v])
                addtube(u, v + m, 1);
    return (V.size() - dinic() <= n);
}

int main()
{
    scanf("%d%d", &n, &m), n++;
    for (int i = 1, tot, target; i <= m; i++)
    {
        scanf("%d%d", &val[i], &tot), mp[i][i] = true, mpx.push_back(val[i]);
        while (tot--)
            scanf("%d", &target), succ[i].push_back(target), mp[i][target] = true;
    }
    for (int k = 1; k <= m; k++)
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++)
                mp[i][j] |= mp[i][k] && mp[k][j];
    sort(mpx.begin(), mpx.end()), mpx.erase(unique(mpx.begin(), mpx.end()), mpx.end());
    if (check(mpx.size() + 1))
        puts("AK"), exit(0);
    int l = 1, r = mpx.size(), res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, res = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", mpx[res - 1]);
    return 0;
}