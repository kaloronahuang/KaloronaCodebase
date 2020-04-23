// LOJ117.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200, MAX_E = 3e5 + 200, INF = 0x3f3f3f3f;

typedef long long ll;

int n, m, gS, gT, start_pos, end_pos, head[MAX_N], current, dep[MAX_N], cur[MAX_N], di[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
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

ll dinic()
{
    ll ret = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(cur));
        while (int di = dfs(start_pos, 0x3f3f3f3f))
            ret += di;
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &gS, &gT);
    start_pos = n + 1, end_pos = n + 2;
    for (int i = 1, u, v, lower, upper; i <= m; i++)
    {
        scanf("%d%d%d%d", &u, &v, &lower, &upper);
        addtube(u, v, upper - lower);
        di[u] -= lower, di[v] += lower;
    }
    for (int i = 1; i <= n; i++)
        if (di[i] < 0)
            addtube(i, end_pos, -di[i]);
        else
            addtube(start_pos, i, di[i]);
    addtube(gT, gS, INF);
    ll ret = dinic();
    bool flag = true;
    for (int i = head[start_pos]; i != -1; i = edges[i].nxt)
        flag &= edges[i].weight == 0;
    if (flag == false)
        puts("please go home to sleep"), exit(0);
    ret = edges[current - 1].weight;
    start_pos = gT, end_pos = gS;
    edges[current - 1].weight = edges[current - 2].weight = 0;
    ret -= dinic(), printf("%lld\n", ret);
    return 0;
}