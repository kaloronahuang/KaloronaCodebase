// SP839.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5500, MAX_E = 2e4 + 200, INF = 0x3f3f3f3f;

int T, n, m, k, mark[MAX_N], head[MAX_N], cur[MAX_N], current;
int dep[MAX_N], ans[MAX_N], ui[MAX_E], vi[MAX_E], st, ed;
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

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
    q.push(st), dep[st] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dep[edges[i].to] == 0 && edges[i].weight > 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[ed] != 0;
}

int dfs(int u, int flow)
{
    if (u == ed || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight > 0)
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
        while (int di = dfs(st, INF))
            ret += di;
    }
    return ret;
}

void dfs_collect(int u, int bit)
{
    ans[u] += (1 << bit), vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (vis[edges[i].to] == false && edges[i].weight > 0)
            dfs_collect(edges[i].to, bit);
}

void solve()
{
    for (int bit = 0; bit <= 30; bit++)
    {
        memset(head, -1, sizeof(head)), current = 0;
        for (int i = 1; i <= m; i++)
            addpath(ui[i], vi[i], 1), addpath(vi[i], ui[i], 1);
        for (int i = 1; i <= n; i++)
            if (mark[i] != -1 && ((mark[i] >> bit) & 1))
                addtube(st, i, INF);
            else if (mark[i] != -1 && (!((mark[i] >> bit) & 1)))
                addtube(i, ed, INF);
        memset(vis, false, sizeof(vis));
        dinic(), dfs_collect(st, bit);
    }
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m), memset(ans, 0, sizeof(ans));
        for (int i = 1; i <= m; i++)
            scanf("%d%d", &ui[i], &vi[i]);
        memset(mark, -1, sizeof(mark)), scanf("%d", &k);
        for (int i = 1, id, mk; i <= k; i++)
            scanf("%d%d", &id, &mk), mark[id] = mk;
        st = n + 1, ed = st + 1, solve();
        for (int i = 1; i <= n; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}