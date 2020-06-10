// P4662.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, MAX_E = 1e5 + 200 + (MAX_N * 3), INF = 0x3f3f3f3f;

int n, m, head[MAX_N], current, dep[MAX_N], start_pos, end_pos;
int warehouse, port;
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
    for (int i = head[u]; i != -1; i = edges[i].nxt)
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
        while (int di = dfs(start_pos, INF))
            ret += di;
    return ret;
}

void collect(int u)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (vis[edges[i].to] == false && edges[i].weight > 0)
            collect(edges[i].to);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &port, &warehouse);
    start_pos = port, end_pos = warehouse + n;
    for (int i = 1, cut; i <= n; i++)
        scanf("%d", &cut), addtube(i, i + n, cut);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addtube(u + n, v, INF), addtube(v + n, u, INF);
    dinic(), collect(start_pos);
    vector<int> ansBox;
    for (int i = 0; i < current; i += 2)
        if (vis[edges[i ^ 1].to] && !vis[edges[i].to])
            ansBox.push_back(edges[i ^ 1].to);
    sort(ansBox.begin(), ansBox.end()), ansBox.erase(unique(ansBox.begin(), ansBox.end()), ansBox.end());
    for (int u : ansBox)
        printf("%d ", u);
    puts("");
    return 0;
}