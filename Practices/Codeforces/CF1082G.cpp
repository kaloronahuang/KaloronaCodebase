// CF1082G.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;

int head[MAX_N], n, m, dot[MAX_N], cur[MAX_N], dep[MAX_N], current;
int start_pt, end_pt;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int flow)
{
    addpath(src, dst, flow), addpath(dst, src, 0);
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(start_pt), dep[start_pt] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pt] != 0;
}

ll dfs(int u, ll flow)
{
    if (u == end_pt || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
        {
            ll di = dfs(edges[i].to, min(flow, 1LL * edges[i].weight));
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
    {
        memcpy(cur, head, sizeof(head));
        while (ll di = dfs(start_pt, INF))
            ret += di;
    }
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), start_pt = n + m + 1, end_pt = start_pt + 1;
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &val), addtube(start_pt, i, val);
    ll ans = 0;
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w), ans += w;
        addtube(i + n, end_pt, w), addtube(u, i + n, 0x3f3f3f3f), addtube(v, i + n, 0x3f3f3f3f);
    }
    ans -= dinic();
    printf("%lld\n", ans);
    return 0;
}