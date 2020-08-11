// P5934.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e4 + 200, MAX_M = 2e5 + 200, INF = 0x3f3f3f3f;

int n, m, head[MAX_N], current, cur[MAX_N], start_pos, end_pos, dep[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_M << 2];

struct seg
{
    int u, v, w;
    bool operator<(const seg &rhs) const { return w < rhs.w; }
} segs[MAX_M];

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
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
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

int main()
{
    memset(head, -1, sizeof(head)), current = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m + 1; i++)
        scanf("%d%d%d", &segs[i].u, &segs[i].v, &segs[i].w);
    sort(segs + 1, segs + 1 + m);
    for (int i = 1; i <= m; i++)
        if (segs[i].w < segs[m + 1].w)
            addtube(segs[i].u, segs[i].v, 1), addtube(segs[i].v, segs[i].u, 1);
    start_pos = segs[m + 1].u, end_pos = segs[m + 1].v;
    int ans = dinic();
    memset(head, -1, sizeof(head)), current = 0;
    for (int i = 1; i <= m; i++)
        if (segs[i].w > segs[m + 1].w)
            addtube(segs[i].u, segs[i].v, 1), addtube(segs[i].v, segs[i].u, 1);
    ans += dinic(), printf("%d\n", ans);
    return 0;
}