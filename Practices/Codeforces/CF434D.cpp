// CF434D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e4 + 200, MAX_E = (200 * 100 + MAX_N) << 1, INF = 0x7f7f7f7f;

typedef long long ll;

int n, m, li[MAX_N], ri[MAX_N], ptot, start_pos, end_pos, head[MAX_N], current, dep[MAX_N], cur[MAX_N], ai[MAX_N], bi[MAX_N], ci[MAX_N];
map<pair<int, int>, int> idx;
ll limit;

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_E];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void addtube(int src, int dst, ll weight)
{
    addpath(src, dst, weight);
    addpath(dst, src, 0);
}

ll calc(int i, int x) { return 1LL * ai[i] * x * x + 1LL * bi[i] * x + 1LL * ci[i]; }

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

ll dfs(int u, ll flow)
{
    if (u == end_pos || flow == 0)
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
        memcpy(cur, head, sizeof(cur));
        while (ll di = dfs(start_pos, INF))
            ret += di;
    }
    return ret;
}

int getId(int x, int y) { return idx.count(make_pair(x, y)) == 0 ? idx[make_pair(x, y)] = ++ptot : idx[make_pair(x, y)]; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &ai[i], &bi[i], &ci[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &li[i], &ri[i]);
    start_pos = MAX_N - 1, end_pos = start_pos - 1, limit = INF / n;
    for (int i = 1; i <= n; i++)
    {
        addtube(start_pos, getId(i, li[i] - 1), INF);
        for (int j = li[i]; j <= ri[i]; j++)
            addtube(getId(i, j - 1), getId(i, j), limit - calc(i, j));
        addtube(getId(i, ri[i]), end_pos, INF);
    }
    for (int i = 1, u, v, d; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &d);
        for (int j = max(li[v] + d, li[u]) - 1; j <= min(ri[v] + d, ri[u]); j++)
            addtube(getId(u, j), getId(v, j - d), INF);
    }
    ll ans = 1LL * n * limit - dinic();
    printf("%lld\n", ans);
    return 0;
}