// P3749.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

typedef long long ll;

int n, m, ai[110], di[110][110], head[MAX_N], current, start_pos, end_pos, dep[MAX_N], cur[MAX_N], ptot, id[110][110], upper;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N * 10];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int weight) { addpath(src, dst, weight), addpath(dst, src, 0); }

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
    if (flow == 0 || u == end_pos)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1 && edges[i].weight > 0)
        {
            int di = dfs(edges[i].to, min(flow, edges[i].weight));
            if (di > 0)
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
        }
    return 0;
}

int dinic()
{
    int ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(head));
        while (int di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), upper = max(upper, ai[i]);
    start_pos = ++ptot, end_pos = ++ptot;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            scanf("%d", &di[i][j]), id[i][j] = ++ptot;
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
        {
            int cost = di[i][j];
            if (i == j)
            {
                if (m)
                    addtube(id[i][j], ptot + ai[i], INF);
                cost -= ai[i];
            }
            else
            {
                addtube(id[i][j], id[i + 1][j], INF);
                addtube(id[i][j], id[i][j - 1], INF);
            }
            if (cost > 0)
                addtube(start_pos, id[i][j], cost), ans += cost;
            if (cost < 0)
                addtube(id[i][j], end_pos, -cost);
        }
    if (m)
        for (int i = 1; i <= upper; i++)
            addtube(++ptot, end_pos, 1LL * i * i);
    printf("%lld\n", ans - dinic());
    return 0;
}