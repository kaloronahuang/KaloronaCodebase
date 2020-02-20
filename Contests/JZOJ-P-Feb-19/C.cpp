// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

typedef long long ll;

int n, m, head[MAX_N], current, flow[MAX_N], pre[MAX_N], start_pt, end_pt, fa[MAX_N], di[MAX_N], S, T, tag[MAX_N];
ll base_cost, dist[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_N << 2];

void fileIO()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
}

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void addtube(int src, int dst, int weight, int cost)
{
    addpath(src, dst, weight, cost), addpath(dst, src, 0, -cost);
}

void addtube(int src, int dst, int upper, int lower, int cost)
{
    if (upper != lower)
        addtube(src, dst, upper - lower, cost);
    base_cost += 1LL * lower * cost;
    di[src] -= lower, di[dst] += lower;
}

bool spfa()
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));
    memset(flow, 0, sizeof(flow));
    memset(pre, -1, sizeof(pre));
    queue<int> q;
    q.push(S), dist[S] = 0, flow[S] = INF, vis[S] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dist[edges[i].to] > dist[u] + edges[i].cost && edges[i].weight > 0)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost, pre[edges[i].to] = i;
                flow[edges[i].to] = min(flow[u], edges[i].weight);
                if (!vis[edges[i].to])
                    q.push(edges[i].to), vis[edges[i].to] = true;
            }
    }
    return flow[T] != 0;
}

pair<ll, ll> mfmc()
{
    ll ret = 0, cost = 0;
    while (spfa())
    {
        cost += 1LL * flow[T] * dist[T], ret += flow[T];
        int p = T, i = pre[p];
        while (p != S)
        {
            edges[i].weight -= flow[T], edges[i ^ 1].weight += flow[T];
            p = edges[i ^ 1].to, i = pre[p];
        }
    }
    return make_pair(ret, cost);
}

int Ai[MAX_N], Bi[MAX_N], Ci[MAX_N], Di[MAX_N];

void dfs(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), tag[u] += tag[edges[i].to];
}

int main()
{
    // fileIO();
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    start_pt = n + 1, end_pt = n + 2, S = n + 3, T = n + 4;
    for (int i = 2, fr, fb, cr, cb; i <= n; i++)
    {
        scanf("%d%d%d%d%d", &fa[i], &fr, &fb, &cr, &cb);
        Ai[i] = fr, Bi[i] = fb, Ci[i] = cr, Di[i] = cb;
        addpath(fa[i], i, 0, 0);
    }
    for (int i = 1; i <= m; i++)
    {
        int si, ti, cr, cb;
        scanf("%d%d%d%d", &si, &ti, &cr, &cb);
        Ai[i + n] = si, Bi[i + n] = ti, Ci[i + n] = cr, Di[i + n] = cb;
        tag[si]--, tag[ti]++;
    }
    dfs(1), memset(head, -1, sizeof(head)), current = 0;
    for (int i = 2, fr, fb, cr, cb; i <= n; i++)
    {
        fr = Ai[i], fb = Bi[i], cr = Ci[i], cb = Di[i];
        base_cost += 1LL * tag[i] * cb;
        if (fb + fr < tag[i])
            puts("-1"), exit(0);
        addtube(i, fa[i], min(tag[i], fr), max(0, tag[i] - fb), cr - cb);
    }
    for (int i = 1; i <= m; i++)
    {
        int si, ti, cr, cb;
        si = Ai[i + n], ti = Bi[i + n], cr = Ci[i + n], cb = Di[i + n];
        addtube(start_pt, ti, 1, 1, 0);
        addtube(si, end_pt, 1, 1, 0);
        addtube(ti, si, 1, cb - cr), base_cost += cr;
    }
    for (int i = 1; i <= n + 2; i++)
        if (di[i] > 0)
            addtube(S, i, di[i], 0);
        else
            addtube(i, T, -di[i], 0);
    addtube(end_pt, start_pt, INF, 0);
    printf("%lld\n", base_cost + mfmc().second);
    return 0;
}