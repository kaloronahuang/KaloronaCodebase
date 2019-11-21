// P2402.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e4 + 200;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int head[MAX_N], current, dep[MAX_N], n, m, st, ed, cur[MAX_N];
ll capacity[MAX_N], balance[MAX_N], net_sum, dist[330][330];

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_N * 50];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, ll weight)
{
    addpath(src, dst, weight), addpath(dst, src, 0);
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

int dfs(int u, ll flow)
{
    if (u == ed || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (ll di = dfs(edges[i].to, min(flow, edges[i].weight)))
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
        memcpy(cur, head, sizeof(head));
        while (ll di = dfs(st, INF))
            ret += di;
    }
    return ret;
}

void build_network(ll mid)
{
    memset(head, -1, sizeof(head)), current = 0;
    st = (n << 1) | 1, ed = st + 1;
    for (int i = 1; i <= n; i++)
        addtube(st, i, balance[i]), addtube(i + n, ed, capacity[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (dist[i][j] <= mid)
                addtube(i, j + n, INF);
}

bool check(ll mid)
{
    build_network(mid);
    if (dinic() == net_sum)
        return true;
    return false;
}

int main()
{
    memset(dist, 0x3f, sizeof(dist));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &balance[i], &capacity[i]), net_sum += balance[i];
    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;
    for (ll i = 1, u, v, w; i <= m; i++)
        scanf("%lld%lld%lld", &u, &v, &w), dist[u][v] = dist[v][u] = min(dist[v][u], w);
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    ll l = 0, r = 1e18, ans = -1;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld", ans);
    return 0;
}