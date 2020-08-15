// P2805.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 3e5 + 200, MAX_E = 2e6 + 200, INF = 0x3f3f3f3f;

namespace SubtaskToposort
{

    int deg[MAX_N], ptot;
    vector<int> G[MAX_N];

    void addpath(int src, int dst) { G[src].push_back(dst), deg[dst]++; }

    void toposort()
    {
        queue<int> q;
        for (int i = 1; i <= ptot; i++)
            if (deg[i] == 0)
                q.push(i);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : G[u])
                if (--deg[v] == 0)
                    q.push(v);
        }
    }

} // namespace SubtaskToposort

int n, m, head[MAX_N], current, dep[MAX_N], start_pos, end_pos, cur[MAX_N], score[MAX_N];
vector<int> target[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E];

int getId(int x, int y) { return (x - 1) * m + y; }

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
    memset(dep, 0, sizeof(int) * (end_pos + 5));
    memcpy(cur, head, sizeof(int) * (end_pos + 5));
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

ll dinic()
{
    ll ret = 0;
    while (bfs())
        while (int di = dfs(start_pos, INF))
            ret += di;
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), SubtaskToposort::ptot = n * m;
    for (int i = 1; i <= n; i++)
        for (int j = 1, tot, u, v; j <= m; j++)
        {
            scanf("%d%d", &score[getId(i, j)], &tot);
            while (tot--)
            {
                scanf("%d%d", &u, &v), u++, v++;
                target[getId(i, j)].push_back(getId(u, v));
                SubtaskToposort::addpath(getId(i, j), getId(u, v));
            }
            if (j < m)
                target[getId(i, j + 1)].push_back(getId(i, j)), SubtaskToposort::addpath(getId(i, j + 1), getId(i, j));
        }
    SubtaskToposort::toposort();
    start_pos = n * m + 1, end_pos = n * m + 2;
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (SubtaskToposort::deg[getId(i, j)] == 0)
            {
                int u = getId(i, j);
                if (score[u] > 0)
                    addtube(start_pos, u, score[u]), ans += score[u];
                else if (score[u] < 0)
                    addtube(u, end_pos, -score[u]);
                for (int v : target[u])
                    if (SubtaskToposort::deg[v] == 0)
                        addtube(v, u, INF);
            }
    printf("%lld\n", ans - dinic());
    return 0;
}